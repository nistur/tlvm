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
#define TLVM_6800_MNEM(mnem) tlvmReturn tlvm6800##mnem (tlvmContext* context, tlvmByte* cycles)
#define TLVM_6800_MNEM_MOD(_mnem)	\
    TLVM_6800_MNEM(_mnem##_A);		\
    TLVM_6800_MNEM(_mnem##_B);		\
    TLVM_6800_MNEM(_mnem##_X);		\
    TLVM_6800_MNEM(_mnem##_E);

#define TLVM_6800_MNEM_FULL(_mnem)		\
    TLVM_6800_MNEM(_mnem##_I_A);		\
    TLVM_6800_MNEM(_mnem##_D_A);		\
    TLVM_6800_MNEM(_mnem##_X_A);		\
    TLVM_6800_MNEM(_mnem##_E_A);		\
    TLVM_6800_MNEM(_mnem##_I_B);		\
    TLVM_6800_MNEM(_mnem##_D_B);		\
    TLVM_6800_MNEM(_mnem##_X_B);		\
    TLVM_6800_MNEM(_mnem##_E_B);

#define TLVM_6800_INSTRUCTION(_mnem, _cycles, _len, _inst)		\
    TLVM_6800_MNEM(_mnem)						\
    {									\
    TLVM_NULL_CHECK(context, NO_CONTEXT);				\
    {									\
	_inst								\
    }									\
    context->m_ProgramCounter += _len;					\
    TLVM_TICK(_cycles);							\
    TLVM_RETURN_CODE(SUCCESS);						\
    }

TLVM_6800_MNEM(NOP);
TLVM_6800_MNEM(TAP);
TLVM_6800_MNEM(TPA);
TLVM_6800_MNEM(INX);
TLVM_6800_MNEM(DEX);
TLVM_6800_MNEM(CLV);
TLVM_6800_MNEM(SEV);
TLVM_6800_MNEM(CLC);
TLVM_6800_MNEM(SEC);
TLVM_6800_MNEM(CLI);
TLVM_6800_MNEM(SEI);

TLVM_6800_MNEM(SBA);
TLVM_6800_MNEM(CBA);
TLVM_6800_MNEM(TAB);
TLVM_6800_MNEM(TBA);
TLVM_6800_MNEM(DAA);
TLVM_6800_MNEM(ABA);

TLVM_6800_MNEM(BRA);
TLVM_6800_MNEM(BHI);
TLVM_6800_MNEM(BLS);
TLVM_6800_MNEM(BCC);
TLVM_6800_MNEM(BCS);
TLVM_6800_MNEM(BNE);
TLVM_6800_MNEM(BEQ);
TLVM_6800_MNEM(BVC);
TLVM_6800_MNEM(BVS);
TLVM_6800_MNEM(BPL);
TLVM_6800_MNEM(BMI);
TLVM_6800_MNEM(BGE);
TLVM_6800_MNEM(BLT);
TLVM_6800_MNEM(BGT);
TLVM_6800_MNEM(BLE);

TLVM_6800_MNEM(TSX);
TLVM_6800_MNEM(INS);
TLVM_6800_MNEM_MOD(PUL);
TLVM_6800_MNEM(DES);
TLVM_6800_MNEM(TXS);
TLVM_6800_MNEM_MOD(PSH);
TLVM_6800_MNEM(RTS);
TLVM_6800_MNEM(RTI);
TLVM_6800_MNEM(WAI);
TLVM_6800_MNEM(SWI);

TLVM_6800_MNEM_MOD(NEG);
TLVM_6800_MNEM_MOD(COM);
TLVM_6800_MNEM_MOD(LSR);
TLVM_6800_MNEM(ROR);
TLVM_6800_MNEM(ASR);
TLVM_6800_MNEM(ASL);
TLVM_6800_MNEM(ROL);
TLVM_6800_MNEM_MOD(DEC);
TLVM_6800_MNEM_MOD(INC);
TLVM_6800_MNEM(TST);
TLVM_6800_MNEM(CLR);

TLVM_6800_MNEM(SUB);
TLVM_6800_MNEM_FULL(CMP);
TLVM_6800_MNEM(SBC);
TLVM_6800_MNEM(AND);
TLVM_6800_MNEM(BIT);
TLVM_6800_MNEM_FULL(LDA);
TLVM_6800_MNEM(STA);
TLVM_6800_MNEM(EOR);
TLVM_6800_MNEM(ADC);
TLVM_6800_MNEM(ORA);
TLVM_6800_MNEM(ADD);
TLVM_6800_MNEM(CPX);
TLVM_6800_MNEM(BSR);
TLVM_6800_MNEM_MOD(JSR);
TLVM_6800_MNEM(LDS);
TLVM_6800_MNEM(LDX);
TLVM_6800_MNEM(STS);
TLVM_6800_MNEM(STX);

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

#define TLVM_6800_GET_MEM_INDEXED(_val)					\
    tlvmByte* _val = NULL;						\
    {									\
	TLVM_6800_GET_ADDR_INDEXED(addr);				\
	_val = tlvmGetMemory(context, addr, TLVM_FLAG_READ | TLVM_FLAG_WRITE ); \
	TLVM_NULL_CHECK(_val, NO_MEMORY);				\
    }

#define TLVM_6800_GET_MEM_EXTENDED(_val)				\
    tlvmByte* _val = NULL;						\
    {									\
	TLVM_6800_GET_ADDR_EXTENDED(addr);				\
	_val = tlvmGetMemory(context, addr, TLVM_FLAG_READ | TLVM_FLAG_WRITE ); \
	TLVM_NULL_CHECK(_val, NO_MEMORY);				\
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
    tlvmInstruction*     m_InstructionSet;
} tlvmProcessorData_6800;

#endif/*TLVM_HAS_6800*/
#endif/*__6800_H__*/
