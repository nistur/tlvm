#ifdef  TLVM_HAS_8080
#include "tlvm_internal.h"

tlvmReturn tlvmINX  (tlvmContext* context, tlvmByte* cycles)
{
    if(context == NULL)
        TLVM_RETURN_CODE(NO_CONTEXT);

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
    if(context == NULL)
        TLVM_RETURN_CODE(NO_CONTEXT);

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
    if(context == NULL)
        TLVM_RETURN_CODE(NO_CONTEXT);

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

    TLVM_FLAG_SET_IF(val ^ 0xFFFF, C);
    TLVM_FLAG_SET_IF(val & 0xFFFF, Z);

    // size of instruction    = 1
    context->m_ProgramCounter += 1;
    if(cycles)
        *cycles = 10;

    TLVM_RETURN_CODE(SUCCESS);
}
#endif/*TLVM_HAS_8080*/
