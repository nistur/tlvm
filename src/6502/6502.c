#ifdef  TLVM_HAS_6502
#include "tlvm_internal.h"

tlvmReturn tlvm6502Init(tlvmContext* context)
{
    if(context == NULL)
        tlvmReturnCode(NO_CONTEXT);

    // make sure we have enough space for instructions
    if(context->m_InstructionSet)
        tlvmFree(context->m_InstructionSet);
    context->m_InstructionSet = tlvmMallocArray(tlvmInstruction, 256);

    // initialise all the 6502 registers
    if(context->m_Registers)
        tlvmFree(context->m_Registers);
    context->m_Registers = tlvmMallocArray(tlvmByte, 5);

    // create default I/O ports
    if(context->m_Ports)
        tlvmFree(context->m_Ports);

    if(context->m_ProcessorData)
        tlvmFree(context->m_ProcessorData);
    context->m_ProcessorData = (tlvmProcessorData*)tlvmMalloc(tlvm6502data);

    // 6502 stack pointer is hard wired to range 0x0100 -> 0x01FF
    context->m_Registers[TLVM_6502_REG_SP_H] = 0x01;

    return tlvmAdd6502Instructions(context);
}

tlvmReturn tlvmAdd6502Instructions(tlvmContext* context)
{
    if(context == NULL)
        tlvmReturnCode(NO_CONTEXT);

    context->m_InstructionSet[TLVM_6502_NOP] = tlvm6502NOP;

    tlvmReturnCode(SUCCESS);
}

#endif/*TLVM_HAS_6502*/