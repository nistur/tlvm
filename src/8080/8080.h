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
#ifndef __8080_H__
#define __8080_H__

#ifdef  TLVM_HAS_8080
#include "8080_debug.h"
/*********************************************
 * REGISTERS
 *********************************************/
#define TLVM_REG_F 0x0
#define TLVM_REG_A 0x1
#define TLVM_REG_C 0x2
#define TLVM_REG_B 0x3
#define TLVM_REG_E 0x4
#define TLVM_REG_D 0x5
#define TLVM_REG_L 0x6
#define TLVM_REG_H 0x7
 // fake register to carry pending interrupts
#define TLVM_REG_I 0x8

/*********************************************
 * FLAGS
 *********************************************/
#define TLVM_FLAG_S 	(1<<7) // Sign
#define TLVM_FLAG_Z 	(1<<6) // Zero
#define TLVM_FLAG_I 	(1<<5) // Interrupt
#define TLVM_FLAG_H 	(1<<4) // Auxiliary Carry
#define TLVM_FLAG_P 	(1<<2) // Parity
#define TLVM_FLAG_C 	(1<<0) // Carry

#define TLVM_FLAG_ALL 	(TLVM_FLAG_S | TLVM_FLAG_Z | TLVM_FLAG_I| TLVM_FLAG_H | TLVM_FLAG_P | TLVM_FLAG_C)

// TLVM_FLAG_NONE is not just 0, as some of the bits are not used as flags
#define TLVM_FLAG_NONE 	~TLVM_FLAG_ALL

/*********************************************
 * INSTRUCTIONS
 *   TODO: Sort these
 *   TODO: Replace TLVM_ with TLVM_8080_
 *********************************************/
#define TLVM_NOP           0x00
#define TLVM_HLT           0x76
#define TLVM_LXI_B         0x01
#define TLVM_STAX_B        0x02
#define TLVM_MVI_B         0x06
#define TLVM_RLC           0x07
#define TLVM_LDAX_B        0x0A
#define TLVM_MVI_C         0x0E
#define TLVM_RRC           0x0F
#define TLVM_LXI_D         0x11
#define TLVM_STAX_D        0x12
#define TLVM_MVI_D         0x16
#define TLVM_RAL           0x17
#define TLVM_LDAX_D        0x1A
#define TLVM_MVI_E         0x1E
#define TLVM_RAR           0x1F
#define TLVM_LXI_H         0x21
#define TLVM_SHLD          0x22
#define TLVM_MVI_H         0x26
#define TLVM_DAA           0x27
#define TLVM_LHLD          0x2A
#define TLVM_MVI_L         0x2E
#define TLVM_CMA           0x2F
#define TLVM_LXI_SP        0x31
#define TLVM_MVI_M         0x36
#define TLVM_STC           0x37
#define TLVM_LDA           0x3A
#define TLVM_MVI_A         0x3E
#define TLVM_CMC           0x3F

#define TLVM_MOV_BB        (TLVM_MOV_TO_B | TLVM_MOV_FROM_B)
#define TLVM_MOV_BC        (TLVM_MOV_TO_B | TLVM_MOV_FROM_C)
#define TLVM_MOV_BD        (TLVM_MOV_TO_B | TLVM_MOV_FROM_D)
#define TLVM_MOV_BE        (TLVM_MOV_TO_B | TLVM_MOV_FROM_E)
#define TLVM_MOV_BH        (TLVM_MOV_TO_B | TLVM_MOV_FROM_H)
#define TLVM_MOV_BL        (TLVM_MOV_TO_B | TLVM_MOV_FROM_L)
#define TLVM_MOV_BM        (TLVM_MOV_TO_B | TLVM_MOV_FROM_M)
#define TLVM_MOV_BA        (TLVM_MOV_TO_B | TLVM_MOV_FROM_A)

