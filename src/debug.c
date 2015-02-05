#include <tlvm_internal.h>

#ifdef TLVM_DEBUG

tlvmReturn tlvmDebugAddBreakpoint(tlvmContext* context, tlvmShort addr, tlvmDebugCallbackFn callback)
{
	if(context == NULL)
		TLVM_RETURN_CODE(NO_CONTEXT);

	tlvmDebugBreakpoint* breakpoint = tlvmMalloc(tlvmDebugBreakpoint);
	breakpoint->m_Address = addr;
	breakpoint->m_Callback = callback;

	if(context->m_Breakpoints == NULL)
	{
		context->m_Breakpoints = breakpoint;
	}
	else
	{
		tlvmDebugBreakpoint* prev = context->m_Breakpoints;
		while(prev->m_Next != NULL)
			prev = prev->m_Next;
		prev->m_Next = breakpoint;
	}

	TLVM_RETURN_CODE(SUCCESS);
}

tlvmReturn tlvmDebugGetInstruction(tlvmContext* context, tlvmChar** instuction, tlvmByte* size)
{
	if(context == NULL)
		TLVM_RETURN_CODE(NO_CONTEXT);

	// for now, we only have the 8080
	return tlvm8080DebugGetInstruction(context, instuction, size);
}

tlvmReturn tlvmDebugStep(tlvmContext* context, tlvmDebugCallbackFn callback)
{
	if(context == NULL)
		TLVM_RETURN_CODE(NO_CONTEXT);

	context->m_StepCallback = callback;

	TLVM_RETURN_CODE(SUCCESS);
}

tlvmReturn tlvmDebugContinue(tlvmContext* context)
{
	if(context == NULL)
		TLVM_RETURN_CODE(NO_CONTEXT);

	context->m_StepCallback = NULL;
	context->m_DebugState = TLVM_DEBUG_STATE_RUN;

	TLVM_RETURN_CODE(SUCCESS);
}

tlvmReturn tlvmDebugHalt(tlvmContext* context)
{
	if(context == NULL)
		TLVM_RETURN_CODE(NO_CONTEXT);

	context->m_DebugState = TLVM_DEBUG_STATE_HALT;

	TLVM_RETURN_CODE(SUCCESS);	
}

tlvmReturn tlvmSetProgramCounter(tlvmContext* context, tlvmShort addr)
{
	if(context == NULL)
		TLVM_RETURN_CODE(NO_CONTEXT);
	context->m_ProgramCounter = addr;

	TLVM_RETURN_CODE(SUCCESS);
}

tlvmReturn tlvmDebugGetMemory(tlvmContext* context, tlvmShort addr, tlvmShort size, tlvmByte** dst)
{
	tlvmByte* target = *dst;
	tlvmShort address;
	if(context == NULL)
		TLVM_RETURN_CODE(NO_CONTEXT);

	if(dst == NULL)
		TLVM_RETURN_CODE(NO_MEMORY);
	for(address = addr; address != addr + size; ++addr)
	{
		tlvmByte* mem = tlvmGetMemory(context, address, TLVM_FLAG_READ);
		if(mem == NULL)
			TLVM_RETURN_CODE(INVALID_INPUT);
		*target = *mem;
		target++;
	}

	TLVM_RETURN_CODE(SUCCESS);
}

tlvmReturn tlvmDebugParseRegister(tlvmContext* context, tlvmChar* regstr, tlvmByte* outreg)
{
	if(context == NULL)
		TLVM_RETURN_CODE(NO_CONTEXT);

	return tlvm8080DebugParseRegister(context, regstr, outreg);
}

tlvmReturn tlvmDebugGetRegister(tlvmContext* context, tlvmByte regid, tlvmByte* outval)
{
	if(context == NULL)
		TLVM_RETURN_CODE(NO_CONTEXT);
	if(outval == NULL)
		TLVM_RETURN_CODE(INVALID_INPUT);
	if(context->m_Registers == NULL)
		TLVM_RETURN_CODE(INVALID_INPUT);

	*outval = context->m_Registers[regid];

	TLVM_RETURN_CODE(SUCCESS);
}

tlvmReturn tlvmDebugCheck(tlvmContext* context)
{
	if(context == NULL)
		TLVM_RETURN_CODE(NO_CONTEXT);

	tlvmPauseClock(context);
	if(context->m_DebugState == TLVM_DEBUG_STATE_BREAK)
	{
		if(context->m_StepCallback != NULL)
		{
			context->m_StepCallback(context, TLVM_DEBUG_STEP, context->m_ProgramCounter);
		}
		else
		{
			context->m_DebugState = TLVM_DEBUG_STATE_RUN;
		}
	}
	else if(context->m_DebugState == TLVM_DEBUG_STATE_RUN)
	{
		tlvmDebugBreakpoint* breakpoint = context->m_Breakpoints;
		while(breakpoint)
		{
			if(breakpoint->m_Address == context->m_ProgramCounter)
			{
				context->m_DebugState = TLVM_DEBUG_STATE_BREAK;
				breakpoint->m_Callback(context, TLVM_DEBUG_BREAKPOINT, breakpoint->m_Address);
			}
			breakpoint = breakpoint->m_Next;
		}
	}
	else if(context->m_DebugState == TLVM_DEBUG_STATE_HALT)
	{
		tlvmResumeClock(context); // make sure the clock doesn't stay paused
		TLVM_RETURN_CODE(EXIT);
	}

	tlvmResumeClock(context);

	TLVM_RETURN_CODE(SUCCESS);
}

tlvmReturn tlvmDebugReset(tlvmContext* context)
{
    if(context == NULL)
        TLVM_RETURN_CODE(NO_CONTEXT);

    context->m_DebugState = TLVM_DEBUG_STATE_RUN;
    
    TLVM_RETURN_CODE(SUCCESS);	
}

#endif/*TLVM_DEBUG*/