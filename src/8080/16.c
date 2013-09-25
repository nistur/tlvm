#ifdef  TLVM_HAS_8080
#include "tlvm_internal.h"

tlvmReturn tlvmINX  (tlvmContext* context, tlvmByte* cycles)
{
    if(context == NULL)
        tlvmReturnCode(NO_CONTEXT);

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

    tlvmReturnCode(SUCCESS);

}

tlvmReturn tlvmDCX  (tlvmContext* context, tlvmByte* cycles)
{
    if(context == NULL)
        tlvmReturnCode(NO_CONTEXT);

    TLVM_GET_OP(opcode, 0);

    switch(opcode)
    {
    case TLVM_DCX_B:
        TLVM_SET_16BIT(TLVM_REG_B, TLVM_REG_C, TLVM_GET_16BIT(TLVM_REG_B, TLVM_REG_C) - 1);
    break;
    case TLVM_DCX_D:
        TLVM_SET_16BIT(TLVM_REG_D, TLVM_REG_E, TLVM_GET_16BIT(TLVM_REG_D, TLVM_REG_E) - 1);
    break;
    case TLVM_DCX_H:
        TLVM_SET_16BIT(TLVM_REG_H, TLVM_REG_L, TLVM_GET_16BIT(TLVM_REG_H, TLVM_REG_L) - 1);
    break;
    case TLVM_DCX_SP:
        context->m_StackPointer--;
    break;
    }

    // size of instruction    = 1
    context->m_ProgramCounter += 1;
    if(cycles)
        *cycles = 5;

    tlvmReturnCode(SUCCESS);

}

tlvmReturn tlvmDAD(tlvmContext* context, tlvmByte* cycles)
{
    if(context == NULL)
        tlvmReturnCode(NO_CONTEXT);

    TLVM_GET_OP(opcode, 0);

    tlvmShort val = TLVM_GET_16BIT(TLVM_REG_H, TLVM_REG_L);

    switch(opcode)
    {
    case TLVM_DAD_B:
        val += TLVM_GET_16BIT(TLVM_REG_B, TLVM_REG_C);
    break;
    case TLVM_DAD_D:
        val += TLVM_GET_16BIT(TLVM_REG_D, TLVM_REG_E);
    break;
    case TLVM_DAD_H:
        val += TLVM_GET_16BIT(TLVM_REG_H, TLVM_REG_L);
    break;
    case TLVM_DAD_SP:
        val += context->m_StackPointer;
    break;
    }

    TLVM_SET_16BIT(TLVM_REG_H, TLVM_REG_L, val);

    // size of instruction    = 1
    context->m_ProgramCounter += 1;
    if(cycles)
        *cycles = 10;

    tlvmReturnCode(SUCCESS);
}
#endif/*TLVM_HAS_8080*/