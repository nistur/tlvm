#ifdef  TLVM_HAS_8080
#include "tlvm_internal.h"

tlvmReturn tlvmROT(tlvmContext* context, tlvmByte* cycles)
{
    if(context == NULL)
        TLVM_RETURN_CODE(NO_CONTEXT);
    TLVM_GET_OP(operand,0);
    
    tlvmShort acc = (tlvmShort)context->m_Registers[TLVM_REG_A];

    if(operand == TLVM_RLC)
    {
        acc <<= 1;
        if(acc & (1<<8))
        {
            acc |= 1;
            TLVM_FLAG_SET(C);
        }
        else
        {
            TLVM_FLAG_UNSET(C);
        }
    }
    else if(operand == TLVM_RRC)
    {
        if(acc & 1)
        {
            acc |= 1<<8;
            TLVM_FLAG_SET(C);
        }
        else
        {
            TLVM_FLAG_UNSET(C);
        }
        acc >>= 1;
    }
    else if(operand == TLVM_RAL)
    {
        acc <<= 1;
        if(TLVM_FLAG_ISSET(C))
            acc |= 1;
        TLVM_FLAG_SET_IF(acc > 0xFF, C);
    }
    else if(operand == TLVM_RAR)
    {
        if(TLVM_FLAG_ISSET(C))
            acc |= 1<<8;
        TLVM_FLAG_SET_IF(acc & 1, C);
        acc >>= 1;
    }

    context->m_Registers[TLVM_REG_A] = (tlvmByte)(acc & 0xFF);

    // size of instruction = 1
    context->m_ProgramCounter += 1;
    if(cycles)
        *cycles = 4;
    TLVM_RETURN_CODE(SUCCESS);
}

#endif/*TLVM_HAS_8080*/
