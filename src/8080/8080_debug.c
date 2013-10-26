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

#define TLVM_DEBUG_REG(reg) \
(strcmp((const char*)regstr, #reg) == 0)

#define TLVM_DEBUG_CHECK_REG(reg) \
if(TLVM_DEBUG_REG(reg)) \
{ \
	*outreg = TLVM_REG_##reg; \
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

    TLVM_DEBUG_8BIT_OP(ACI, "ACI");
    TLVM_DEBUG_8BIT_OP(SBI, "SBI");
    TLVM_DEBUG_8BIT_OP(XRI, "XRI");
    TLVM_DEBUG_8BIT_OP(CPI, "CPI");

    TLVM_DEBUG_16BIT_OP(LXI_B, "LXI B");
    TLVM_DEBUG_16BIT_OP(LXI_D, "LXI D");
    TLVM_DEBUG_16BIT_OP(LXI_H, "LXI H");
    TLVM_DEBUG_16BIT_OP(LXI_SP, "LXI SP");

    TLVM_DEBUG_SIMPLE_OP(LDAX_B, "LDAX B");
    TLVM_DEBUG_SIMPLE_OP(LDAX_D, "LDAX D");

    TLVM_DEBUG_SIMPLE_OP(STAX_B, "STAX B");
    TLVM_DEBUG_SIMPLE_OP(STAX_D, "STAX D");

    TLVM_DEBUG_16BIT_OP(SHLD, "SHLD");

    TLVM_DEBUG_16BIT_OP(STA, "STA");

    TLVM_DEBUG_SIMPLE_OP(INX_B, "INX B");
    TLVM_DEBUG_SIMPLE_OP(INX_D, "INX D");
    TLVM_DEBUG_SIMPLE_OP(INX_H, "INX H");
    TLVM_DEBUG_SIMPLE_OP(INX_SP, "INX SP");

    TLVM_DEBUG_SIMPLE_OP(INR_B, "INR B");
    TLVM_DEBUG_SIMPLE_OP(INR_D, "INR D");
    TLVM_DEBUG_SIMPLE_OP(INR_H, "INR H");
    TLVM_DEBUG_SIMPLE_OP(INR_M, "INR M");
    TLVM_DEBUG_SIMPLE_OP(INR_C, "INR C");
    TLVM_DEBUG_SIMPLE_OP(INR_E, "INR E");
    TLVM_DEBUG_SIMPLE_OP(INR_L, "INR L");
    TLVM_DEBUG_SIMPLE_OP(INR_A, "INR A");

    TLVM_DEBUG_SIMPLE_OP(DCX_B, "DCX B");
    TLVM_DEBUG_SIMPLE_OP(DCX_D, "DCX D");
    TLVM_DEBUG_SIMPLE_OP(DCX_H, "DCX H");
    TLVM_DEBUG_SIMPLE_OP(DCX_SP, "DCX SP");

    TLVM_DEBUG_SIMPLE_OP(DCR_B, "DCR B");
    TLVM_DEBUG_SIMPLE_OP(DCR_D, "DCR D");
    TLVM_DEBUG_SIMPLE_OP(DCR_H, "DCR H");
    TLVM_DEBUG_SIMPLE_OP(DCR_M, "DCR M");
    TLVM_DEBUG_SIMPLE_OP(DCR_C, "DCR C");
    TLVM_DEBUG_SIMPLE_OP(DCR_E, "DCR E");
    TLVM_DEBUG_SIMPLE_OP(DCR_L, "DCR L");
    TLVM_DEBUG_SIMPLE_OP(DCR_A, "DCR A");

    TLVM_DEBUG_SIMPLE_OP(ADD_B, "ADD B");
    TLVM_DEBUG_SIMPLE_OP(ADD_C, "ADD C");
    TLVM_DEBUG_SIMPLE_OP(ADD_D, "ADD D");
    TLVM_DEBUG_SIMPLE_OP(ADD_E, "ADD E");
    TLVM_DEBUG_SIMPLE_OP(ADD_H, "ADD H");
    TLVM_DEBUG_SIMPLE_OP(ADD_L, "ADD L");
    TLVM_DEBUG_SIMPLE_OP(ADD_M, "ADD M");
    TLVM_DEBUG_SIMPLE_OP(ADD_A, "ADD A");

    TLVM_DEBUG_SIMPLE_OP(ADC_B, "ADC B");
    TLVM_DEBUG_SIMPLE_OP(ADC_C, "ADC C");
    TLVM_DEBUG_SIMPLE_OP(ADC_D, "ADC D");
    TLVM_DEBUG_SIMPLE_OP(ADC_E, "ADC E");
    TLVM_DEBUG_SIMPLE_OP(ADC_H, "ADC H");
    TLVM_DEBUG_SIMPLE_OP(ADC_L, "ADC L");
    TLVM_DEBUG_SIMPLE_OP(ADC_M, "ADC M");
    TLVM_DEBUG_SIMPLE_OP(ADC_A, "ADC A");

    TLVM_DEBUG_SIMPLE_OP(SUB_B, "SUB B");
    TLVM_DEBUG_SIMPLE_OP(SUB_C, "SUB C");
    TLVM_DEBUG_SIMPLE_OP(SUB_D, "SUB D");
    TLVM_DEBUG_SIMPLE_OP(SUB_E, "SUB E");
    TLVM_DEBUG_SIMPLE_OP(SUB_H, "SUB H");
    TLVM_DEBUG_SIMPLE_OP(SUB_L, "SUB L");
    TLVM_DEBUG_SIMPLE_OP(SUB_M, "SUB M");
    TLVM_DEBUG_SIMPLE_OP(SUB_A, "SUB A");

    TLVM_DEBUG_SIMPLE_OP(SBB_B, "SBB B");
    TLVM_DEBUG_SIMPLE_OP(SBB_C, "SBB C");
    TLVM_DEBUG_SIMPLE_OP(SBB_D, "SBB D");
    TLVM_DEBUG_SIMPLE_OP(SBB_E, "SBB E");
    TLVM_DEBUG_SIMPLE_OP(SBB_H, "SBB H");
    TLVM_DEBUG_SIMPLE_OP(SBB_L, "SBB L");
    TLVM_DEBUG_SIMPLE_OP(SBB_M, "SBB M");
    TLVM_DEBUG_SIMPLE_OP(SBB_A, "SBB A");

	TLVM_DEBUG_SIMPLE_OP(ANA_B, "ANA B");
	TLVM_DEBUG_SIMPLE_OP(ANA_C, "ANA C");
	TLVM_DEBUG_SIMPLE_OP(ANA_D, "ANA D");
	TLVM_DEBUG_SIMPLE_OP(ANA_E, "ANA E");
	TLVM_DEBUG_SIMPLE_OP(ANA_H, "ANA H");
	TLVM_DEBUG_SIMPLE_OP(ANA_L, "ANA L");
	TLVM_DEBUG_SIMPLE_OP(ANA_M, "ANA M");
	TLVM_DEBUG_SIMPLE_OP(ANA_A, "ANA A");
	
	TLVM_DEBUG_SIMPLE_OP(ORA_B, "ORA B");
	TLVM_DEBUG_SIMPLE_OP(ORA_C, "ORA C");
	TLVM_DEBUG_SIMPLE_OP(ORA_D, "ORA D");
	TLVM_DEBUG_SIMPLE_OP(ORA_E, "ORA E");
	TLVM_DEBUG_SIMPLE_OP(ORA_H, "ORA H");
	TLVM_DEBUG_SIMPLE_OP(ORA_L, "ORA L");
	TLVM_DEBUG_SIMPLE_OP(ORA_M, "ORA M");
	TLVM_DEBUG_SIMPLE_OP(ORA_A, "ORA A");
	
	TLVM_DEBUG_SIMPLE_OP(XRA_B, "XRA B");
	TLVM_DEBUG_SIMPLE_OP(XRA_C, "XRA C");
	TLVM_DEBUG_SIMPLE_OP(XRA_D, "XRA D");
	TLVM_DEBUG_SIMPLE_OP(XRA_E, "XRA E");
	TLVM_DEBUG_SIMPLE_OP(XRA_H, "XRA H");
	TLVM_DEBUG_SIMPLE_OP(XRA_L, "XRA L");
	TLVM_DEBUG_SIMPLE_OP(XRA_M, "XRA M");
	TLVM_DEBUG_SIMPLE_OP(XRA_A, "XRA A");
	
	TLVM_DEBUG_SIMPLE_OP(CMP_B, "CMP B");
	TLVM_DEBUG_SIMPLE_OP(CMP_C, "CMP C");
	TLVM_DEBUG_SIMPLE_OP(CMP_D, "CMP D");
	TLVM_DEBUG_SIMPLE_OP(CMP_E, "CMP E");
	TLVM_DEBUG_SIMPLE_OP(CMP_H, "CMP H");
	TLVM_DEBUG_SIMPLE_OP(CMP_L, "CMP L");
	TLVM_DEBUG_SIMPLE_OP(CMP_M, "CMP M");
	TLVM_DEBUG_SIMPLE_OP(CMP_A, "CMP A");

	TLVM_DEBUG_8BIT_OP(ADI, "ADI");
	TLVM_DEBUG_8BIT_OP(SUI, "SUI");
	TLVM_DEBUG_8BIT_OP(ANI, "ANI");
	TLVM_DEBUG_8BIT_OP(ORI, "ORI");

    TLVM_DEBUG_SIMPLE_OPCODE(RZ);
    TLVM_DEBUG_SIMPLE_OPCODE(RNZ);
    TLVM_DEBUG_SIMPLE_OPCODE(RC);
    TLVM_DEBUG_SIMPLE_OPCODE(RNC);
    TLVM_DEBUG_SIMPLE_OPCODE(RPE);
    TLVM_DEBUG_SIMPLE_OPCODE(RPO);
    TLVM_DEBUG_SIMPLE_OPCODE(RM);
    TLVM_DEBUG_SIMPLE_OPCODE(RP);

    TLVM_DEBUG_SIMPLE_OPCODE(RET);

	TLVM_DEBUG_SIMPLE_OP(POP_B, "POP B");
	TLVM_DEBUG_SIMPLE_OP(POP_D, "POP D");
	TLVM_DEBUG_SIMPLE_OP(POP_H, "POP H");
	TLVM_DEBUG_SIMPLE_OP(POP_PSW, "POP PSW");

	TLVM_DEBUG_SIMPLE_OP(PUSH_B, "PUSH B");
	TLVM_DEBUG_SIMPLE_OP(PUSH_D, "PUSH D");
	TLVM_DEBUG_SIMPLE_OP(PUSH_H, "PUSH H");
	TLVM_DEBUG_SIMPLE_OP(PUSH_PSW, "PUSH PSW");

    TLVM_DEBUG_16BIT_OP(JZ, "JZ");
    TLVM_DEBUG_16BIT_OP(JNZ, "JNZ");
    TLVM_DEBUG_16BIT_OP(JC, "JC");
    TLVM_DEBUG_16BIT_OP(JNC, "JNC");
    TLVM_DEBUG_16BIT_OP(JPE, "JPE");
    TLVM_DEBUG_16BIT_OP(JPO, "JPO");
    TLVM_DEBUG_16BIT_OP(JM,  "JM");
    TLVM_DEBUG_16BIT_OP(JP,  "JP");

	TLVM_DEBUG_16BIT_OP(JMP, "JMP");

    TLVM_DEBUG_8BIT_OP(IN, "IN");
    TLVM_DEBUG_8BIT_OP(OUT, "OUT");

	TLVM_DEBUG_SIMPLE_OPCODE(XTHL);

	TLVM_DEBUG_SIMPLE_OPCODE(EI);
	TLVM_DEBUG_SIMPLE_OPCODE(DI);

    TLVM_DEBUG_16BIT_OP(CZ, "CZ");
    TLVM_DEBUG_16BIT_OP(CNZ, "CNZ");
    TLVM_DEBUG_16BIT_OP(CC, "CC");
    TLVM_DEBUG_16BIT_OP(CNC, "CNC");
    TLVM_DEBUG_16BIT_OP(CPE, "CPE");
    TLVM_DEBUG_16BIT_OP(CPO, "CPO");
    TLVM_DEBUG_16BIT_OP(CM,  "CM");
    TLVM_DEBUG_16BIT_OP(CP,  "CP");

    TLVM_DEBUG_16BIT_OP(CALL,  "CALL");

	TLVM_DEBUG_SIMPLE_OP(DAD_B, "DAD_B");
	TLVM_DEBUG_SIMPLE_OP(DAD_D, "DAD_D");
	TLVM_DEBUG_SIMPLE_OP(DAD_H, "DAD_H");
	TLVM_DEBUG_SIMPLE_OP(DAD_SP, "DAD_SP");

	TLVM_DEBUG_SIMPLE_OP(RST_0, "RST 0");
	TLVM_DEBUG_SIMPLE_OP(RST_1, "RST 1");
	TLVM_DEBUG_SIMPLE_OP(RST_2, "RST 2");
	TLVM_DEBUG_SIMPLE_OP(RST_3, "RST 3");
	TLVM_DEBUG_SIMPLE_OP(RST_4, "RST 4");
	TLVM_DEBUG_SIMPLE_OP(RST_5, "RST 5");
	TLVM_DEBUG_SIMPLE_OP(RST_6, "RST 6");
	TLVM_DEBUG_SIMPLE_OP(RST_7, "RST 7");

    sprintf((char*)*instruction, "UNKNOWN 0x%X", opcode);
    tlvmReturnCode(UNKNOWN_INSTRUCTION);
}

tlvmReturn tlvm8080DebugParseRegister(tlvmContext* context, tlvmChar* regstr, tlvmByte* outreg)
{
	if(context == NULL)
		tlvmReturnCode(NO_CONTEXT);
	if(outreg == NULL)
		tlvmReturnCode(INVALID_INPUT);

	TLVM_DEBUG_CHECK_REG(B);
	TLVM_DEBUG_CHECK_REG(C);
	TLVM_DEBUG_CHECK_REG(D);
	TLVM_DEBUG_CHECK_REG(E);
	TLVM_DEBUG_CHECK_REG(H);
	TLVM_DEBUG_CHECK_REG(L);
	TLVM_DEBUG_CHECK_REG(A);
	TLVM_DEBUG_CHECK_REG(F);

    tlvmReturnCode(UNKNOWN_INSTRUCTION);
}

#endif/*TLVM_DEBUG*/
#endif/*TLVM_HAS_8080*/