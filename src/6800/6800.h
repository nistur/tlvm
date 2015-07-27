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
#ifndef __6800_H__
#define __6800_H__

#ifdef  TLVM_HAS_6800

/*********************************************
 * REGISTERS
 *********************************************/
#define TLVM_6800_REG_A    0x0
#define TLVM_6800_REG_B    0x1
#define TLVM_6800_REG_F    0x2 // Condition Code Register

#define TLVM_6800_REG16_IX 0x0

/*********************************************
 * FLAGS
 *********************************************/
#define TLVM_6800_FLAG_H   (1<<5) // Half Carry
#define TLVM_6800_FLAG_I   (1<<4) // Interrupt
#define TLVM_6800_FLAG_N   (1<<3) // Negative
#define TLVM_6800_FLAG_Z   (1<<2) // Zero
#define TLVM_6800_FLAG_V   (1<<1) // Overflow
#define TLVM_6800_FLAG_C   (1<<0) // Carry

#define TLVM_6800_FLAG_ALL  \
       (TLVM_6800_FLAG_H | \
        TLVM_6800_FLAG_I | \
        TLVM_6800_FLAG_N | \
        TLVM_6800_FLAG_Z | \
        TLVM_6800_FLAG_V | \
        TLVM_6800_FLAG_C)

// TLVM_FLAG_NONE is not just 0, as some of the bits are not used as flags
#define TLVM_6800_FLAG_NONE   ~TLVM_6800_FLAG_ALL

/*********************************************
 * INTERRUPT VECTOR
 *********************************************/
#define TLVM_6800_INT_RESET 0xFFFE
#define TLVM_6800_INT_NMI   0xFFFC
#define TLVM_6800_INT_SWI   0xFFFA
#define TLVM_6800_INT_IRQ   0xFFF8

/*********************************************
 * INSTRUCTIONS
 *********************************************/
TLVM_INSTRUCTION_BASE(6800, LSR);
TLVM_INSTRUCTION_BASE(6800, TRA);
TLVM_INSTRUCTION_BASE(6800, INC);
TLVM_INSTRUCTION_BASE(6800, DEC);
TLVM_INSTRUCTION_BASE(6800, CLR);
TLVM_INSTRUCTION_BASE(6800, SET);
TLVM_INSTRUCTION_BASE(6800, SUB);
TLVM_INSTRUCTION_BASE(6800, CMP);
TLVM_INSTRUCTION_BASE(6800, SUB);
TLVM_INSTRUCTION_BASE(6800, ADD);
TLVM_INSTRUCTION_BASE(6800, BRA);
TLVM_INSTRUCTION_BASE(6800, PUL);
TLVM_INSTRUCTION_BASE(6800, PSH);
TLVM_INSTRUCTION_BASE(6800, NEG);

TLVM_INSTRUCTION_DECLARE  (6800, NOP,   0x01);
TLVM_INSTRUCTION_VARIATION(6800, TAP,   0x06);
TLVM_INSTRUCTION_VARIATION(6800, TPA,   0x07);
TLVM_INSTRUCTION_VARIATION(6800, INX,   0x08);
TLVM_INSTRUCTION_VARIATION(6800, DEX,   0x09);
TLVM_INSTRUCTION_VARIATION(6800, CLV,   0x0A);
TLVM_INSTRUCTION_VARIATION(6800, SEV,   0x0B);
TLVM_INSTRUCTION_VARIATION(6800, CLC,   0x0C);
TLVM_INSTRUCTION_VARIATION(6800, SEC,   0x0D);
TLVM_INSTRUCTION_VARIATION(6800, CLI,   0x0E);
TLVM_INSTRUCTION_VARIATION(6800, SEI,   0x0F);

TLVM_INSTRUCTION_VARIATION(6800, SBA,   0x10);
TLVM_INSTRUCTION_VARIATION(6800, CBA,   0x11);
TLVM_INSTRUCTION_VARIATION(6800, TAB,   0x16);
TLVM_INSTRUCTION_VARIATION(6800, TBA,   0x17);
TLVM_INSTRUCTION_DECLARE  (6800, DAA,   0x19);
TLVM_INSTRUCTION_VARIATION(6800, ABA,   0x1B);

