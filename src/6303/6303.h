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
#ifndef __6303_H__
#define __6303_H__

#ifdef  TLVM_HAS_6303

#define TLVM_6303_REG_F    0x0
#define TLVM_6303_REG_A    0x1
#define TLVM_6303_REG_B    0x2
#define TLVM_6303_REG_D    0x3
#define TLVM_6303_REG_E    0x4

/*********************************************
 * FLAGS
 *********************************************/
#define TLVM_6303_FLAG_H   (1<<7) // Half Carry
#define TLVM_6303_FLAG_I   (1<<6) // Interrupt
#define TLVM_6303_FLAG_N   (1<<5) // Negative
#define TLVM_6303_FLAG_Z   (1<<4) // Zero
#define TLVM_6303_FLAG_V   (1<<2) // Overflow
#define TLVM_6303_FLAG_C   (1<<0) // Carry

#define TLVM_6303_FLAG_ALL  \
       (TLVM_6303_FLAG_H | \
        TLVM_6303_FLAG_I | \
        TLVM_6303_FLAG_N | \
        TLVM_6303_FLAG_Z | \
        TLVM_6303_FLAG_V | \
        TLVM_6303_FLAG_C)

// TLVM_FLAG_NONE is not just 0, as some of the bits are not used as flags
#define TLVM_6303_FLAG_NONE   ~TLVM_6303_FLAG_ALL

TLVM_INSTRUCTION_BASE(6303, LSR);

TLVM_INSTRUCTION_DECLARE  (6303, TRAP,  0x00);
TLVM_INSTRUCTION_DECLARE  (6303, NOP,   0x01);
TLVM_INSTRUCTION_VARIATION(6303, LSRD,  0x04);
TLVM_INSTRUCTION_VARIATION(6303, LSRA,  0x44);
TLVM_INSTRUCTION_VARIATION(6303, LSRB,  0x54);
TLVM_INSTRUCTION_VARIATION(6303, LSRdX, 0x64);
TLVM_INSTRUCTION_VARIATION(6303, LSRmm, 0x74);

/*********************************************
 * tlvm6303Init
 *     Setup the entire 6303 CPU. This will
 * initialise all the registers and I/O ports 
 * and then setup the instruction set
 * parameters:
 *     context - the CPU context to add 6303 
 * support to
 *********************************************/
tlvmReturn  tlvm6303Init  (tlvmContext** context);


/*********************************************
 * tlvm6303SetupData
 *     Add Hitachi 6303 instruction set to CPU
 *********************************************/
void       tlvm6303SetupData();

typedef struct _tlvmContext_6303
{
    tlvmContext m_Header;

    tlvmByte    m_Registers[9];
    tlvmByte    m_Ports[256];
} tlvmContext_6303;

typedef struct _tlvmProcessorData_6303
{
    tlvmProcessorData m_Header;

    // instrution set
    tlvmInstruction     m_InstructionSet[256];
} tlvmProcessorData_6303;

#endif/*TLVM_HAS_6303*/
#endif/*__6303_H__*/
