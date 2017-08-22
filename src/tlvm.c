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
    TLVM_NULL_CHECK(cpuid, INVALID_INPUT);
#if TLVM_HAS_8080
    if(cpuid == TLVM_CPU_8080)
        tlvm8080Init(context);
#endif
#if TLVM_HAS_6800
    if(cpuid == TLVM_CPU_6800)
        tlvm6800Init(context);
#endif
#if TLVM_HAS_6303
    if(cpuid == TLVM_CPU_6303)
        tlvm6303Init(context);
#endif
#if TLVM_HAS_Z80
    if(cpuid == TLVM_CPU_Z80)
        tlvmZ80Init(context);
#endif

#ifdef TLVM_DEBUG
    (*context)->m_Backtrace = (*context)->m_BacktracePool;
    int bt = 0;
    (*context)->m_BacktracePool[bt].m_Trace[0] = 0;
    for(bt = 0; bt < TLVM_DEBUG_BACKTRACE_SIZE - 1; ++bt)
    {
	(*context)->m_BacktracePool[bt].m_Next = &(*context)->m_BacktracePool[bt+1];
	(*context)->m_BacktracePool[bt+1].m_Prev = &(*context)->m_BacktracePool[bt];
	(*context)->m_BacktracePool[bt+1].m_Trace[0] = 0;
	(*context)->m_BacktraceEnd = &(*context)->m_BacktracePool[bt+1];
    }
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

    tlvmDebugBacktrace* trace = context->m_BacktraceEnd;
    // mark previous one as new end
    context->m_BacktraceEnd = trace->m_Prev;
    trace->m_Prev->m_Next = 0;
    trace->m_Prev = 0;
    // put this one at the start
    context->m_Backtrace->m_Prev = trace;
    trace->m_Next = context->m_Backtrace;
    context->m_Backtrace = trace;
    // populate this trace
    tlvmChar*  instruction = tlvmMallocArray(tlvmChar, TLVM_DEBUG_BACKTRACE_STRSIZE);
    tlvmByte size = TLVM_DEBUG_BACKTRACE_STRSIZE;
    tlvmDebugGetInstruction(context, &instruction, &size);
    sprintf(trace->m_Trace, "0x%X\t%s", context->m_ProgramCounter, instruction);
    tlvmFree(instruction);
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

    tlvmUnsetFlags(context, TLVM_FLAG_HALT | TLVM_FLAG_STALL);

    tlvmLong cycleCount = 0;
    tlvmByte cycles = 0;
    tlvmReturn status = TLVM_SUCCESS;
    
    tlvmResetClock(context);
    
    while(TLVM_TRUE)
    {
        if(context->m_Flags & TLVM_FLAG_HALT)
            break;

        // if we're stalled, still tick over the CPU emulation, just
        // don't step forward - This should get the correct behaviour
        if((context->m_Flags & TLVM_FLAG_STALL) == TLVM_FALSE)
            status = tlvmStep(context, &cycles);
        
        if(status == TLVM_STALL)
        {
            // If the CPU's stalled and we've been told to halt on stalls
            // then flag that the CPU's halted, which will break out of
            // the run loop the next time around, after we've called sleep
            // which would match behaviour of instructions which stall the
            // CPU, as they finish execution before stalling (eg 6800 WAI)
            // To continue execution after a stall, either the halt on stall
            // flag should NOT be set, or tlvmRun should be called at the
            // correct time to continue execution.
            if((context->m_Flags & TLVM_FLAG_HALT_ON_STALL) &&
               (context->m_Flags & TLVM_FLAG_HALT) == TLVM_FALSE)
                tlvmSetFlags(context, TLVM_FLAG_HALT);
        }
        else if(status != TLVM_SUCCESS)
        {
            // anything else other than stall and success, we definitely
            // want to break out
            break;
        }
        
        cycleCount += (tlvmLong)cycles;
        
        if(context->m_Clockspeed != 0)
            tlvmSleepUntil(context, cycleCount); // sleep until we've taken long enough for 
        
    }
    tlvmSetFlags(context, TLVM_FLAG_HALT);
    if(status != TLVM_EXIT)
        TLVM_RETURN();
    TLVM_RETURN_CODE(SUCCESS);
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

#ifdef TLVM_DEBUG
    if(flags  & TLVM_FLAG_WRITE)
    {
	tlvmDebugCheckMemory(context, address);
    }
#endif/*TLVM_DEBUG*/

    tlvmShort addr = address - pMem->m_Start;
    return &pMem->m_Buffer[addr];
}

tlvmReturn tlvmGetPort(tlvmContext* context, tlvmByte port, tlvmByte* outPort)
{
    TLVM_NULL_CHECK(context, NO_CONTEXT);
    TLVM_NULL_CHECK(outPort, INVALID_INPUT);
    *outPort = context->m_OutputPorts[port];
    TLVM_RETURN_CODE(SUCCESS);
}

tlvmReturn tlvmSetPort(tlvmContext* context, tlvmByte port, tlvmByte portval)
{
    TLVM_NULL_CHECK(context, NO_CONTEXT);
    context->m_InputPorts[port] = portval;
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
    return tlvmSetFlags(context, TLVM_FLAG_HALT);
}

tlvmReturn tlvmGetFlags(tlvmContext* context, tlvmByte* flags)
{
    TLVM_NULL_CHECK(context, NO_CONTEXT);
    TLVM_NULL_CHECK(flags, INVALID_INPUT);

    *flags = context->m_Flags;
    
    TLVM_RETURN_CODE(SUCCESS);
}

tlvmReturn tlvmUnsetFlags(tlvmContext* context, tlvmByte flags)
{
    TLVM_NULL_CHECK(context, NO_CONTEXT);

    context->m_Flags &= ~flags;
    
    TLVM_RETURN_CODE(SUCCESS);
}

tlvmReturn tlvmSetFlags(tlvmContext* context, tlvmByte flags)
{
    TLVM_NULL_CHECK(context, NO_CONTEXT);

    context->m_Flags |= flags;
    
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