TLVM_INSTRUCTION_VARIATION(6800, BRA,   0x20);
TLVM_INSTRUCTION_VARIATION(6800, BHI,   0x22);
TLVM_INSTRUCTION_VARIATION(6800, BLS,   0x23);
TLVM_INSTRUCTION_VARIATION(6800, BCC,   0x24);
TLVM_INSTRUCTION_VARIATION(6800, BCS,   0x25);
TLVM_INSTRUCTION_VARIATION(6800, BNE,   0x26);
TLVM_INSTRUCTION_VARIATION(6800, BEQ,   0x27);
TLVM_INSTRUCTION_VARIATION(6800, BVC,   0x28);
TLVM_INSTRUCTION_VARIATION(6800, BVS,   0x29);
TLVM_INSTRUCTION_VARIATION(6800, BPL,   0x2A);
TLVM_INSTRUCTION_VARIATION(6800, BMI,   0x2B);
TLVM_INSTRUCTION_VARIATION(6800, BGE,   0x2C);
TLVM_INSTRUCTION_VARIATION(6800, BLT,   0x2D);
TLVM_INSTRUCTION_VARIATION(6800, BGT,   0x2E);
TLVM_INSTRUCTION_VARIATION(6800, BLE,   0x2F);

TLVM_INSTRUCTION_VARIATION(6800, TSX,   0x30);
TLVM_INSTRUCTION_VARIATION(6800, INS,   0x31);
TLVM_INSTRUCTION_VARIATION(6800, PULA,  0x32);
TLVM_INSTRUCTION_VARIATION(6800, PULB,  0x33);
TLVM_INSTRUCTION_VARIATION(6800, DES,   0x34);
TLVM_INSTRUCTION_VARIATION(6800, TXS,   0x35);
TLVM_INSTRUCTION_VARIATION(6800, PSHA,  0x36);
TLVM_INSTRUCTION_VARIATION(6800, PSHB,  0x37);
TLVM_INSTRUCTION_DECLARE  (6800, RTS,   0x39);
TLVM_INSTRUCTION_DECLARE  (6800, RTI,   0x3B);
TLVM_INSTRUCTION_DECLARE  (6800, WAI,   0x3E);
TLVM_INSTRUCTION_DECLARE  (6800, SWI,   0x3E);

TLVM_INSTRUCTION_VARIATION(6800, NEGA,  0x40);

TLVM_INSTRUCTION_VARIATION(6800, NEGB,  0x50);

TLVM_INSTRUCTION_VARIATION(6800, NEGX,  0x60);

TLVM_INSTRUCTION_VARIATION(6800, NEGE,  0x70);

TLVM_INSTRUCTION_VARIATION(6800, LSRA,  0x44);
TLVM_INSTRUCTION_VARIATION(6800, LSRB,  0x54);
TLVM_INSTRUCTION_VARIATION(6800, LSRdX, 0x64);
TLVM_INSTRUCTION_VARIATION(6800, LSRmm, 0x74);

#define TLVM_6800_GET_ADDR_EXTENDED(val)                \
tlvmShort val;                                          \
{                                                       \
    TLVM_GET_OP(hi, 1);                                 \
    TLVM_GET_OP(lo, 2);                                 \
    val = ((((tlvmShort)hi) << 8) | ((tlvmShort)lo));   \
}

#define TLVM_6800_GET_ADDR_INDEXED(val)                 \
tlvmShort val = TLVM_REGISTER16(TLVM_6800_REG16_IX);    \
{                                                       \
    TLVM_GET_OP(addr, 1);                               \
    val += (tlvmShort)addr;                             \
}

/*********************************************
 * tlvm6800Init
 *     Setup the entire 6800 CPU. This will
 * initialise all the registers and I/O ports 
 * and then setup the instruction set
 * parameters:
 *     context - the CPU context to add 6800 
 * support to
 *********************************************/
tlvmReturn  tlvm6800Init  (tlvmContext** context);


/*********************************************
 * tlvm6800SetupData
 *     Add Motorolla 6800 instruction set to CPU
 *********************************************/
void       tlvm6800SetupData();

/*********************************************
 * tlvm6800Interrupt
 *     Perform a hardware interrupt on the 6800 CPU
 * parameters:
 *     context - the CPU context to perform the
 * interrupt on
 *     interrupt - the kind of hardware interrupt
 * to trigger
 *         - TLVM_INTERRUPT_IRQ - Maskable interrupt
 *         - TLVM_INTERRUPT_NMI - Non-Maskable interrupt
 *         - TLVM_INTERRUPT_RESET - Reset interrupt
 *********************************************/
tlvmReturn tlvm6800Interrupt(tlvmContext* context, tlvmByte interrupt);

typedef struct _tlvmContext_6800
{
    tlvmContext m_Header;

    tlvmByte    m_Registers[9];
    tlvmShort   m_WideRegisters[1];
    tlvmByte    m_Ports[256];
} tlvmContext_6800;

typedef struct _tlvmProcessorData_6800
{
    tlvmProcessorData m_Header;

    // instrution set
    tlvmInstruction     m_InstructionSet[256];
} tlvmProcessorData_6800;

#endif/*TLVM_HAS_6800*/
#endif/*__6800_H__*/
