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

tlvmReturn tlvmINX  (tlvmContext* context, tlvmByte* cycles)
{
    TLVM_NULL_CHECK(context, NO_CONTEXT);

    TLVM_GET_OP(opcode, 0);

    switch(opcode)
    {
    case TLVM_INX_B:
        {
            tlvmShort val = TLVM_GET_16BIT(TLVM_REG_B, TLVM_REG_C);
            TLVM_SET_16BIT(TLVM_REG_B, TLVM_REG_C, val + 1);
        }
    break;
    case TLVM_INX_D:
        {
            tlvmShort val = TLVM_GET_16BIT(TLVM_REG_D, TLVM_REG_E);
            TLVM_SET_16BIT(TLVM_REG_D, TLVM_REG_E, val + 1);
        }
    break;
    case TLVM_INX_H:
        {
            tlvmShort val = TLVM_GET_16BIT(TLVM_REG_H, TLVM_REG_L);
            TLVM_SET_16BIT(TLVM_REG_H, TLVM_REG_L, val + 1);
        }
    break;
    case TLVM_INX_SP:
        context->m_StackPointer++;
    break;
    }

    // size of instruction    = 1
    context->m_ProgramCounter += 1;
    if(cycles)
        *cycles = 5;

    TLVM_RETURN_CODE(SUCCESS);

}

tlvmReturn tlvmDCX  (tlvmContext* context, tlvmByte* cycles)
{
    TLVM_NULL_CHECK(context, NO_CONTEXT);

    TLVM_GET_OP(opcode, 0);

    switch(opcode)
    {
    case TLVM_DCX_B:
    {
        tlvmShort val = TLVM_GET_16BIT(TLVM_REG_B, TLVM_REG_C);
        TLVM_SET_16BIT(TLVM_REG_B, TLVM_REG_C, val - 1);
    }
    break;
    case TLVM_DCX_D:
    {
        tlvmShort val = TLVM_GET_16BIT(TLVM_REG_D, TLVM_REG_E);
        TLVM_SET_16BIT(TLVM_REG_D, TLVM_REG_E, val - 1);
    }
    break;
    case TLVM_DCX_H:
    {
        tlvmShort val = TLVM_GET_16BIT(TLVM_REG_H, TLVM_REG_L);
        TLVM_SET_16BIT(TLVM_REG_H, TLVM_REG_L, val - 1);
    }
    break;
    case TLVM_DCX_SP:
        context->m_StackPointer--;
    break;
    }

    // size of instruction    = 1
    context->m_ProgramCounter += 1;
    if(cycles)
        *cycles = 5;

    TLVM_RETURN_CODE(SUCCESS);

}

tlvmReturn tlvmDAD(tlvmContext* context, tlvmByte* cycles)
{
    TLVM_NULL_CHECK(context, NO_CONTEXT);

    TLVM_GET_OP(opcode, 0);

    tlvmLong val = (tlvmLong)TLVM_GET_16BIT(TLVM_REG_H, TLVM_REG_L);

    switch(opcode)
    {
    case TLVM_DAD_B:
        val += (tlvmLong)TLVM_GET_16BIT(TLVM_REG_B, TLVM_REG_C);
    break;
    case TLVM_DAD_D:
        val += (tlvmLong)TLVM_GET_16BIT(TLVM_REG_D, TLVM_REG_E);
    break;
    case TLVM_DAD_H:
        val += (tlvmLong)TLVM_GET_16BIT(TLVM_REG_H, TLVM_REG_L);
    break;
    case TLVM_DAD_SP:
        val += (tlvmLong)context->m_StackPointer;
    break;
    }

    TLVM_SET_16BIT(TLVM_REG_H, TLVM_REG_L, (tlvmShort)(val & 0xFFFF));

    TLVM_FLAG_SET_IF(val ^ 0xFFFF, C, 8080);
    TLVM_FLAG_SET_IF(val & 0xFFFF, Z, 8080);

    // size of instruction    = 1
    context->m_ProgramCounter += 1;
    if(cycles)
        *cycles = 10;

    TLVM_RETURN_CODE(SUCCESS);
}
#endif/*TLVM_HAS_8080*/
