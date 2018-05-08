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

tlvmReturn tlvmSUB(tlvmContext* context, tlvmByte* cycles)
{
    TLVM_NULL_CHECK(context, NO_CONTEXT);

    TLVM_GET_OP(opcode, 0);

    tlvmByte* src = NULL;

    tlvmShort borrow = 0;
    switch(opcode)
    {
    case TLVM_SBB_B:
        borrow = TLVM_FLAG_ISSET(C, 8080) ? 1 : 0;
	FALLTHROUGH;
    case TLVM_SUB_B:
        src = &context->m_Registers[TLVM_8080_REG_B];
    break;
    case TLVM_SBB_C:
        borrow = TLVM_FLAG_ISSET(C, 8080) ? 1 : 0;
	FALLTHROUGH;
    case TLVM_SUB_C:
        src = &context->m_Registers[TLVM_8080_REG_C];
    break;
    case TLVM_SBB_D:
        borrow = TLVM_FLAG_ISSET(C, 8080) ? 1 : 0;
	FALLTHROUGH;
    case TLVM_SUB_D:
        src = &context->m_Registers[TLVM_8080_REG_D];
    break;
    case TLVM_SBB_E:
        borrow = TLVM_FLAG_ISSET(C, 8080) ? 1 : 0;
	FALLTHROUGH;
    case TLVM_SUB_E:
        src = &context->m_Registers[TLVM_8080_REG_E];
    break;
    case TLVM_SBB_H:
        borrow = TLVM_FLAG_ISSET(C, 8080) ? 1 : 0;
	FALLTHROUGH;
    case TLVM_SUB_H:
        src = &context->m_Registers[TLVM_8080_REG_H];
    break;
    case TLVM_SBB_L:
        borrow = TLVM_FLAG_ISSET(C, 8080) ? 1 : 0;
	FALLTHROUGH;
    case TLVM_SUB_L:
        src = &context->m_Registers[TLVM_8080_REG_L];
    break;
    case TLVM_SBB_M:
        borrow = TLVM_FLAG_ISSET(C, 8080) ? 1 : 0;
	FALLTHROUGH;
    case TLVM_SUB_M:
        {
            tlvmShort addr = TLVM_GET_16BIT(TLVM_8080_REG_H, TLVM_8080_REG_L);
            src = tlvmGetMemory(context, addr, TLVM_FLAG_READ);
        }
    break;
    case TLVM_SBB_A:
        borrow = TLVM_FLAG_ISSET(C, 8080) ? 1 : 0;
	FALLTHROUGH;
    case TLVM_SUB_A:
        src = &context->m_Registers[TLVM_8080_REG_A];
    break;
    }

    TLVM_NULL_CHECK(src, INVALID_INPUT);

    tlvmShort res = (tlvmShort)context->m_Registers[TLVM_8080_REG_A] - (tlvmShort)*src - borrow;
    TLVM_SET_FLAGS(res, 8080);
    context->m_Registers[TLVM_8080_REG_A] = (tlvmByte)(res & 0xFF);

    // size of instruction    = 1
    context->m_ProgramCounter += 1;
    if(cycles)
        *cycles = 4;

    TLVM_RETURN_CODE(SUCCESS);
}

tlvmReturn tlvmSUI(tlvmContext* context, tlvmByte* cycles)
{
    TLVM_NULL_CHECK(context, NO_CONTEXT);

    TLVM_GET_OP(operand, 0);
    TLVM_GET_OP(op1,     1);

    tlvmShort borrow = 0;
    if(operand == TLVM_SBI)
        borrow = TLVM_FLAG_ISSET(C, 8080) ? 1 : 0;

    tlvmShort res = (tlvmShort)context->m_Registers[TLVM_8080_REG_A] - (tlvmShort)op1 - borrow;
    TLVM_SET_FLAGS(res, 8080);
    context->m_Registers[TLVM_8080_REG_A] = (tlvmByte)(res & 0xFF);


    // size of instruction    = 1
    // size of operand        = 1
    context->m_ProgramCounter += 2;
    if(cycles)
        *cycles = 7;

    TLVM_RETURN_CODE(SUCCESS);
}
#endif/*TLVM_HAS_8080*/
