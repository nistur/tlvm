#include "tlvm_internal.h"

tlvmReturn tlvmClearContext(tlvmContext* context)
{
    context->m_Memory = NULL;
    context->m_MemorySize = 0;

    context->m_Program = NULL;
    context->m_ProgramCounter = 0;

    memset(context->m_InstructionSet, 0, sizeof(tlvmInstruction*) * TLVM_OPCODE_MAX);

    tlvmReturnCode(SUCCESS);
}

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

    (*context)->m_InstructionSet[TLVM_NOOP] = tlvmNOOP;

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

tlvmReturn tlvmSetMemoryBuffer(tlvmContext* context, tlvmByte* memory, tlvmByte size)
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

tlvmReturn tlvmLoadProgram(tlvmContext* context, tlvmByte* program, tlvmUInt size)
{
    if(context == NULL)
        tlvmReturnCode(NO_CONTEXT);
    if(program == NULL || size == 0)
        tlvmReturnCode(INVALID_INPUT)
    context->m_Program = tlvmMallocArray(tlvmByte, size);
    tlvmMemcpy(context->m_Program, program, size);

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
    if(g_tlvmError != TLVM_EXIT)
        tlvmReturn();
    tlvmReturnCode(SUCCESS);
}

const char* tlvmError()
{
    return g_tlvmErrors[g_tlvmError];
}
