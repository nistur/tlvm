#ifdef  TLVM_HAS_8080
#include "tlvm_internal.h"

tlvmReturn tlvmRST(tlvmContext* context, tlvmByte* cycles)
{
    if(context == NULL)
        tlvmReturnCode(NO_CONTEXT);

    TLVM_GET_OP(opcode, 0);

    // increment the program counter first so if/when we return,
    // we don't hit the interrupt again
    // size of instruction    = 1
    context->m_ProgramCounter += 1;

    // push the program counter
    tlvmByte pcLo = (tlvmByte)(context->m_ProgramCounter & 0xFF);
    tlvmByte pcHi = (tlvmByte)(context->m_ProgramCounter >> 8);

    TLVM_STACK_PUSH(pcHi);
    TLVM_STACK_PUSH(pcLo);

    // which interrupt are we hitting?
    tlvmShort addr = 0x08;
    switch(opcode)
    {
    case TLVM_RST_0:
        addr *= 0;
    break;
    case TLVM_RST_1:
        addr *= 1;
    break;
    case TLVM_RST_2:
        addr *= 2;
    break;
    case TLVM_RST_3:
        addr *= 3;
    break;
    case TLVM_RST_4:
        addr *= 4;
    break;
    case TLVM_RST_5:
        addr *= 5;
    break;
    case TLVM_RST_6:
        addr *= 6;
    break;
    case TLVM_RST_7:
        addr *= 7;
    break;
    }

    context->m_ProgramCounter = addr;
    if(cycles)
        *cycles =11;

    tlvmReturnCode(SUCCESS);
}

// right now these do nothing... do they disable the RST instructions?
// or something else?
tlvmReturn tlvmEI(tlvmContext* context, tlvmByte* cycles)
{
    if(context == NULL)
        tlvmReturnCode(NO_CONTEXT);

    // size of instruction    = 1
    context->m_ProgramCounter += 1;
    if(cycles)
        *cycles =4;

    tlvmReturnCode(SUCCESS);
}

tlvmReturn tlvmDI(tlvmContext* context, tlvmByte* cycles)
{
    if(context == NULL)
        tlvmReturnCode(NO_CONTEXT);

    // size of instruction    = 1
    context->m_ProgramCounter += 1;
    if(cycles)
        *cycles =4;

    tlvmReturnCode(SUCCESS);
}
#endif/*TLVM_HAS_8080*/