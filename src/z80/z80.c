#ifdef  TLVM_HAS_Z80
#include "tlvm_internal.h"

tlvmReturn tlvmInitZ80(tlvmContext* context)
{
    if(context == NULL)
        tlvmReturnCode(NO_CONTEXT);

    // make sure we have enough space for instructions
    if(context->m_InstructionSet)
        tlvmFree(context->m_InstructionSet);
    context->m_InstructionSet = tlvmMallocArray(tlvmInstruction, 512);

    // initialise all the 8080 registers
    if(context->m_Registers)
        tlvmFree(context->m_Registers);
    context->m_Registers = tlvmMallocArray(tlvmByte, 8);

    // create default I/O ports
    if(context->m_Ports)
        tlvmFree(context->m_Ports);
    context->m_Ports = tlvmMallocArray(tlvmByte, 255);

    if(tlvmAdd8080Instructions(context) != TLVM_SUCCESS)
        tlvmReturn();

    if(tlvmAddZ80Instructions(context) != TLVM_SUCCESS)
        tlvmReturn();

    tlvmReturnCode(SUCCESS);
}

tlvmReturn tlvmAddZ80Instructions(tlvmContext* context)
{
}

#endif/*TLVM_HAS_Z80*/