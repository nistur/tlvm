/*
Copyright (c) 2015 Philipp Geyer

This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not
   claim that you wrote the original software. If you use this software
   in a product, an acknowledgement in the product documentation would be
   appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be
   misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.

Philipp Geyer
nistur@gmail.com
*/

#include <tlvm_internal.h>

#ifdef TLVM_DEBUG

tlvmReturn tlvmDebugAddBreakpoint(tlvmContext* context, tlvmShort addr, tlvmDebugCallbackFn callback)
{
    TLVM_NULL_CHECK(context, NO_CONTEXT);

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
    TLVM_NULL_CHECK(context, NO_CONTEXT);

#ifdef TLVM_HAS_8080
	// for now, we only have the 8080
	return tlvm8080DebugGetInstruction(context, instuction, size);
#endif/*TLVM_HAS_8080*/
    TLVM_RETURN_CODE(UNIMPLEMENTED);
}

tlvmReturn tlvmDebugStep(tlvmContext* context, tlvmDebugCallbackFn callback)
{
    TLVM_NULL_CHECK(context, NO_CONTEXT);

	context->m_StepCallback = callback;

	TLVM_RETURN_CODE(SUCCESS);
}

tlvmReturn tlvmDebugContinue(tlvmContext* context)
{
    TLVM_NULL_CHECK(context, NO_CONTEXT);

	context->m_StepCallback = NULL;
	context->m_DebugState = TLVM_DEBUG_STATE_RUN;

	TLVM_RETURN_CODE(SUCCESS);
}

tlvmReturn tlvmDebugHalt(tlvmContext* context)
{
    TLVM_NULL_CHECK(context, NO_CONTEXT);

	context->m_DebugState = TLVM_DEBUG_STATE_HALT;

	TLVM_RETURN_CODE(SUCCESS);	
}

tlvmReturn tlvmSetProgramCounter(tlvmContext* context, tlvmShort addr)
{
    TLVM_NULL_CHECK(context, NO_CONTEXT);
	context->m_ProgramCounter = addr;

	TLVM_RETURN_CODE(SUCCESS);
}

tlvmReturn tlvmDebugGetMemory(tlvmContext* context, tlvmShort addr, tlvmShort size, tlvmByte** dst)
{
	tlvmByte* target = *dst;
	tlvmShort address;
    TLVM_NULL_CHECK(context, NO_CONTEXT);

    TLVM_NULL_CHECK(dst, NO_MEMORY);
	for(address = addr; address != addr + size; ++address)
	{
		tlvmByte* mem = tlvmGetMemory(context, address, TLVM_FLAG_READ);
    	TLVM_NULL_CHECK(mem, INVALID_INPUT);
		*target = *mem;
		target++;
	}

	TLVM_RETURN_CODE(SUCCESS);
}

tlvmReturn tlvmDebugParseRegister(tlvmContext* context, tlvmChar* regstr, tlvmByte* outreg)
{
    TLVM_NULL_CHECK(context, NO_CONTEXT);

#ifdef TLVM_HAS_8080
	return tlvm8080DebugParseRegister(context, regstr, outreg);
#endif/*TLVM_HAS_8080*/
    TLVM_RETURN_CODE(UNIMPLEMENTED);
}

tlvmReturn tlvmDebugGetRegister(tlvmContext* context, tlvmByte regid, tlvmByte* outval)
{
    TLVM_NULL_CHECK(context, NO_CONTEXT);
    TLVM_NULL_CHECK(outval, INVALID_INPUT);
    TLVM_NULL_CHECK(context->m_Registers, INVALID_INPUT);

	*outval = context->m_Registers[regid];

	TLVM_RETURN_CODE(SUCCESS);
}

tlvmReturn tlvmDebugCheck(tlvmContext* context)
{
    TLVM_NULL_CHECK(context, NO_CONTEXT);

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
    TLVM_NULL_CHECK(context, NO_CONTEXT);

    context->m_DebugState = TLVM_DEBUG_STATE_RUN;
    
    TLVM_RETURN_CODE(SUCCESS);	
}

#endif/*TLVM_DEBUG*/
