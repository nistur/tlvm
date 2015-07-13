#ifdef  TLVM_HAS_6502
#include "tlvm_internal.h"


tlvmReturn tlvm6502NOP(tlvmContext* context, tlvmByte* cycles)
{
    TLVM_NULL_CHECK(context, NO_CONTEXT);
    
    context->m_ProgramCounter += 1;
    if(cycles)
        *cycles = 2;
    
    tlvmReturnCode(SUCCESS);
}

#endif/*TLVM_HAS_6502*/
