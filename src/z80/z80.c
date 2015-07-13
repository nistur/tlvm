#ifdef  TLVM_HAS_Z80
#include "tlvm_internal.h"

tlvmProcessorData_Z80 g_Z80Data;

tlvmReturn tlvmZ80Init(tlvmContext** context)
{
    TLVM_NULL_CHECK(context, NO_CONTEXT);
    
    tlvmContext_Z80* cpu = tlvmMalloc(tlvmContext_Z80);
    *context = &cpu->m_Header;
    
    if(g_Z80Data.m_Header.m_ProcessorID == 0)
        tlvmZ80SetupData();
 

    TLVM_RETURN_CODE(SUCCESS);
}

tlvmReturn tlvmAddZ80Instructions(tlvmInstruction* instructionSet)
{
    TLVM_RETURN_CODE(SUCCESS);
}

void tlvmZ80SetupData()
{
    g_Z80Data.m_Header.m_ProcessorID = TLVM_CPU_Z80;

    tlvmAdd8080Instructions(g_Z80Data.m_InstructionSet);
    tlvmAddZ80Instructions(g_Z80Data.m_InstructionSet);
    
    g_Z80Data.m_Header.m_InstructionSet = g_Z80Data.m_InstructionSet;
}


#endif/*TLVM_HAS_Z80*/