#define TLVM_MOV_CB        (TLVM_MOV_TO_C | TLVM_MOV_FROM_B)
#define TLVM_MOV_CC        (TLVM_MOV_TO_C | TLVM_MOV_FROM_C)
#define TLVM_MOV_CD        (TLVM_MOV_TO_C | TLVM_MOV_FROM_D)
#define TLVM_MOV_CE        (TLVM_MOV_TO_C | TLVM_MOV_FROM_E)
#define TLVM_MOV_CH        (TLVM_MOV_TO_C | TLVM_MOV_FROM_H)
#define TLVM_MOV_CL        (TLVM_MOV_TO_C | TLVM_MOV_FROM_L)
#define TLVM_MOV_CM        (TLVM_MOV_TO_C | TLVM_MOV_FROM_M)
#define TLVM_MOV_CA        (TLVM_MOV_TO_C | TLVM_MOV_FROM_A)

#define TLVM_MOV_DB        (TLVM_MOV_TO_D | TLVM_MOV_FROM_B)
#define TLVM_MOV_DC        (TLVM_MOV_TO_D | TLVM_MOV_FROM_C)
#define TLVM_MOV_DD        (TLVM_MOV_TO_D | TLVM_MOV_FROM_D)
#define TLVM_MOV_DE        (TLVM_MOV_TO_D | TLVM_MOV_FROM_E)
#define TLVM_MOV_DH        (TLVM_MOV_TO_D | TLVM_MOV_FROM_H)
#define TLVM_MOV_DL        (TLVM_MOV_TO_D | TLVM_MOV_FROM_L)
#define TLVM_MOV_DM        (TLVM_MOV_TO_D | TLVM_MOV_FROM_M)
#define TLVM_MOV_DA        (TLVM_MOV_TO_D | TLVM_MOV_FROM_A)

#define TLVM_MOV_EB        (TLVM_MOV_TO_E | TLVM_MOV_FROM_B)
#define TLVM_MOV_EC        (TLVM_MOV_TO_E | TLVM_MOV_FROM_C)
#define TLVM_MOV_ED        (TLVM_MOV_TO_E | TLVM_MOV_FROM_D)
#define TLVM_MOV_EE        (TLVM_MOV_TO_E | TLVM_MOV_FROM_E)
#define TLVM_MOV_EH        (TLVM_MOV_TO_E | TLVM_MOV_FROM_H)
#define TLVM_MOV_EL        (TLVM_MOV_TO_E | TLVM_MOV_FROM_L)
#define TLVM_MOV_EM        (TLVM_MOV_TO_E | TLVM_MOV_FROM_M)
#define TLVM_MOV_EA        (TLVM_MOV_TO_E | TLVM_MOV_FROM_A)

#define TLVM_MOV_HB        (TLVM_MOV_TO_H | TLVM_MOV_FROM_B)
#define TLVM_MOV_HC        (TLVM_MOV_TO_H | TLVM_MOV_FROM_C)
#define TLVM_MOV_HD        (TLVM_MOV_TO_H | TLVM_MOV_FROM_D)
#define TLVM_MOV_HE        (TLVM_MOV_TO_H | TLVM_MOV_FROM_E)
#define TLVM_MOV_HH        (TLVM_MOV_TO_H | TLVM_MOV_FROM_H)
#define TLVM_MOV_HL        (TLVM_MOV_TO_H | TLVM_MOV_FROM_L)
#define TLVM_MOV_HM        (TLVM_MOV_TO_H | TLVM_MOV_FROM_M)
#define TLVM_MOV_HA        (TLVM_MOV_TO_H | TLVM_MOV_FROM_A)

#define TLVM_MOV_LB        (TLVM_MOV_TO_L | TLVM_MOV_FROM_B)
#define TLVM_MOV_LC        (TLVM_MOV_TO_L | TLVM_MOV_FROM_C)
#define TLVM_MOV_LD        (TLVM_MOV_TO_L | TLVM_MOV_FROM_D)
#define TLVM_MOV_LE        (TLVM_MOV_TO_L | TLVM_MOV_FROM_E)
#define TLVM_MOV_LH        (TLVM_MOV_TO_L | TLVM_MOV_FROM_H)
#define TLVM_MOV_LL        (TLVM_MOV_TO_L | TLVM_MOV_FROM_L)
#define TLVM_MOV_LM        (TLVM_MOV_TO_L | TLVM_MOV_FROM_M)
#define TLVM_MOV_LA        (TLVM_MOV_TO_L | TLVM_MOV_FROM_A)

