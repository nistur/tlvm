#include "tlvm_internal.h"

tlvmReturn tlvmSUB(tlvmContext* context, tlvmByte* cycles)
{
    if(context == NULL)
        tlvmReturnCode(NO_CONTEXT);

    TLVM_GET_OP(opcode, 0);

    tlvmByte* src = NULL;

    tlvmShort borrow = 0;
    switch(opcode)
    {
    case TLVM_SBB_B:
        borrow = TLVM_FLAG_ISSET(C) ? 1 : 0;
    case TLVM_SUB_B:
        src = &context->m_Registers[TLVM_REG_B];
    break;
    case TLVM_SBB_C:
        borrow = TLVM_FLAG_ISSET(C) ? 1 : 0;
    case TLVM_SUB_C:
        src = &context->m_Registers[TLVM_REG_C];
    break;
    case TLVM_SBB_D:
        borrow = TLVM_FLAG_ISSET(C) ? 1 : 0;
    case TLVM_SUB_D:
        src = &context->m_Registers[TLVM_REG_D];
    break;
    case TLVM_SBB_E:
        borrow = TLVM_FLAG_ISSET(C) ? 1 : 0;
    case TLVM_SUB_E:
        src = &context->m_Registers[TLVM_REG_E];
    break;
    case TLVM_SBB_H:
        borrow = TLVM_FLAG_ISSET(C) ? 1 : 0;
    case TLVM_SUB_H:
        src = &context->m_Registers[TLVM_REG_H];
    break;
    case TLVM_SBB_L:
        borrow = TLVM_FLAG_ISSET(C) ? 1 : 0;
    case TLVM_SUB_L:
        src = &context->m_Registers[TLVM_REG_L];
    break;
    case TLVM_SBB_M:
        borrow = TLVM_FLAG_ISSET(C) ? 1 : 0;
    case TLVM_SUB_M:
        {
            tlvmShort addr = TLVM_GET_16BIT(TLVM_REG_H, TLVM_REG_L);
            src = tlvmGetMemory(context, addr, TLVM_FLAG_READ);
        }
    break;
    case TLVM_SBB_A:
        borrow = TLVM_FLAG_ISSET(C) ? 1 : 0;
    case TLVM_SUB_A:
        src = &context->m_Registers[TLVM_REG_A];
    break;
    }

    if(src == NULL)
        tlvmReturnCode(INVALID_INPUT);

    tlvmShort res = (tlvmShort)context->m_Registers[TLVM_REG_A] - (tlvmShort)*src - borrow;
    TLVM_SET_FLAGS(res);
    context->m_Registers[TLVM_REG_A] = (tlvmByte)(res & 0xFF);

    // size of instruction    = 1
    context->m_ProgramCounter += 1;
    if(cycles)
        *cycles = 4;

    tlvmReturnCode(SUCCESS);
}

tlvmReturn tlvmSUI(tlvmContext* context, tlvmByte* cycles)
{
    if(context == NULL)
        tlvmReturnCode(NO_CONTEXT);

    TLVM_GET_OP(operand, 0);
    TLVM_GET_OP(op1,     1);

    tlvmShort borrow = 0;
    if(operand == TLVM_ACI)
        borrow = TLVM_FLAG_ISSET(C) ? 1 : 0;

    tlvmShort res = (tlvmShort)context->m_Registers[TLVM_REG_A] - (tlvmShort)op1 - borrow;
    TLVM_SET_FLAGS(res);
    context->m_Registers[TLVM_REG_A] = (tlvmByte)(res & 0xFF);


    // size of instruction    = 1
    // size of operand        = 1
    context->m_ProgramCounter += 2;
    if(cycles)
        *cycles = 7;

    tlvmReturnCode(SUCCESS);
}
