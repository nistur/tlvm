/*
Copyright (c) 2015 Philipp Geyer

This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not
   claim that you wrote the original software. If you use this software
   in a product, an acknowledgement in the product documentation would be
   appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be
   misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.

Philipp Geyer
nistur@gmail.com
*/

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

    TLVM_RETURN_CODE(SUCCESS);
}

tlvmReturn tlvmInitContext(tlvmContext** context, tlvmByte cpuid)
{
    TLVM_NULL_CHECK(context, NO_CONTEXT);
#if TLVM_HAS_8080
    if(cpuid == TLVM_CPU_8080)
        tlvm8080Init(context);
#endif
#if TLVM_HAS_6303
    if(cpuid == TLVM_CPU_6303)
        tlvm6303Init(context);
#endif
#if TLVM_HAS_6502
    if(cpuid == TLVM_CPU_6502)
        tlvm6502Init(context);
#endif

    TLVM_RETURN_CODE(SUCCESS);
}

tlvmReturn tlvmTerminateContext(tlvmContext** context)
{
    TLVM_NULL_CHECK(context, NO_CONTEXT);
    TLVM_NULL_CHECK(*context, NO_CONTEXT);

    if(tlvmClearContext(*context) != TLVM_SUCCESS)
        TLVM_RETURN();

    tlvmFree(*context);
    *context = 0;
    TLVM_RETURN_CODE(SUCCESS);
}

tlvmReturn tlvmSetClockspeed(tlvmContext* context, tlvmShort clockspeed)
{
    TLVM_NULL_CHECK(context, NO_CONTEXT);
    context->m_Clockspeed = clockspeed;

    TLVM_RETURN_CODE(SUCCESS);
}