#define TLVM_MOV_MB        (TLVM_MOV_TO_M | TLVM_MOV_FROM_B)
#define TLVM_MOV_MC        (TLVM_MOV_TO_M | TLVM_MOV_FROM_C)
#define TLVM_MOV_MD        (TLVM_MOV_TO_M | TLVM_MOV_FROM_D)
#define TLVM_MOV_ME        (TLVM_MOV_TO_M | TLVM_MOV_FROM_E)
#define TLVM_MOV_MH        (TLVM_MOV_TO_M | TLVM_MOV_FROM_H)
#define TLVM_MOV_ML        (TLVM_MOV_TO_M | TLVM_MOV_FROM_L)
#define TLVM_MOV_MM        // doesn't exist
#define TLVM_MOV_MA        (TLVM_MOV_TO_M | TLVM_MOV_FROM_A)

#define TLVM_MOV_AB        (TLVM_MOV_TO_A | TLVM_MOV_FROM_B)
#define TLVM_MOV_AC        (TLVM_MOV_TO_A | TLVM_MOV_FROM_C)
#define TLVM_MOV_AD        (TLVM_MOV_TO_A | TLVM_MOV_FROM_D)
#define TLVM_MOV_AE        (TLVM_MOV_TO_A | TLVM_MOV_FROM_E)
#define TLVM_MOV_AH        (TLVM_MOV_TO_A | TLVM_MOV_FROM_H)
#define TLVM_MOV_AL        (TLVM_MOV_TO_A | TLVM_MOV_FROM_L)
#define TLVM_MOV_AM        (TLVM_MOV_TO_A | TLVM_MOV_FROM_M)
#define TLVM_MOV_AA        (TLVM_MOV_TO_A | TLVM_MOV_FROM_A)
 
#define TLVM_ANA_B         0xA0
#define TLVM_ANA_C         0xA1
#define TLVM_ANA_D         0xA2
#define TLVM_ANA_E         0xA3
#define TLVM_ANA_H         0xA4
#define TLVM_ANA_L         0xA5
#define TLVM_ANA_M         0xA6
#define TLVM_ANA_A         0xA7
#define TLVM_ANI           0xE6
 
#define TLVM_ORA_B         0xB0
#define TLVM_ORA_C         0xB1
#define TLVM_ORA_D         0xB2
#define TLVM_ORA_E         0xB3
#define TLVM_ORA_H         0xB4
#define TLVM_ORA_L         0xB5
#define TLVM_ORA_M         0xB6
#define TLVM_ORA_A         0xB7
#define TLVM_ORI           0xF6
 
