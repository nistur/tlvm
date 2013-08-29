#include "tlvm_internal.h"

tlvmReturn tlvmClearContext(tlvmContext* context)
{
    context->m_Memory = NULL;
    context->m_MemorySize = 0;

    context->m_Program = NULL;
    context->m_ProgramCounter = 0;
    context->m_Bootloader = NULL;

    memset(context->m_InstructionSet, 0, sizeof(tlvmInstruction*) * TLVM_OPCODE_MAX);

    tlvmReturnCode(SUCCESS);
}

tlvmReturn tlvmInitCore(tlvmContext* context);

tlvmReturn tlvmInitContext(tlvmContext** context)
{
    if(context == NULL)
       tlvmReturnCode(NO_CONTEXT);

    *context = tlvmMalloc(tlvmContext);
    if(tlvmClearContext(*context) != TLVM_SUCCESS)
    {
	   tlvmTerminateContext(context);
       tlvmReturn();
    }

    if(tlvmInitCore(*context) != TLVM_SUCCESS)
        tlvmReturn();

    tlvmReturnCode(SUCCESS);
}

tlvmReturn tlvmTerminateContext(tlvmContext** context)
{
    if(context == NULL || *context == NULL)
	   tlvmReturnCode(NO_CONTEXT);

    if(tlvmClearContext(*context) != TLVM_SUCCESS)
        tlvmReturn();

    tlvmFree(*context);
    *context = 0;
    tlvmReturnCode(SUCCESS);
}

tlvmReturn tlvmSetMemoryBuffer(tlvmContext* context, tlvmByte* memory, tlvmShort size)
{
    if(context == NULL)
        tlvmReturnCode(NO_CONTEXT);
    if(memory == NULL)
        tlvmReturnCode(NO_MEMORY);
    if(size == 0)
        tlvmReturnCode(INVALID_INPUT);

    context->m_Memory = memory;
    context->m_MemorySize = size;

    tlvmReturnCode(SUCCESS);
}

tlvmReturn tlvmLoadBootloader(tlvmContext* context, tlvmByte* bootloader)
{
    if(context == NULL)
        tlvmReturnCode(NO_CONTEXT);
    if(bootloader == NULL)
        tlvmReturnCode(INVALID_INPUT)
    context->m_Bootloader = tlvmMallocArray(tlvmByte, 256);
    tlvmMemcpy(context->m_Bootloader, bootloader, 256);
    context->m_Program = context->m_Bootloader;

    context->m_ProgramCounter = 0;

    tlvmReturnCode(SUCCESS);
}

tlvmReturn tlvmStep(tlvmContext* context)
{
    if(context == NULL)
        tlvmReturnCode(NO_CONTEXT);
    if(context->m_Program == NULL)
        tlvmReturnCode(INVALID_INPUT);

    tlvmByte opcode = context->m_Program[context->m_ProgramCounter];
    if(context->m_InstructionSet[opcode] == NULL)
        tlvmReturnCode(UNKNOWN_INSTRUCTION);
    context->m_InstructionSet[opcode](context);
    tlvmReturn();
}

tlvmReturn tlvmRun(tlvmContext* context)
{
    while(tlvmStep(context) == TLVM_SUCCESS){}
    if(g_tlvmStatus != TLVM_EXIT)
        tlvmReturn();
    tlvmReturnCode(SUCCESS);
}

const char* tlvmError()
{
    if(g_tlvmStatus == -1)
        return "UNIMPLEMENTED";
    return g_tlvmStatusMessages[g_tlvmStatus];
}

void* tlvmMallocInternal(int size)
{
    void* rtn = malloc(size);
    memset(rtn, 0, size);
    return rtn;
}

void  tlvmFreeInternal(void* ptr)
{
    free(ptr);
}
