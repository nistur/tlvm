#ifdef  TLVM_HAS_8080
#include "tlvm_internal.h"

tlvmReturn tlvmCMP(tlvmContext* context, tlvmByte* cycles)
{
    if(context == NULL)
        TLVM_RETURN_CODE(NO_CONTEXT);

    TLVM_GET_OP(opcode, 0);

    tlvmByte* src = NULL;

    switch(opcode)
    {
    case TLVM_CMP_B:
        src = &context->m_Registers[TLVM_REG_B];
    break;
    case TLVM_CMP_C:
        src = &context->m_Registers[TLVM_REG_C];
    break;
    case TLVM_CMP_D:
        src = &context->m_Registers[TLVM_REG_D];
    break;
    case TLVM_CMP_E:
        src = &context->m_Registers[TLVM_REG_E];
    break;
    case TLVM_CMP_H:
        src = &context->m_Registers[TLVM_REG_H];
    break;
    case TLVM_CMP_L:
        src = &context->m_Registers[TLVM_REG_L];
    break;
    case TLVM_CMP_M:
        {
            tlvmShort addr = TLVM_GET_16BIT(TLVM_REG_H, TLVM_REG_L);
            src = tlvmGetMemory(context, addr, TLVM_FLAG_READ);
        }
    break;
    case TLVM_CMP_A:
        src = &context->m_Registers[TLVM_REG_A];
    break;
    }

    if(src == NULL)
        TLVM_RETURN_CODE(INVALID_INPUT);

    tlvmShort res = (tlvmShort)context->m_Registers[TLVM_REG_A] - (tlvmShort)*src;
    TLVM_SET_FLAGS(res);

    // size of instruction    = 1
    context->m_ProgramCounter += 1;
    if(cycles)
        *cycles = 4;

    TLVM_RETURN_CODE(SUCCESS);
}

tlvmReturn tlvmCPI(tlvmContext* context, tlvmByte* cycles)
{
    if(context == NULL)
        TLVM_RETURN_CODE(NO_CONTEXT);

    TLVM_GET_OP(op1, 1);

    tlvmShort res = (tlvmShort)context->m_Registers[TLVM_REG_A] - (tlvmShort)op1;
    TLVM_SET_FLAGS(res);

    // size of instruction    = 1
    // size of operand        = 1
    context->m_ProgramCounter += 2;
    if(cycles)
        *cycles = 7;

    TLVM_RETURN_CODE(SUCCESS);
}
#endif/*TLVM_HAS_8080*/