#define TLVM_XRA_B         0xA8
#define TLVM_XRA_C         0xA9
#define TLVM_XRA_D         0xAA
#define TLVM_XRA_E         0xAB
#define TLVM_XRA_H         0xAC
#define TLVM_XRA_L         0xAD
#define TLVM_XRA_M         0xAE
#define TLVM_XRA_A         0xAF
#define TLVM_XRI           0xEE

 #define TLVM_JNZ          0xC2
 #define TLVM_JZ           0xCA
 #define TLVM_JNC          0xD2
 #define TLVM_JC           0xDA
 #define TLVM_JPO          0xE2
 #define TLVM_JPE          0xEA
 #define TLVM_JP           0xF2
 #define TLVM_JM           0xFA
 #define TLVM_JMP          0xC3

 #define TLVM_CNZ          0xC4
 #define TLVM_CZ           0xCC
 #define TLVM_CNC          0xD4
 #define TLVM_CC           0xDC
 #define TLVM_CPO          0xE4
 #define TLVM_CPE          0xEC
 #define TLVM_CP           0xF4
 #define TLVM_CM           0xFC
 #define TLVM_CALL         0xCD

 #define TLVM_RNZ          0xC0
 #define TLVM_RZ           0xC8
 #define TLVM_RNC          0xD0
 #define TLVM_RC           0xD8
 #define TLVM_RPO          0xE0
 #define TLVM_RPE          0xE8
 #define TLVM_RP           0xF0
 #define TLVM_RM           0xF8
 #define TLVM_RET          0xC9

 #define TLVM_PUSH_B       0xC5
 #define TLVM_PUSH_D       0xD5
 #define TLVM_PUSH_H       0xE5
 #define TLVM_PUSH_PSW     0xF5

 #define TLVM_POP_B        0xC1
 #define TLVM_POP_D        0xD1
 #define TLVM_POP_H        0xE1
 #define TLVM_POP_PSW      0xF1

 #define TLVM_SPHL         0xF9
 #define TLVM_XTHL         0xE3
 #define TLVM_PCHL         0xE9
 #define TLVM_XCHG         0xEB

 #define TLVM_STA          0x32 // set stack pointer

 #define TLVM_OUT          0xD3
 #define TLVM_IN           0xDB

 #define TLVM_RST_0        0xC7
 #define TLVM_RST_1        0xCF
 #define TLVM_RST_2        0xD7
 #define TLVM_RST_3        0xDF
 #define TLVM_RST_4        0xE7
 #define TLVM_RST_5        0xEF
 #define TLVM_RST_6        0xF7
 #define TLVM_RST_7        0xFF

 #define TLVM_DI           0xF3 // Disable hardware interrupts
 #define TLVM_EI           0xFB // Enable hardware interrupts

 #define TLVM_ADD_B        0x80 // add register B to A
 #define TLVM_ADD_C        0x81 // add register C to A
 #define TLVM_ADD_D        0x82 // add register D to A
 #define TLVM_ADD_E        0x83 // add register E to A
 #define TLVM_ADD_H        0x84 // add register H to A
 #define TLVM_ADD_L        0x85 // add register L to A
 #define TLVM_ADD_M        0x86 // add (HL) to A
 #define TLVM_ADD_A        0x87 // add register A to A

 #define TLVM_ADC_B        0x88 // add register B to A with carry
 #define TLVM_ADC_C        0x89 // add register C to A with carry
 #define TLVM_ADC_D        0x8A // add register D to A with carry
 #define TLVM_ADC_E        0x8B // add register E to A with carry
 #define TLVM_ADC_H        0x8C // add register H to A with carry
 #define TLVM_ADC_L        0x8D // add register L to A with carry
 #define TLVM_ADC_M        0x8E // add (HL) to A with carry
 #define TLVM_ADC_A        0x8F // add register A to A with carry

 #define TLVM_SUB_B        0x90 // add register B to A
 #define TLVM_SUB_C        0x91 // add register C to A
 #define TLVM_SUB_D        0x92 // add register D to A
 #define TLVM_SUB_E        0x93 // add register E to A
 #define TLVM_SUB_H        0x94 // add register H to A
 #define TLVM_SUB_L        0x95 // add register L to A
 #define TLVM_SUB_M        0x96 // add (HL) to A
 #define TLVM_SUB_A        0x97 // add register A to A

 #define TLVM_SBB_B        0x98 // add register B to A with borrow
 #define TLVM_SBB_C        0x99 // add register C to A with borrow
 #define TLVM_SBB_D        0x9A // add register D to A with borrow
 #define TLVM_SBB_E        0x9B // add register E to A with borrow
 #define TLVM_SBB_H        0x9C // add register H to A with borrow
 #define TLVM_SBB_L        0x9D // add register L to A with borrow
 #define TLVM_SBB_M        0x9E // add (HL) to A with borrow
 #define TLVM_SBB_A        0x9F // add register A to A with borrow

 #define TLVM_CMP_B        0xB8 // compare register B to A
 #define TLVM_CMP_C        0xB9 // compare register C to A
 #define TLVM_CMP_D        0xBA // compare register D to A
 #define TLVM_CMP_E        0xBB // compare register E to A
 #define TLVM_CMP_H        0xBC // compare register H to A
 #define TLVM_CMP_L        0xBD // compare register L to A
 #define TLVM_CMP_M        0xBE // compare (HL) to A
 #define TLVM_CMP_A        0xBF // compare register A to A

 #define TLVM_DAD_B        0x09 // add register pair BC to HL
 #define TLVM_DAD_D        0x19 // add register pair DE to HL
 #define TLVM_DAD_H        0x29 // add register pair HL to HL
 #define TLVM_DAD_SP       0x39 // add register SP to HL
 
 #define TLVM_ADI          0xC6 // add immediate to A
 #define TLVM_ACI          0xCE // add immediate to A with carry
 #define TLVM_SUI          0xD6 // subtract immediate from A
 #define TLVM_SBI          0xDE // subtract immediate from A with borrow
 #define TLVM_CPI          0xFE // compare immediate with A

 #define TLVM_INR_B        0x04
 #define TLVM_INR_C        0x0C
 #define TLVM_INR_D        0x14
 #define TLVM_INR_E        0x1C
 #define TLVM_INR_H        0x24
 #define TLVM_INR_L        0x2C
 #define TLVM_INR_M        0x34
 #define TLVM_INR_A        0x3C

 #define TLVM_INX_B		   0x03
 #define TLVM_INX_D		   0x13
 #define TLVM_INX_H		   0x23
 #define TLVM_INX_SP	   0x33

 #define TLVM_DCR_B        0x05
 #define TLVM_DCR_C        0x0D
 #define TLVM_DCR_D        0x15
 #define TLVM_DCR_E        0x1D
 #define TLVM_DCR_H        0x25
 #define TLVM_DCR_L        0x2D
 #define TLVM_DCR_M        0x35
 #define TLVM_DCR_A        0x3D

 #define TLVM_DCX_B		   0x0B
 #define TLVM_DCX_D		   0x1B
 #define TLVM_DCX_H		   0x2B
 #define TLVM_DCX_SP	   0x3B

