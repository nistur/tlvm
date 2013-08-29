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

#define TLVM_OPCODE_MAX (256)

typedef tlvmReturn(*tlvmInstruction)(tlvmContext*);

/***************************************
 * Library context
 * - holds current state
 ***************************************/
struct _tlvmContext
{
	tlvmByte* m_Memory;
	tlvmByte  m_MemorySize;

	// instrution set
	tlvmInstruction m_InstructionSet[TLVM_OPCODE_MAX];

	// program
	tlvmByte* m_Program;
	tlvmByte  m_ProgramCounter;

	// registers
	tlvmByte  m_Registers[8];
};

/***************************************
 * Some basic memory management wrappers
 ***************************************/
#include <stdlib.h>
#include <string.h>
#define tlvmMallocArray(x, n)   (x*)malloc(sizeof(x) * n)
#define tlvmMalloc(x)           (x*)malloc(sizeof(x))
#define tlvmFree(x)             free(x)
#define tlvmMemcpy(dst, src, s) memcpy(dst, src, sizeof(*src)*s);

/***************************************
 * Error handling
 ***************************************/
extern tlvmReturn  g_tlvmError;
extern const char* g_tlvmErrors[];
#define tlvmReturnCode(x)				\
    {						\
	g_tlvmError = TLVM_##x;			\
	return TLVM_##x;			\
    }
#define tlvmReturn() \
    {  \
    	return g_tlvmError; \
    }



#endif/*__TLVM_INTERNAL_H__*/
