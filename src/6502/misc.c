#ifdef  TLVM_HAS_6502
#include "tlvm_internal.h"

tlvmReturn tlvm6502NOP(tlvmContext* context, tlvmByte* cycles)
{
    TLVM_NULL_CHECK(context, NO_CONTEXT);
    
    context->m_ProgramCounter += 1;
    if(cycles)
        *cycles = 2;
    
    TLVM_RETURN_CODE(SUCCESS);
}

tlvmReturn tlvm6502BRK(tlvmContext* context, tlvmByte* cycles)
{
    TLVM_NULL_CHECK(context, NO_CONTEXT);

    context->m_ProgramCounter += 2;

    TLVM_GET_MEMORY_16(interrupt, 0xFFFE);

    TLVM_PUSH_PC(interrupt);
    TLVM_STACK_PUSH(TLVM_REGISTER(TLVM_6502_REG_F));

    TLVM_FLAG_SET(B, 6502);

    if(cycles)
        *cycles = 7;

    TLVM_RETURN_CODE(SUCCESS);
}

tlvmReturn tlvm6502RTI(tlvmContext* context, tlvmByte* cycles)
{
    TLVM_NULL_CHECK(context, NO_CONTEXT);

    TLVM_STACK_POP(TLVM_REGISTER(TLVM_6502_REG_F));
    TLVM_POP_PC();

    if(cycles)
        *cycles = 6;

    TLVM_RETURN_CODE(SUCCESS);
}

#endif/*TLVM_HAS_6502*/