/*********************************************
 * MOV HELPERS
 *********************************************/
#define TLVM_MOV_FROM_B    0x00
#define TLVM_MOV_FROM_C    0x01
#define TLVM_MOV_FROM_D    0x02
#define TLVM_MOV_FROM_E    0x03
#define TLVM_MOV_FROM_H    0x04
#define TLVM_MOV_FROM_L    0x05
#define TLVM_MOV_FROM_M    0x06
#define TLVM_MOV_FROM_A    0x07

#define TLVM_MOV_HI        0x08

#define TLVM_MOV_TO_B      0x40
#define TLVM_MOV_TO_C      0x48
#define TLVM_MOV_TO_D      0x50
#define TLVM_MOV_TO_E      0x58
#define TLVM_MOV_TO_H      0x60
#define TLVM_MOV_TO_L      0x68
#define TLVM_MOV_TO_M      0x70
#define TLVM_MOV_TO_A      0x78


/*********************************************
 * Core instructions
 *********************************************/
tlvmReturn tlvmNOP  (tlvmContext* context, tlvmByte* cycles);
tlvmReturn tlvmHLT  (tlvmContext* context, tlvmByte* cycles);
tlvmReturn tlvmLXI  (tlvmContext* context, tlvmByte* cycles);
tlvmReturn tlvmSTAX (tlvmContext* context, tlvmByte* cycles);
tlvmReturn tlvmMVI  (tlvmContext* context, tlvmByte* cycles);
tlvmReturn tlvmLDAX (tlvmContext* context, tlvmByte* cycles);
tlvmReturn tlvmSHLD (tlvmContext* context, tlvmByte* cycles);
tlvmReturn tlvmLHLD (tlvmContext* context, tlvmByte* cycles);
tlvmReturn tlvmLDA  (tlvmContext* context, tlvmByte* cycles);
tlvmReturn tlvmMOV  (tlvmContext* context, tlvmByte* cycles);
tlvmReturn tlvmANA  (tlvmContext* context, tlvmByte* cycles);
tlvmReturn tlvmANI  (tlvmContext* context, tlvmByte* cycles);
tlvmReturn tlvmORA  (tlvmContext* context, tlvmByte* cycles);
tlvmReturn tlvmORI  (tlvmContext* context, tlvmByte* cycles);
tlvmReturn tlvmXRA  (tlvmContext* context, tlvmByte* cycles);
tlvmReturn tlvmXRI  (tlvmContext* context, tlvmByte* cycles);
tlvmReturn tlvmPUSH (tlvmContext* context, tlvmByte* cycles);
tlvmReturn tlvmPOP  (tlvmContext* context, tlvmByte* cycles);
tlvmReturn tlvmSPHL (tlvmContext* context, tlvmByte* cycles);
tlvmReturn tlvmXTHL (tlvmContext* context, tlvmByte* cycles);
tlvmReturn tlvmXCHG (tlvmContext* context, tlvmByte* cycles);
tlvmReturn tlvmPCHL (tlvmContext* context, tlvmByte* cycles);
tlvmReturn tlvmJMP  (tlvmContext* context, tlvmByte* cycles);
tlvmReturn tlvmCALL (tlvmContext* context, tlvmByte* cycles);
tlvmReturn tlvmRET  (tlvmContext* context, tlvmByte* cycles);
tlvmReturn tlvmSTA  (tlvmContext* context, tlvmByte* cycles);
tlvmReturn tlvmOUT  (tlvmContext* context, tlvmByte* cycles);
tlvmReturn tlvmIN   (tlvmContext* context, tlvmByte* cycles);
tlvmReturn tlvmRST  (tlvmContext* context, tlvmByte* cycles);
tlvmReturn tlvmEI   (tlvmContext* context, tlvmByte* cycles);
tlvmReturn tlvmDI   (tlvmContext* context, tlvmByte* cycles);
tlvmReturn tlvmSTC  (tlvmContext* context, tlvmByte* cycles);
tlvmReturn tlvmCMC  (tlvmContext* context, tlvmByte* cycles);
tlvmReturn tlvmCMA  (tlvmContext* context, tlvmByte* cycles);

