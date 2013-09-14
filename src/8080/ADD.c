#include "tlvm_internal.h"

tlvmReturn tlvmADD(tlvmContext* context, tlvmByte* cycles)
{
    if(context == NULL)
        tlvmReturnCode(NO_CONTEXT);

    TLVM_GET_OP(opcode, 0);

    tlvmByte* src = NULL;

    switch(opcode)
    {
    case TLVM_ADD_B:
        src = &context->m_Registers[TLVM_REG_B];
    break;
    case TLVM_ADD_C:
        src = &context->m_Registers[TLVM_REG_C];
    break;
    case TLVM_ADD_D:
        src = &context->m_Registers[TLVM_REG_D];
    break;
    case TLVM_ADD_E:
        src = &context->m_Registers[TLVM_REG_E];
    break;
    case TLVM_ADD_H:
        src = &context->m_Registers[TLVM_REG_H];
    break;
    case TLVM_ADD_L:
        src = &context->m_Registers[TLVM_REG_L];
    break;
    case TLVM_ADD_M:
        {
            tlvmShort addr = TLVM_GET_16BIT(TLVM_REG_H, TLVM_REG_L);
            src = tlvmGetMemory(context, addr, TLVM_FLAG_READ);
        }
    break;
    case TLVM_ADD_A:
        src = &context->m_Registers[TLVM_REG_A];
    break;
    }

    if(src == NULL)
        tlvmReturnCode(INVALID_INPUT);

    tlvmShort res = (tlvmShort)context->m_Registers[TLVM_REG_A] + (tlvmShort)*src;
    TLVM_SET_FLAGS(res);
    context->m_Registers[TLVM_REG_A] = (tlvmByte)(res & 0xFF);

    // size of instruction    = 1
    context->m_ProgramCounter += 1;
    if(cycles)
        *cycles = 1;

    tlvmReturnCode(SUCCESS);
}

tlvmReturn tlvmADI(tlvmContext* context, tlvmByte* cycles)
{
    if(context == NULL)
        tlvmReturnCode(NO_CONTEXT);

    TLVM_GET_OP(op1, 1);

    tlvmShort res = (tlvmShort)context->m_Registers[TLVM_REG_A] + (tlvmShort)op1;
    TLVM_SET_FLAGS(res);
    context->m_Registers[TLVM_REG_A] = (tlvmByte)(res & 0xFF);

    // size of instruction    = 1
    // size of operand        = 1
    context->m_ProgramCounter += 2;
    if(cycles)
        *cycles = 2;

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
