#ifndef __TLVM_DEBUG_INTERNAL_H__
#define __TLVM_DEBUG_INTERNAL_H__

#ifdef  TLVM_DEBUG

#define TLVM_DEBUG_STATE_RUN 	0x00
#define TLVM_DEBUG_STATE_BREAK	0x01
#define TLVM_DEBUG_STATE_HALT   0xFF

typedef struct _tlvmDebugBreakpoint
{
	struct _tlvmDebugBreakpoint*	m_Next;

	tlvmShort 						m_Address;
	tlvmDebugCallbackFn 			m_Callback;
} tlvmDebugBreakpoint;

tlvmReturn tlvmDebugCheck(tlvmContext* context);

#endif/*TLVM_DEBUG*/

#endif/*__TLVM_DEBUG_INTERNAL_H__*/