#ifdef  TLVM_HAS_8080
#include "tlvm_internal.h"

tlvmReturn tlvmADD(tlvmContext* context, tlvmByte* cycles)
{
    if(context == NULL)
        TLVM_RETURN_CODE(NO_CONTEXT);

    TLVM_GET_OP(opcode, 0);

    tlvmByte* src = NULL;

    tlvmShort carry = 0;
    switch(opcode)
    {
    case TLVM_ADC_B:
        carry = TLVM_FLAG_ISSET(C) ? 1 : 0;
    case TLVM_ADD_B:
        src = &context->m_Registers[TLVM_REG_B];
    break;
    case TLVM_ADC_C:
        carry = TLVM_FLAG_ISSET(C) ? 1 : 0;
    case TLVM_ADD_C:
        src = &context->m_Registers[TLVM_REG_C];
    break;
    case TLVM_ADC_D:
        carry = TLVM_FLAG_ISSET(C) ? 1 : 0;
    case TLVM_ADD_D:
        src = &context->m_Registers[TLVM_REG_D];
    break;
    case TLVM_ADC_E:
        carry = TLVM_FLAG_ISSET(C) ? 1 : 0;
    case TLVM_ADD_E:
        src = &context->m_Registers[TLVM_REG_E];
    break;
    case TLVM_ADC_H:
        carry = TLVM_FLAG_ISSET(C) ? 1 : 0;
    case TLVM_ADD_H:
        src = &context->m_Registers[TLVM_REG_H];
    break;
    case TLVM_ADC_L:
        carry = TLVM_FLAG_ISSET(C) ? 1 : 0;
    case TLVM_ADD_L:
        src = &context->m_Registers[TLVM_REG_L];
    break;
    case TLVM_ADC_M:
        carry = TLVM_FLAG_ISSET(C) ? 1 : 0;
    case TLVM_ADD_M:
        {
            tlvmShort addr = TLVM_GET_16BIT(TLVM_REG_H, TLVM_REG_L);
            src = tlvmGetMemory(context, addr, TLVM_FLAG_READ);
        }
    break;
    case TLVM_ADC_A:
        carry = TLVM_FLAG_ISSET(C) ? 1 : 0;
    case TLVM_ADD_A:
        src = &context->m_Registers[TLVM_REG_A];
    break;
    }

    if(src == NULL)
        TLVM_RETURN_CODE(INVALID_INPUT);

    static tlvmByte mask = 1<<3;
    TLVM_FLAG_SET_IF(*src & mask && context->m_Registers[TLVM_REG_A] & mask, H);


    tlvmShort res = (tlvmShort)context->m_Registers[TLVM_REG_A] + (tlvmShort)*src + carry;
    TLVM_SET_FLAGS(res);
    context->m_Registers[TLVM_REG_A] = (tlvmByte)(res & 0xFF);

    // size of instruction    = 1
    context->m_ProgramCounter += 1;
    if(cycles)
        *cycles = 4;

    TLVM_RETURN_CODE(SUCCESS);
}

tlvmReturn tlvmADI(tlvmContext* context, tlvmByte* cycles)
{
    if(context == NULL)
        TLVM_RETURN_CODE(NO_CONTEXT);

    TLVM_GET_OP(operand, 0);
    TLVM_GET_OP(op1,     1);

    tlvmShort carry = 0;
    if(operand == TLVM_ACI)
        carry = TLVM_FLAG_ISSET(C) ? 1 : 0;

    static tlvmByte mask = 1<<3;
    TLVM_FLAG_SET_IF(op1 & mask && context->m_Registers[TLVM_REG_A] & mask, H);

    tlvmShort res = (tlvmShort)context->m_Registers[TLVM_REG_A] + (tlvmShort)op1 + carry;
    TLVM_SET_FLAGS(res);
    context->m_Registers[TLVM_REG_A] = (tlvmByte)(res & 0xFF);

    // size of instruction    = 1
    // size of operand        = 1
    context->m_ProgramCounter += 2;
    if(cycles)
        *cycles = 7;

    TLVM_RETURN_CODE(SUCCESS);
}
#endif/*TLVM_HAS_8080*/