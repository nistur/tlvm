#pragma once
#ifndef __TLVM_INTERNAL_H__
#define __TLVM_INTERNAL_H__

#include "tlvm.h"

#include "tlvm_instructions.h"

#define TLVM_REG_F 0x0
#define TLVM_REG_A 0x1
#define TLVM_REG_C 0x2
#define TLVM_REG_B 0x3
#define TLVM_REG_E 0x4
#define TLVM_REG_D 0x5
#define TLVM_REG_L 0x6
#define TLVM_REG_H 0x7

#define TLVM_FLAG_S 	(1<<7) // Sign
#define TLVM_FLAG_Z 	(1<<6) // Zero
#define TLVM_FLAG_I 	(1<<5) // Interrupt
#define TLVM_FLAG_H 	(1<<4) // Auxiliary Carry
#define TLVM_FLAG_P 	(1<<2) // Parity
#define TLVM_FLAG_C 	(1<<0) // Carry
#define TLVM_FLAG_ALL 	(TLVM_FLAG_S | TLVM_FLAG_Z | TLVM_FLAG_I| TLVM_FLAG_H | TLVM_FLAG_P | TLVM_FLAG_C)
#define TLVM_FLAG_NONE 	~TLVM_FLAG_ALL

#define TLVM_FLAG_ISSET(x) (context->m_Registers[TLVM_REG_F] & TLVM_FLAG_##x)
#define TLVM_FLAG_SET(x) context->m_Registers[TLVM_REG_F] |= TLVM_FLAG_##x
#define TLVM_FLAG_UNSET(x) context->m_Registers[TLVM_REG_F] &= (TLVM_FLAG_ALL ^ TLVM_FLAG_##x)
#define TLVM_FLAG_SET_IF(test, x) if(test){ TLVM_FLAG_SET(x); }else{ TLVM_FLAG_UNSET(x); }
#define TLVM_SET_FLAGS(res) \
	TLVM_FLAG_SET_IF((res & 0xFF) == 0, Z); \
	TLVM_FLAG_SET_IF(res & 0x80, S); \
	TLVM_FLAG_SET_IF(res > 0xFF, C); \
	

#define TLVM_OPCODE_MAX (256)

#define TLVM_GET_16BIT(h, l) 	((tlvmShort)context->m_Registers[h]) << 8 | (tlvmShort)context->m_Registers[l]
#define TLVM_SET_16BIT(h, l, v) \
	context->m_Registers[h] = (tlvmByte)(v >> 8); \
	context->m_Registers[l] = (tlvmByte)(v & 0xFF);

#define TLVM_GET_OP(v, n) \
	tlvmByte v = 0;\
	tlvmByte* v##addr = tlvmGetMemory(context, context->m_ProgramCounter+n, TLVM_FLAG_READ); \
	if(v##addr != NULL) \
		v = *v##addr;

typedef tlvmReturn(*tlvmInstruction)(tlvmContext*, tlvmByte*);

tlvmByte* tlvmGetMemory(tlvmContext* context, tlvmShort address, tlvmByte flags);

/***************************************
 * Library context
 * - holds current state
 ***************************************/
typedef struct _tlvmMemoryBuffer tlvmMemoryBuffer;

struct _tlvmContext
{
	tlvmMemoryBuffer* m_Memory;

	// instrution set
	tlvmInstruction m_InstructionSet[TLVM_OPCODE_MAX];

	tlvmShort  m_ProgramCounter;

	tlvmShort  m_StackPointer;

	// registers
	tlvmByte  m_Registers[8];
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
void* tlvmMallocInternal(int size);
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
#define tlvmReturnCode(x)				\
    {						\
	g_tlvmStatus = TLVM_##x;			\
	return TLVM_##x;			\
    }
#define tlvmReturn() \
    {  \
    	return g_tlvmStatus; \
    }



#endif/*__TLVM_INTERNAL_H__*/
