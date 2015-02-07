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

tlvmReturn tlvmDebugReset(tlvmContext* context);

#endif/*TLVM_DEBUG*/

#endif/*__TLVM_DEBUG_INTERNAL_H__*/