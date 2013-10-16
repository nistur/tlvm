#include "tlvm_internal.h"

tlvmReturn tlvmClearContext(tlvmContext* context)
{
    tlvmMemoryBuffer* pMem = context->m_Memory;
    while(pMem)
    {
        tlvmMemoryBuffer* pNext = pMem->m_Next;
        tlvmFree(pMem);
        pMem = pNext;
    }

    // set everything to NULL/0
    memset(context, 0, sizeof(tlvmContext));

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

tlvmReturn tlvmSetClockspeed(tlvmContext* context, tlvmShort clockspeed)
{
    if(context == NULL)
        tlvmReturnCode(NO_CONTEXT);
    context->m_Clockspeed = clockspeed;

    tlvmReturnCode(SUCCESS);
}

tlvmReturn tlvmSetMemory(tlvmContext* context, tlvmByte* memory, tlvmShort offset, tlvmShort size, tlvmByte flags)
{
    if(context == NULL)
        tlvmReturnCode(NO_CONTEXT);
    if(memory == NULL)
        tlvmReturnCode(NO_MEMORY);
    if(size == 0)
        tlvmReturnCode(INVALID_INPUT);
    tlvmShort start = offset;
    tlvmShort end = offset + size;

    if(context->m_Memory == NULL || start < context->m_Memory->m_Start)
    {
        if( context->m_Memory != NULL && end > context->m_Memory->m_Start )
            tlvmReturnCode(MEMORY_OVERLAP);
        tlvmMemoryBuffer* mem = tlvmMalloc(tlvmMemoryBuffer);
        mem->m_Buffer = memory;
        mem->m_Start  = start;
        mem->m_End    = end;
        mem->m_Flags  = flags;
        mem->m_Next   = context->m_Memory;
        context->m_Memory = mem;
    }
    else
    {
        // find the correct place to add a new buffer
        tlvmMemoryBuffer* pBuf = context->m_Memory;
        while(pBuf)
        {
            tlvmMemoryBuffer* pNext = pBuf->m_Next;
            if(!pNext)
                break;
            if(start > pNext->m_Start)
            {
                pBuf = pNext;
                continue;
            }
            if(end > pNext->m_Start)
            {
                tlvmReturnCode(MEMORY_OVERLAP);
            }
            break;
        }

        tlvmMemoryBuffer* mem = tlvmMalloc(tlvmMemoryBuffer);
        mem->m_Buffer = memory;
        mem->m_Start  = start;
        mem->m_End    = end;
        mem->m_Flags  = flags;
        mem->m_Next   = pBuf->m_Next;
        pBuf->m_Next  = mem;
    }

    tlvmReturnCode(SUCCESS);
}

tlvmReturn tlvmUnsetMemory(tlvmContext* context, tlvmByte* memory)
{
    if(context == NULL)
        tlvmReturnCode(NO_CONTEXT);
    if(memory == NULL)
        tlvmReturnCode(NO_MEMORY);
    if(context->m_Memory == NULL)
        tlvmReturnCode(NO_MEMORY);

    if(memory == context->m_Memory->m_Buffer)
    {
        tlvmMemoryBuffer* pMem = context->m_Memory;
        context->m_Memory = pMem->m_Next;
        tlvmFree(pMem);
        tlvmReturnCode(SUCCESS);
    }

    tlvmMemoryBuffer* pPrev = context->m_Memory;
    tlvmMemoryBuffer* pMem = pPrev->m_Next;
    while(pMem)
    {
        if(pMem->m_Buffer)
        {
            pPrev->m_Next = pMem->m_Next;
            tlvmFree(pMem);
            tlvmReturnCode(SUCCESS);
        }
        pPrev = pMem;
        pMem = pPrev->m_Next;
    }
    // should never get here, but if we do, it's because the buffer couldn't be found
    tlvmReturnCode(INVALID_INPUT);
}

tlvmReturn tlvmStep(tlvmContext* context, tlvmByte* cycles)
{
    if(context == NULL)
        tlvmReturnCode(NO_CONTEXT);

#ifdef  TLVM_DEBUG
    if(tlvmDebugCheck(context) != TLVM_SUCCESS)
        tlvmReturn();
#endif/*TLVM_DEBUG*/

    tlvmByte* opcode = tlvmGetMemory(context, context->m_ProgramCounter, TLVM_FLAG_READ);
    if(opcode == NULL)
        tlvmReturnCode(INVALID_INPUT);
    if(context->m_InstructionSet[*opcode] == NULL)
        tlvmReturnCode(UNKNOWN_INSTRUCTION);
    context->m_InstructionSet[*opcode](context, cycles);
    tlvmReturn();
}

tlvmReturn tlvmRun(tlvmContext* context)
{
    if(context == NULL)
        tlvmReturnCode(NO_CONTEXT);

    if(context->m_Clockspeed == 0)
    {
        tlvmByte empty;
        while(tlvmStep(context, &empty) == TLVM_SUCCESS){}
        if(g_tlvmStatus != TLVM_EXIT)
            tlvmReturn();
        tlvmReturnCode(SUCCESS);
    }
    else
    {
        tlvmLong cycleCount = 0;
        tlvmByte cycles = 0;
        tlvmReturn status = TLVM_SUCCESS;

        tlvmResetClock(context);

        while(status == TLVM_SUCCESS)
        {
            status = tlvmStep(context, &cycles);

            cycleCount += (tlvmLong)cycles;

            tlvmSleepUntil(context, cycleCount); // sleep until we've taken long enough for 
        }

        if(status != TLVM_EXIT)
            tlvmReturn();
        tlvmReturnCode(SUCCESS);
    }
}

tlvmReturn tlvmReset(tlvmContext* context)
{
    if(context == NULL)
        tlvmReturnCode(NO_CONTEXT);
    context->m_ProgramCounter = 0;
    memset(context->m_Registers, 0, 8);
    context->m_StackPointer = 0;

    tlvmReturnCode(SUCCESS);
}

tlvmByte* tlvmGetMemory(tlvmContext* context, tlvmShort address, tlvmByte flags)
{
    if(context == NULL)
        return NULL;
    if(context->m_Memory == NULL)
        return NULL;

    tlvmMemoryBuffer* pMem = context->m_Memory;
    while(pMem && address > pMem->m_End) pMem = pMem->m_Next;

    if(pMem == NULL)
        return NULL;

    if(address < pMem->m_Start)
        return NULL;
    if(flags & TLVM_FLAG_WRITE && !(pMem->m_Flags & TLVM_FLAG_WRITE))
        return NULL;

    tlvmShort addr = address - pMem->m_Start;
    return &pMem->m_Buffer[addr];
}

// kinda hacked from http://www.emulator101.com.s3-website-us-east-1.amazonaws.com/files/8080emu-first50.c
tlvmBool tlvmParity(tlvmByte val)
{
    tlvmByte p = 0;
    tlvmByte i = 0;

    for (i=0; i<8; i++)
    {
        if (val & 0x1) p++;
        val = val >> 1;
    }
    return (0 == (p & 0x1));
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
