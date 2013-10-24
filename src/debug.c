#include <tlvm_internal.h>

#ifdef TLVM_DEBUG

tlvmReturn tlvmDebugAddBreakpoint(tlvmContext* context, tlvmShort addr, tlvmDebugCallbackFn callback)
{
	if(context == NULL)
		tlvmReturnCode(NO_CONTEXT);

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

	tlvmReturnCode(SUCCESS);
}

tlvmReturn tlvmDebugGetInstruction(tlvmContext* context, tlvmChar** instuction)
{
	if(context == NULL)
		tlvmReturnCode(NO_CONTEXT);

	// for now, we only have the 8080
	return tlvm8080DebugGetInstruction(context, instuction);
}

tlvmReturn tlvmDebugStep(tlvmContext* context, tlvmDebugCallbackFn callback)
{
	if(context == NULL)
		tlvmReturnCode(NO_CONTEXT);

	context->m_StepCallback = callback;

	tlvmReturnCode(SUCCESS);
}

tlvmReturn tlvmDebugContinue(tlvmContext* context)
{
	if(context == NULL)
		tlvmReturnCode(NO_CONTEXT);

	context->m_StepCallback = NULL;
	context->m_DebugState = TLVM_DEBUG_STATE_RUN;

	tlvmReturnCode(SUCCESS);
}

tlvmReturn tlvmDebugHalt(tlvmContext* context)
{
	if(context == NULL)
		tlvmReturnCode(NO_CONTEXT);

	context->m_DebugState = TLVM_DEBUG_STATE_HALT;

	tlvmReturnCode(SUCCESS);	
}

tlvmReturn tlvmDebugGetMemory(tlvmContext* context, tlvmShort addr, tlvmShort size, tlvmByte** dst)
{
	tlvmByte* target = *dst;
	tlvmShort address;
	if(context == NULL)
		tlvmReturnCode(NO_CONTEXT);

	if(dst == NULL)
		tlvmReturnCode(NO_MEMORY);
	for(address = addr; address != addr + size; ++addr)
	{
		tlvmByte* mem = tlvmGetMemory(context, address, TLVM_FLAG_READ);
		if(mem == NULL)
			tlvmReturnCode(INVALID_INPUT);
		*target = *mem;
		target++;
	}

	tlvmReturnCode(SUCCESS);
}

tlvmReturn tlvmDebugParseRegister(tlvmContext* context, tlvmChar* regstr, tlvmByte* outreg)
{
	if(context == NULL)
		tlvmReturnCode(NO_CONTEXT);

	return tlvm8080DebugParseRegister(context, regstr, outreg);
}

tlvmReturn tlvmDebugGetRegister(tlvmContext* context, tlvmByte regid, tlvmByte* outval)
{
	if(context == NULL)
		tlvmReturnCode(NO_CONTEXT);
	if(outval == NULL)
		tlvmReturnCode(INVALID_INPUT);
	if(context->m_Registers == NULL)
		tlvmReturnCode(INVALID_INPUT);

	*outval = context->m_Registers[regid];

	tlvmReturnCode(SUCCESS);
}

tlvmReturn tlvmDebugCheck(tlvmContext* context)
{
	if(context == NULL)
		tlvmReturnCode(NO_CONTEXT);

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
		tlvmReturnCode(EXIT);
	}

	tlvmResumeClock(context);

	tlvmReturnCode(SUCCESS);
}

#endif/*TLVM_DEBUG*/