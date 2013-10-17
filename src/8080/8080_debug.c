#include "tlvm_internal.h"

#include <stdio.h>

#ifdef  TLVM_HAS_8080
#ifdef  TLVM_DEBUG

#define TLVM_DEBUG_SIMPLE_OP(op, instr) \
if(opcode == TLVM_##op) \
{ \
	sprintf((char*)*instruction, instr); \
	tlvmReturnCode(SUCCESS); \
}

#define TLVM_DEBUG_SIMPLE_OPCODE(op) TLVM_DEBUG_SIMPLE_OP(op, #op)

#define TLVM_DEBUG_8BIT_OP(op, instr) \
if(opcode == TLVM_##op) \
{ \
	TLVM_GET_OP(operand, 1); \
	sprintf((char*)*instruction, "%s 0x%02x", instr, operand); \
	tlvmReturnCode(SUCCESS); \
}

#define TLVM_DEBUG_16BIT_OP(op, instr) \
if(opcode == TLVM_##op) \
{ \
	TLVM_GET_OP(opLow, 1); \
	TLVM_GET_OP(opHigh, 2); \
	tlvmShort operand = (tlvmShort)opHigh << 8 | (tlvmShort)opLow; \
	sprintf((char*)*instruction, "%s 0x%04x", instr, operand); \
	tlvmReturnCode(SUCCESS); \
}

tlvmReturn tlvm8080DebugGetInstruction(tlvmContext* context, tlvmChar** instruction)
{
	if(context == NULL)
		tlvmReturnCode(NO_CONTEXT);

    TLVM_GET_OP(opcode, 0);

    TLVM_DEBUG_SIMPLE_OPCODE(NOP);
    TLVM_DEBUG_SIMPLE_OP(MOV_BB, "MOV B B");
    TLVM_DEBUG_SIMPLE_OP(MOV_BC, "MOV B C");
    TLVM_DEBUG_SIMPLE_OP(MOV_BD, "MOV B D");
    TLVM_DEBUG_SIMPLE_OP(MOV_BE, "MOV B E");
    TLVM_DEBUG_SIMPLE_OP(MOV_BH, "MOV B H");
    TLVM_DEBUG_SIMPLE_OP(MOV_BL, "MOV B L");
    TLVM_DEBUG_SIMPLE_OP(MOV_BM, "MOV B M");
    TLVM_DEBUG_SIMPLE_OP(MOV_BA, "MOV B A");

    TLVM_DEBUG_SIMPLE_OP(MOV_CB, "MOV C B");
    TLVM_DEBUG_SIMPLE_OP(MOV_CC, "MOV C C");
    TLVM_DEBUG_SIMPLE_OP(MOV_CD, "MOV C D");
    TLVM_DEBUG_SIMPLE_OP(MOV_CE, "MOV C E");
    TLVM_DEBUG_SIMPLE_OP(MOV_CH, "MOV C H");
    TLVM_DEBUG_SIMPLE_OP(MOV_CL, "MOV C L");
    TLVM_DEBUG_SIMPLE_OP(MOV_CM, "MOV C M");
    TLVM_DEBUG_SIMPLE_OP(MOV_CA, "MOV C A");

    TLVM_DEBUG_SIMPLE_OP(MOV_DB, "MOV D B");
    TLVM_DEBUG_SIMPLE_OP(MOV_DC, "MOV D C");
    TLVM_DEBUG_SIMPLE_OP(MOV_DD, "MOV D D");
    TLVM_DEBUG_SIMPLE_OP(MOV_DE, "MOV D E");
    TLVM_DEBUG_SIMPLE_OP(MOV_DH, "MOV D H");
    TLVM_DEBUG_SIMPLE_OP(MOV_DL, "MOV D L");
    TLVM_DEBUG_SIMPLE_OP(MOV_DM, "MOV D M");
    TLVM_DEBUG_SIMPLE_OP(MOV_DA, "MOV D A");

    TLVM_DEBUG_SIMPLE_OP(MOV_EB, "MOV E B");
    TLVM_DEBUG_SIMPLE_OP(MOV_EC, "MOV E C");
    TLVM_DEBUG_SIMPLE_OP(MOV_ED, "MOV E D");
    TLVM_DEBUG_SIMPLE_OP(MOV_EE, "MOV E E");
    TLVM_DEBUG_SIMPLE_OP(MOV_EH, "MOV E H");
    TLVM_DEBUG_SIMPLE_OP(MOV_EL, "MOV E L");
    TLVM_DEBUG_SIMPLE_OP(MOV_EM, "MOV E M");
    TLVM_DEBUG_SIMPLE_OP(MOV_EA, "MOV E A");

    TLVM_DEBUG_SIMPLE_OP(MOV_HB, "MOV H B");
    TLVM_DEBUG_SIMPLE_OP(MOV_HC, "MOV H C");
    TLVM_DEBUG_SIMPLE_OP(MOV_HD, "MOV H D");
    TLVM_DEBUG_SIMPLE_OP(MOV_HE, "MOV H E");
    TLVM_DEBUG_SIMPLE_OP(MOV_HH, "MOV H H");
    TLVM_DEBUG_SIMPLE_OP(MOV_HL, "MOV H L");
    TLVM_DEBUG_SIMPLE_OP(MOV_HM, "MOV H M");
    TLVM_DEBUG_SIMPLE_OP(MOV_HA, "MOV H A");

    TLVM_DEBUG_SIMPLE_OP(MOV_LB, "MOV L B");
    TLVM_DEBUG_SIMPLE_OP(MOV_LC, "MOV L C");
    TLVM_DEBUG_SIMPLE_OP(MOV_LD, "MOV L D");
    TLVM_DEBUG_SIMPLE_OP(MOV_LE, "MOV L E");
    TLVM_DEBUG_SIMPLE_OP(MOV_LH, "MOV L H");
    TLVM_DEBUG_SIMPLE_OP(MOV_LL, "MOV L L");
    TLVM_DEBUG_SIMPLE_OP(MOV_LM, "MOV L M");
    TLVM_DEBUG_SIMPLE_OP(MOV_LA, "MOV L A");

    TLVM_DEBUG_SIMPLE_OP(MOV_MB, "MOV M B");
    TLVM_DEBUG_SIMPLE_OP(MOV_MC, "MOV M C");
    TLVM_DEBUG_SIMPLE_OP(MOV_MD, "MOV M D");
    TLVM_DEBUG_SIMPLE_OP(MOV_ME, "MOV M E");
    TLVM_DEBUG_SIMPLE_OP(MOV_MH, "MOV M H");
    TLVM_DEBUG_SIMPLE_OP(MOV_ML, "MOV M L");
    //TLVM_DEBUG_SIMPLE_OP(MOV_MM, "MOV M M");
    TLVM_DEBUG_SIMPLE_OP(MOV_MA, "MOV M A");

    TLVM_DEBUG_SIMPLE_OP(MOV_AB, "MOV A B");
    TLVM_DEBUG_SIMPLE_OP(MOV_AC, "MOV A C");
    TLVM_DEBUG_SIMPLE_OP(MOV_AD, "MOV A D");
    TLVM_DEBUG_SIMPLE_OP(MOV_AE, "MOV A E");
    TLVM_DEBUG_SIMPLE_OP(MOV_AH, "MOV A H");
    TLVM_DEBUG_SIMPLE_OP(MOV_AL, "MOV A L");
    TLVM_DEBUG_SIMPLE_OP(MOV_AM, "MOV A M");
    TLVM_DEBUG_SIMPLE_OP(MOV_AA, "MOV A A");

    TLVM_DEBUG_8BIT_OP(MVI_B, "MVI B");
    TLVM_DEBUG_8BIT_OP(MVI_C, "MVI C");
    TLVM_DEBUG_8BIT_OP(MVI_D, "MVI D");
    TLVM_DEBUG_8BIT_OP(MVI_E, "MVI E");
    TLVM_DEBUG_8BIT_OP(MVI_H, "MVI H");
    TLVM_DEBUG_8BIT_OP(MVI_L, "MVI L");
    TLVM_DEBUG_8BIT_OP(MVI_M, "MVI M");
    TLVM_DEBUG_8BIT_OP(MVI_A, "MVI A");

    TLVM_DEBUG_16BIT_OP(LXI_B, "LXI B");
    TLVM_DEBUG_16BIT_OP(LXI_D, "LXI D");
    TLVM_DEBUG_16BIT_OP(LXI_H, "LXI H");

    sprintf((char*)*instruction, "UNKNOWN");
    tlvmReturnCode(UNKNOWN_INSTRUCTION);
}

#endif/*TLVM_DEBUG*/
#endif/*TLVM_HAS_8080*/