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

tlvmReturn tlvmDebugCheck(tlvmContext* context)
{
	if(context == NULL)
		tlvmReturnCode(NO_CONTEXT);

	tlvmPauseClock(context);

	tlvmDebugBreakpoint* breakpoint = context->m_Breakpoints;
	while(breakpoint)
	{
		if(breakpoint->m_Address == context->m_ProgramCounter)
		{
			context->m_DebugState = TLVM_DEBUG_STATE_BREAK;
			breakpoint->m_Callback(TLVM_DEBUG_BREAKPOINT, breakpoint->m_Address);
		}
		breakpoint = breakpoint->m_Next;
	}

	tlvmResumeClock(context);

	tlvmReturnCode(SUCCESS);
}

#endif/*TLVM_DEBUG*/