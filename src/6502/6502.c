#ifdef  TLVM_HAS_6502
#include "tlvm_internal.h"

tlvmProcessorData_6502 g_6502Data;

tlvmReturn tlvm6502Init(tlvmContext* context)
{
    TLVM_NULL_CHECK(context, NO_CONTEXT);

    // initialise all the 6502 registers
    if(context->m_Registers)
        tlvmFree(context->m_Registers);
    context->m_Registers = tlvmMallocArray(tlvmByte, 8);

    // create default I/O ports
    if(context->m_Ports)
        tlvmFree(context->m_Ports);

    if(context->m_ProcessorData)
        tlvmFree(context->m_ProcessorData);
    context->m_ProcessorData = (tlvmProcessorData*)tlvmMalloc(tlvm6502data);

    // 6502 stack pointer is hard wired to range 0x0100 -> 0x01FF
    context->m_Registers[TLVM_6502_REG_SP_H] = 0x01;

    if(g_6502Data.m_Header.m_ProcessorID == 0)
        tlvm6502SetupData();

    TLVM_RETURN_CODE(SUCCESS);
}

void tlvm6502SetupData();
{
    g_6502Data.m_Header.m_ProcessorID = TLVM_CPU_6502;
    g_6502Data.m_Header.m_InstructionSet = g_6502Data.m_InstructionSet;

    TLVM_INSTRUCTION_ADD( g_6502Data.m_InstructionSet, 6502, NOP);
}

#endif/*TLVM_HAS_6502*/
