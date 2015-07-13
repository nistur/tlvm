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

tlvmReturn tlvmPUSH(tlvmContext* context, tlvmByte* cycles)
{
    TLVM_NULL_CHECK(context, NO_CONTEXT);

	TLVM_GET_OP(opcode, 0);

	tlvmByte srcHi = 0;
	tlvmByte srcLo = 0;
	switch(opcode)
	{
	case TLVM_PUSH_B:
    	srcHi = context->m_Registers[TLVM_8080_REG_B];
    	srcLo = context->m_Registers[TLVM_8080_REG_C];
	break;
	case TLVM_PUSH_D:
    	srcHi = context->m_Registers[TLVM_8080_REG_D];
    	srcLo = context->m_Registers[TLVM_8080_REG_E];
	break;
	case TLVM_PUSH_H:
    	srcHi = context->m_Registers[TLVM_8080_REG_H];
    	srcLo = context->m_Registers[TLVM_8080_REG_L];
	break;
	case TLVM_PUSH_PSW:
    	srcHi = context->m_Registers[TLVM_8080_REG_A];
    	srcLo = context->m_Registers[TLVM_8080_REG_F];
	break;
	}
	TLVM_STACK_PUSH(srcHi);
	TLVM_STACK_PUSH(srcLo);

	// size of instruction    = 1
	context->m_ProgramCounter += 1;
    if(cycles)
    	*cycles = 11;

	TLVM_RETURN_CODE(SUCCESS);
}

tlvmReturn tlvmPOP(tlvmContext* context, tlvmByte* cycles)
{
    TLVM_NULL_CHECK(context, NO_CONTEXT);

	TLVM_GET_OP(opcode, 0);

	tlvmByte* dstHi = NULL;
	tlvmByte* dstLo = NULL;
	switch(opcode)
	{
	case TLVM_POP_B:
    	dstHi = &context->m_Registers[TLVM_8080_REG_B];
    	dstLo = &context->m_Registers[TLVM_8080_REG_C];
	break;
	case TLVM_POP_D:
    	dstHi = &context->m_Registers[TLVM_8080_REG_D];
    	dstLo = &context->m_Registers[TLVM_8080_REG_E];
	break;
	case TLVM_POP_H:
    	dstHi = &context->m_Registers[TLVM_8080_REG_H];
    	dstLo = &context->m_Registers[TLVM_8080_REG_L];
	break;
	case TLVM_POP_PSW:
    	dstHi = &context->m_Registers[TLVM_8080_REG_A];
    	dstLo = &context->m_Registers[TLVM_8080_REG_F];
	break;
	}

	TLVM_STACK_POP(*dstLo);
	TLVM_STACK_POP(*dstHi);

    // size of instruction    = 1
    context->m_ProgramCounter += 1;
    if(cycles)
        *cycles = 10;

    TLVM_RETURN_CODE(SUCCESS);
}

tlvmReturn tlvmSPHL(tlvmContext* context, tlvmByte* cycles)
{
    TLVM_NULL_CHECK(context, NO_CONTEXT);

    context->m_StackPointer = TLVM_GET_16BIT(TLVM_8080_REG_H, TLVM_8080_REG_L);
    // size of instruction    = 1
    context->m_ProgramCounter += 1;
    if(cycles)
        *cycles =5;

    TLVM_RETURN_CODE(SUCCESS);
}

tlvmReturn tlvmXTHL(tlvmContext* context, tlvmByte* cycles)
{
    TLVM_NULL_CHECK(context, NO_CONTEXT);

	tlvmByte* dstHi = tlvmGetMemory(context, context->m_StackPointer+1, TLVM_FLAG_WRITE);
	tlvmByte* dstLo = tlvmGetMemory(context, context->m_StackPointer+0, TLVM_FLAG_WRITE);

    TLVM_NULL_CHECK(dstHi, INVALID_INPUT);
    TLVM_NULL_CHECK(dstLo, INVALID_INPUT);

	tlvmByte tmpHi = *dstHi;
	tlvmByte tmpLo = *dstLo;

	*dstHi = context->m_Registers[TLVM_8080_REG_H];
	*dstLo = context->m_Registers[TLVM_8080_REG_L];

	context->m_Registers[TLVM_8080_REG_H] = tmpHi;
	context->m_Registers[TLVM_8080_REG_L] = tmpLo;

	// size of instruction    = 1
	context->m_ProgramCounter += 1;
    if(cycles)
    	*cycles =18;

	TLVM_RETURN_CODE(SUCCESS);
}

#endif/*TLVM_HAS_8080*/