/*********************************************
 * ALU instructions
 *********************************************/
tlvmReturn tlvmADD  (tlvmContext* context, tlvmByte* cycles);
tlvmReturn tlvmADI  (tlvmContext* context, tlvmByte* cycles);
tlvmReturn tlvmCMP  (tlvmContext* context, tlvmByte* cycles);

tlvmReturn tlvmSUB  (tlvmContext* context, tlvmByte* cycles);
tlvmReturn tlvmSUI  (tlvmContext* context, tlvmByte* cycles);
tlvmReturn tlvmCPI  (tlvmContext* context, tlvmByte* cycles);

tlvmReturn tlvmINR  (tlvmContext* context, tlvmByte* cycles);
tlvmReturn tlvmDCR  (tlvmContext* context, tlvmByte* cycles);

tlvmReturn tlvmINX  (tlvmContext* context, tlvmByte* cycles);
tlvmReturn tlvmDCX  (tlvmContext* context, tlvmByte* cycles);

tlvmReturn tlvmDAD  (tlvmContext* context, tlvmByte* cycles);

tlvmReturn tlvmROT  (tlvmContext* context, tlvmByte* cycles);
tlvmReturn tlvmDAA  (tlvmContext* context, tlvmByte* cycles);

/*********************************************
 * tlvmAdd8080
 *     Add Intel 8080 instruction set to CPU
 * parameters:
 *     context - the CPU context to add 8080 
 *     support to
 *********************************************/
tlvmReturn  tlvmAdd8080Instructions(tlvmContext* context);

tlvmReturn tlvm8080GetPort(tlvmContext* context, tlvmByte port, tlvmByte* outPort);
tlvmReturn tlvm8080SetPort(tlvmContext* context, tlvmByte port, tlvmByte portval);
tlvmReturn tlvm8080Interrupt(tlvmContext* context, tlvmByte interrupt);
tlvmReturn tlvm8080HandleInterrupt(tlvmContext* context, tlvmByte interrupt);

typedef struct _tlvm8080data
{
	tlvmProcessorData m_Header;
	tlvm8080IOCallback m_IOCallback;
} tlvm8080data;

#endif/*TLVM_HAS_8080*/
#endif/*__8080_H__*/
