#pragma once
#ifndef __6502_H__
#define __6502_H__

#ifdef  TLVM_HAS_6502
/*********************************************
 * REGISTERS
 *********************************************/
#define TLVM_6502_REG_A    0x0 // Accumulator
#define TLVM_6502_REG_X    0x1
#define TLVM_6502_REG_Y    0x2
#define TLVM_6502_REG_SP_H 0x3 // Stack Pointer High byte
#define TLVM_6502_REG_SP_L 0x4 // Stack Pointer Low byte
#define TLVM_6502_REG_P    0x5 // Processor flags

/*********************************************
 * FLAGS
 *********************************************/
#define TLVM_6502_FLAG_N 	(1<<7) // Sign
#define TLVM_6502_FLAG_V 	(1<<6) // Overflow
#define TLVM_6502_FLAG_B 	(1<<4) // Breakpoint
#define TLVM_6502_FLAG_D 	(1<<3) // BCD
#define TLVM_6502_FLAG_I 	(1<<2) // Interrupt
#define TLVM_6502_FLAG_Z 	(1<<1) // Zero
#define TLVM_6502_FLAG_C 	(1<<0) // Carry

/*********************************************
 * INSTRUCTIONS
 *********************************************/
#define TLVM_6502_NOP 0xEA


tlvmReturn tlvm6502NOP(tlvmContext* context, tlvmByte* cycles);

/*********************************************
 * tlvmAdd6502Instructions
 *     Add MOS Technology 6502 instruction set
 *   to CPU
 * parameters:
 *     context - the CPU context to add 6502 
 *     support to
 *********************************************/
tlvmReturn  tlvmAdd6502Instructions(tlvmContext* context);

typedef struct _tlvm6502data
{
	tlvmProcessorData m_Header;
} tlvm6502data;

#endif/*TLVM_HAS_6502*/
#endif/*__6502_H__*/