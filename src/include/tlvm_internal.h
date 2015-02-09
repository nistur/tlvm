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

#pragma once
#ifndef __TLVM_INTERNAL_H__
#define __TLVM_INTERNAL_H__

#include "tlvm.h"
#include "tlvm_time.h"
#include "tlvm_debug_internal.h"

typedef struct _tlvmProcessorData
{
	tlvmByte m_ProcessorID;
} tlvmProcessorData;
#include "../8080/8080.h"

#define TLVM_FLAG_ISSET(x) (context->m_Registers[TLVM_REG_F] & TLVM_FLAG_##x)
#define TLVM_FLAG_SET(x) context->m_Registers[TLVM_REG_F] |= TLVM_FLAG_##x
#define TLVM_FLAG_UNSET(x) context->m_Registers[TLVM_REG_F] &= (TLVM_FLAG_ALL ^ TLVM_FLAG_##x)
#define TLVM_FLAG_SET_IF(test, x) if(test){ TLVM_FLAG_SET(x); }else{ TLVM_FLAG_UNSET(x); }
#define TLVM_SET_FLAGS(res) \
	TLVM_FLAG_SET_IF((res & 0xFF) == 0, Z); \
	TLVM_FLAG_SET_IF(res & 0x80, S); \
	TLVM_FLAG_SET_IF(res > 0xFF, C); \
	TLVM_FLAG_SET_IF(tlvmParity(res) == TLVM_TRUE, P);
	
#define TLVM_GET_16BIT(h, l) 	((tlvmShort)context->m_Registers[h]) << 8 | (tlvmShort)context->m_Registers[l]
#define TLVM_SET_16BIT(h, l, v) \
	context->m_Registers[h] = (tlvmByte)((v) >> 8); \
	context->m_Registers[l] = (tlvmByte)((v) & 0xFF);

#define TLVM_REGISTER_COMPLEMENT(x) \
    context->m_Registers[x] = ~context->m_Registers[x];

#define TLVM_GET_OP(v, n) \
	tlvmByte v = 0;\
	tlvmByte* v##addr = tlvmGetMemory(context, context->m_ProgramCounter+n, TLVM_FLAG_READ); \
	if(v##addr != NULL) \
		v = *v##addr; \
    else \
        TLVM_RETURN_CODE(NO_MEMORY)

#define TLVM_STACK_PUSH(v) \
{ \
    tlvmByte* dst = tlvmGetMemory(context, context->m_StackPointer - 1, TLVM_FLAG_WRITE); \
    if(dst == NULL) \
        TLVM_RETURN_CODE(INVALID_INPUT); \
    *dst = v; \
    context->m_StackPointer --; \
}

#define TLVM_STACK_POP(v) \
{ \
    tlvmByte* dst = tlvmGetMemory(context, context->m_StackPointer - 0, TLVM_FLAG_READ); \
    if(dst == NULL) \
        TLVM_RETURN_CODE(INVALID_INPUT); \
    v = *dst; \
    context->m_StackPointer ++; \
}

#define TLVM_PUSH_PC(val) \
{ \
	tlvmByte pcHi = (tlvmByte)(context->m_ProgramCounter >> 8); \
	tlvmByte pcLo = (tlvmByte)(context->m_ProgramCounter & 0xFF); \
	TLVM_STACK_PUSH(pcHi); \
	TLVM_STACK_PUSH(pcLo); \
	context->m_ProgramCounter = val; \
}

#define TLVM_POP_PC() \
{ \
	tlvmByte pcHi, pcLo; \
	TLVM_STACK_POP(pcLo); \
	TLVM_STACK_POP(pcHi); \
	context->m_ProgramCounter = ((tlvmShort)(pcHi) << 8) | (tlvmShort)pcLo; \
}

typedef tlvmReturn(*tlvmInstruction)(tlvmContext*, tlvmByte*);

tlvmByte* tlvmGetMemory(tlvmContext* context, tlvmShort address, tlvmByte flags);

tlvmBool tlvmParity(tlvmByte val);

/***************************************
 * Library context
 * - holds current state
 ***************************************/
typedef struct _tlvmMemoryBuffer tlvmMemoryBuffer;

struct _tlvmContext
{
	tlvmMemoryBuffer* m_Memory;

	// instrution set
	tlvmInstruction* m_InstructionSet;

	tlvmShort  m_ProgramCounter;

	tlvmShort  m_StackPointer;

	// registers
	tlvmByte*  m_Registers;

	tlvmByte*  m_Ports; // for now, just hardcode this in

	tlvmShort  m_Clockspeed;

	tlvmLong   m_StartTime;

	tlvmLong   m_TimeOffset;

#ifdef  TLVM_DEBUG
	tlvmDebugBreakpoint* 	m_Breakpoints;
	tlvmByte				m_DebugState;
	tlvmDebugCallbackFn     m_StepCallback;
#endif/*TLVM_DEBUG*/

	tlvmProcessorData* m_ProcessorData;

    tlvmClockFn        m_ClockFn;
    tlvmByte           m_Halt;
};

struct _tlvmMemoryBuffer
{
	tlvmMemoryBuffer* m_Next;
	tlvmShort         m_Start;
	tlvmShort         m_End;
	tlvmByte*         m_Buffer;
	tlvmByte		  m_Flags;
};
/***************************************
 * Some basic memory management wrappers
 ***************************************/
#include <stdlib.h>
#include <string.h>
void* tlvmMallocInternal(size_t size);
void  tlvmFreeInternal(void* ptr);
#define tlvmMallocArray(x, n)   (x*)tlvmMallocInternal(sizeof(x) * n)
#define tlvmMalloc(x)           (x*)tlvmMallocInternal(sizeof(x))
#define tlvmFree(x)             if(x) { tlvmFreeInternal(x); x = 0; }
#define tlvmMemcpy(dst, src, s) memcpy(dst, src, sizeof(*src)*s);

/***************************************
 * Error handling
 ***************************************/
extern tlvmReturn  g_tlvmStatus;
extern const char* g_tlvmStatusMessages[];
#define TLVM_RETURN_CODE(x)				\
    {						\
	g_tlvmStatus = TLVM_##x;			\
	return TLVM_##x;			\
    }
#define TLVM_RETURN() \
    {  \
    	return g_tlvmStatus; \
    }



#endif/*__TLVM_INTERNAL_H__*/