tlvmReturn tlvmSetMemory(tlvmContext* context, tlvmByte* memory, tlvmShort offset, tlvmShort size, tlvmByte flags)
{
    TLVM_NULL_CHECK(context, NO_CONTEXT);
    TLVM_NULL_CHECK(memory, NO_MEMORY);
    TLVM_NULL_CHECK(size, INVALID_INPUT);
    tlvmShort start = offset;
    tlvmShort end = offset + size - 1;

    if(context->m_Memory == NULL || start < context->m_Memory->m_Start)
    {
        if( context->m_Memory != NULL && end > context->m_Memory->m_Start )
            TLVM_RETURN_CODE(MEMORY_OVERLAP);
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
                TLVM_RETURN_CODE(MEMORY_OVERLAP);
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

    TLVM_RETURN_CODE(SUCCESS);
}

tlvmReturn tlvmUnsetMemory(tlvmContext* context, tlvmByte* memory)
{
    TLVM_NULL_CHECK(context, NO_CONTEXT);
    TLVM_NULL_CHECK(memory, NO_MEMORY);
    TLVM_NULL_CHECK(context->m_Memory, NO_MEMORY);

    if(memory == context->m_Memory->m_Buffer)
    {
        tlvmMemoryBuffer* pMem = context->m_Memory;
        context->m_Memory = pMem->m_Next;
        tlvmFree(pMem);
        TLVM_RETURN_CODE(SUCCESS);
    }

    tlvmMemoryBuffer* pPrev = context->m_Memory;
    tlvmMemoryBuffer* pMem = pPrev->m_Next;
    while(pMem)
    {
        if(pMem->m_Buffer)
        {
            pPrev->m_Next = pMem->m_Next;
            tlvmFree(pMem);
            TLVM_RETURN_CODE(SUCCESS);
        }
        pPrev = pMem;
        pMem = pPrev->m_Next;
    }
    // should never get here, but if we do, it's because the buffer couldn't be found
    TLVM_RETURN_CODE(INVALID_INPUT);
}

tlvmReturn tlvmStep(tlvmContext* context, tlvmByte* cycles)
{
    TLVM_NULL_CHECK(context, NO_CONTEXT);

#ifdef  TLVM_DEBUG
    if(tlvmDebugCheck(context) != TLVM_SUCCESS)
        TLVM_RETURN();
#endif/*TLVM_DEBUG*/

    tlvmByte* opcode = tlvmGetMemory(context, context->m_ProgramCounter, TLVM_FLAG_READ);
    TLVM_NULL_CHECK(opcode, INVALID_INPUT);
    TLVM_NULL_CHECK(context->m_ProcessorData->m_InstructionSet[*opcode], UNKNOWN_INSTRUCTION);
    tlvmByte numCycles = 0;
    context->m_ProcessorData->m_InstructionSet[*opcode](context, &numCycles);
    if(context->m_ClockFn)
    {
        int i;
        for(i = 0; i < numCycles; ++i)
            context->m_ClockFn(context, &numCycles);
    }
    if(cycles) *cycles = numCycles;
    TLVM_RETURN();
}

tlvmReturn tlvmRun(tlvmContext* context)
{
    TLVM_NULL_CHECK(context, NO_CONTEXT);

    context->m_Halt = TLVM_FALSE;

    if(context->m_Clockspeed == 0)
    {
        tlvmByte empty;
        while(tlvmStep(context, &empty) == TLVM_SUCCESS){}
        if(g_tlvmStatus != TLVM_EXIT)
            TLVM_RETURN();
        TLVM_RETURN_CODE(SUCCESS);
    }
    else
    {
        tlvmLong cycleCount = 0;
        tlvmByte cycles = 0;
        tlvmReturn status = TLVM_SUCCESS;

        tlvmResetClock(context);

        while(status == TLVM_SUCCESS && context->m_Halt == TLVM_FALSE)
        {
            status = tlvmStep(context, &cycles);

            cycleCount += (tlvmLong)cycles;

            tlvmSleepUntil(context, cycleCount); // sleep until we've taken long enough for 
        }

        if(status != TLVM_EXIT)
            TLVM_RETURN();
        TLVM_RETURN_CODE(SUCCESS);
    }
}

tlvmReturn tlvmReset(tlvmContext* context)
{
    TLVM_NULL_CHECK(context, NO_CONTEXT);
    context->m_ProgramCounter = 0;
    memset(context->m_Registers, 0, 8);
    context->m_StackPointer = 0;
#ifdef TLVM_DEBUG
    tlvmDebugReset(context);
#endif/*TLVM_DEBUG*/

    TLVM_RETURN_CODE(SUCCESS);
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

tlvmReturn tlvmGetPort(tlvmContext* context, tlvmByte port, tlvmByte* outPort)
{
    TLVM_NULL_CHECK(context, NO_CONTEXT);
    TLVM_NULL_CHECK(outPort, INVALID_INPUT);
    *outPort = context->m_Ports[port];
    TLVM_RETURN_CODE(SUCCESS);
}

tlvmReturn tlvmSetPort(tlvmContext* context, tlvmByte port, tlvmByte portval)
{
    TLVM_NULL_CHECK(context, NO_CONTEXT);
    context->m_Ports[port] = portval;
    TLVM_RETURN_CODE(SUCCESS);
}

tlvmReturn tlvmSetClock(tlvmContext* context, tlvmClockFn clockFn)
{
    TLVM_NULL_CHECK(context, NO_CONTEXT);

    context->m_ClockFn = clockFn;

    TLVM_RETURN_CODE(SUCCESS);
}

tlvmReturn tlvmInterrupt(tlvmContext* context, tlvmByte interrupt)
{
    TLVM_NULL_CHECK(context, NO_CONTEXT);

    return context->m_ProcessorData->m_Interrupt(context, interrupt);
}

tlvmReturn tlvmHalt(tlvmContext* context)
{
    TLVM_NULL_CHECK(context, NO_CONTEXT);

    context->m_Halt = TLVM_TRUE;

    TLVM_RETURN_CODE(SUCCESS);
}

tlvmReturn tlvmSetIOCallback(tlvmContext* context, tlvmIOCallback callback)
{
    TLVM_NULL_CHECK(context, NO_CONTEXT);

    context->m_IOCallback = callback;

    TLVM_RETURN_CODE(SUCCESS);
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

void* tlvmMallocInternal(size_t size)
{
    void* rtn = malloc(size);
    memset(rtn, 0, size);
    return rtn;
}

void  tlvmFreeInternal(void* ptr)
{
    free(ptr);
}
