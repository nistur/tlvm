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

#ifdef  TLVM_HAS_8080
#include "tlvm_internal.h"

tlvmReturn tlvmOUT(tlvmContext* context, tlvmByte* cycles)
{
	if(context == NULL)
		TLVM_RETURN_CODE(NO_CONTEXT);

	TLVM_GET_OP(dest, 1);

	context->m_Ports[dest] = context->m_Registers[TLVM_REG_A];

    // size of instruction    = 1
    // size of operand        = 1
    context->m_ProgramCounter += 2;
    if(cycles)
    	*cycles =10;

	tlvm8080data* data = (tlvm8080data*)context->m_ProcessorData;
	if(data != NULL && data->m_IOCallback != NULL)
		data->m_IOCallback(context, dest);

	TLVM_RETURN_CODE(SUCCESS);
}

tlvmReturn tlvmIN(tlvmContext* context, tlvmByte* cycles)
{
	if(context == NULL)
		TLVM_RETURN_CODE(NO_CONTEXT);

	TLVM_GET_OP(dest, 1);

	context->m_Registers[TLVM_REG_A] = context->m_Ports[dest];

    // size of instruction    = 1
    // size of operand        = 1
    context->m_ProgramCounter += 2;
    if(cycles)
    	*cycles =10;

	TLVM_RETURN_CODE(SUCCESS);
}
#endif/*TLVM_HAS_8080*/