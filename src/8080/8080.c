#include "tlvm_internal.h"

tlvmReturn tlvmAdd8080(tlvmContext* context)
{
    if(context == NULL)
        tlvmReturnCode(NO_CONTEXT);
    
    context->m_InstructionSet[TLVM_NOP]      = tlvmNOP;
    context->m_InstructionSet[TLVM_HLT]      = tlvmHLT;
      
    context->m_InstructionSet[TLVM_LXI_B]    = tlvmLXI;
    context->m_InstructionSet[TLVM_LXI_D]    = tlvmLXI;
    context->m_InstructionSet[TLVM_LXI_H]    = tlvmLXI;
    context->m_InstructionSet[TLVM_LXI_SP]   = tlvmLXI;
      
    context->m_InstructionSet[TLVM_LDAX_B]   = tlvmLDAX;
    context->m_InstructionSet[TLVM_LDAX_D]   = tlvmLDAX;
  
    context->m_InstructionSet[TLVM_STAX_B]   = tlvmSTAX;
    context->m_InstructionSet[TLVM_STAX_D]   = tlvmSTAX;
      
    context->m_InstructionSet[TLVM_MVI_B]    = tlvmMVI;
    context->m_InstructionSet[TLVM_MVI_C]    = tlvmMVI;
    context->m_InstructionSet[TLVM_MVI_D]    = tlvmMVI;
    context->m_InstructionSet[TLVM_MVI_E]    = tlvmMVI;
    context->m_InstructionSet[TLVM_MVI_H]    = tlvmMVI;
    context->m_InstructionSet[TLVM_MVI_L]    = tlvmMVI;
    context->m_InstructionSet[TLVM_MVI_M]    = tlvmMVI;
    context->m_InstructionSet[TLVM_MVI_A]    = tlvmMVI;
  
    context->m_InstructionSet[TLVM_LDA]      = tlvmLDA;
    
    context->m_InstructionSet[TLVM_MOV_BB]   = tlvmMOV;
    context->m_InstructionSet[TLVM_MOV_BC]   = tlvmMOV;
    context->m_InstructionSet[TLVM_MOV_BD]   = tlvmMOV;
    context->m_InstructionSet[TLVM_MOV_BE]   = tlvmMOV;
    context->m_InstructionSet[TLVM_MOV_BH]   = tlvmMOV;
    context->m_InstructionSet[TLVM_MOV_BL]   = tlvmMOV;
    context->m_InstructionSet[TLVM_MOV_BM]   = tlvmMOV;
    context->m_InstructionSet[TLVM_MOV_BA]   = tlvmMOV;
    
    context->m_InstructionSet[TLVM_MOV_CB]   = tlvmMOV;
    context->m_InstructionSet[TLVM_MOV_CC]   = tlvmMOV;
    context->m_InstructionSet[TLVM_MOV_CD]   = tlvmMOV;
    context->m_InstructionSet[TLVM_MOV_CE]   = tlvmMOV;
    context->m_InstructionSet[TLVM_MOV_CH]   = tlvmMOV;
    context->m_InstructionSet[TLVM_MOV_CL]   = tlvmMOV;
    context->m_InstructionSet[TLVM_MOV_CM]   = tlvmMOV;
    context->m_InstructionSet[TLVM_MOV_CA]   = tlvmMOV;
    
    context->m_InstructionSet[TLVM_MOV_DB]   = tlvmMOV;
    context->m_InstructionSet[TLVM_MOV_DC]   = tlvmMOV;
    context->m_InstructionSet[TLVM_MOV_DD]   = tlvmMOV;
    context->m_InstructionSet[TLVM_MOV_DE]   = tlvmMOV;
    context->m_InstructionSet[TLVM_MOV_DH]   = tlvmMOV;
    context->m_InstructionSet[TLVM_MOV_DL]   = tlvmMOV;
    context->m_InstructionSet[TLVM_MOV_DM]   = tlvmMOV;
    context->m_InstructionSet[TLVM_MOV_DA]   = tlvmMOV;
    
    context->m_InstructionSet[TLVM_MOV_EB]   = tlvmMOV;
    context->m_InstructionSet[TLVM_MOV_EC]   = tlvmMOV;
    context->m_InstructionSet[TLVM_MOV_ED]   = tlvmMOV;
    context->m_InstructionSet[TLVM_MOV_EE]   = tlvmMOV;
    context->m_InstructionSet[TLVM_MOV_EH]   = tlvmMOV;
    context->m_InstructionSet[TLVM_MOV_EL]   = tlvmMOV;
    context->m_InstructionSet[TLVM_MOV_EM]   = tlvmMOV;
    context->m_InstructionSet[TLVM_MOV_EA]   = tlvmMOV;
    
    context->m_InstructionSet[TLVM_MOV_HB]   = tlvmMOV;
    context->m_InstructionSet[TLVM_MOV_HC]   = tlvmMOV;
    context->m_InstructionSet[TLVM_MOV_HD]   = tlvmMOV;
    context->m_InstructionSet[TLVM_MOV_HE]   = tlvmMOV;
    context->m_InstructionSet[TLVM_MOV_HH]   = tlvmMOV;
    context->m_InstructionSet[TLVM_MOV_HL]   = tlvmMOV;
    context->m_InstructionSet[TLVM_MOV_HM]   = tlvmMOV;
    context->m_InstructionSet[TLVM_MOV_HA]   = tlvmMOV;
    
    context->m_InstructionSet[TLVM_MOV_LB]   = tlvmMOV;
    context->m_InstructionSet[TLVM_MOV_LC]   = tlvmMOV;
    context->m_InstructionSet[TLVM_MOV_LD]   = tlvmMOV;
    context->m_InstructionSet[TLVM_MOV_LE]   = tlvmMOV;
    context->m_InstructionSet[TLVM_MOV_LH]   = tlvmMOV;
    context->m_InstructionSet[TLVM_MOV_LL]   = tlvmMOV;
    context->m_InstructionSet[TLVM_MOV_LM]   = tlvmMOV;
    context->m_InstructionSet[TLVM_MOV_LA]   = tlvmMOV;
    
    context->m_InstructionSet[TLVM_MOV_MB]   = tlvmMOV;
    context->m_InstructionSet[TLVM_MOV_MC]   = tlvmMOV;
    context->m_InstructionSet[TLVM_MOV_MD]   = tlvmMOV;
    context->m_InstructionSet[TLVM_MOV_ME]   = tlvmMOV;
    context->m_InstructionSet[TLVM_MOV_MH]   = tlvmMOV;
    context->m_InstructionSet[TLVM_MOV_ML]   = tlvmMOV;
    context->m_InstructionSet[TLVM_MOV_MA]   = tlvmMOV;
    
    context->m_InstructionSet[TLVM_MOV_AB]   = tlvmMOV;
    context->m_InstructionSet[TLVM_MOV_AC]   = tlvmMOV;
    context->m_InstructionSet[TLVM_MOV_AD]   = tlvmMOV;
    context->m_InstructionSet[TLVM_MOV_AE]   = tlvmMOV;
    context->m_InstructionSet[TLVM_MOV_AH]   = tlvmMOV;
    context->m_InstructionSet[TLVM_MOV_AL]   = tlvmMOV;
    context->m_InstructionSet[TLVM_MOV_AM]   = tlvmMOV;
    context->m_InstructionSet[TLVM_MOV_AA]   = tlvmMOV;
    
    context->m_InstructionSet[TLVM_ANA_B]    = tlvmANA;
    context->m_InstructionSet[TLVM_ANA_C]    = tlvmANA;
    context->m_InstructionSet[TLVM_ANA_D]    = tlvmANA;
    context->m_InstructionSet[TLVM_ANA_E]    = tlvmANA;
    context->m_InstructionSet[TLVM_ANA_H]    = tlvmANA;
    context->m_InstructionSet[TLVM_ANA_L]    = tlvmANA;
    context->m_InstructionSet[TLVM_ANA_M]    = tlvmANA;
    context->m_InstructionSet[TLVM_ANA_A]    = tlvmANA;
    
    context->m_InstructionSet[TLVM_ANI]      = tlvmANI;
    
    context->m_InstructionSet[TLVM_ORA_B]    = tlvmORA;
    context->m_InstructionSet[TLVM_ORA_C]    = tlvmORA;
    context->m_InstructionSet[TLVM_ORA_D]    = tlvmORA;
    context->m_InstructionSet[TLVM_ORA_E]    = tlvmORA;
    context->m_InstructionSet[TLVM_ORA_H]    = tlvmORA;
    context->m_InstructionSet[TLVM_ORA_L]    = tlvmORA;
    context->m_InstructionSet[TLVM_ORA_M]    = tlvmORA;
    context->m_InstructionSet[TLVM_ORA_A]    = tlvmORA;
    
    context->m_InstructionSet[TLVM_ORI]      = tlvmORI;
    
    context->m_InstructionSet[TLVM_XRA_B]    = tlvmXRA;
    context->m_InstructionSet[TLVM_XRA_C]    = tlvmXRA;
    context->m_InstructionSet[TLVM_XRA_D]    = tlvmXRA;
    context->m_InstructionSet[TLVM_XRA_E]    = tlvmXRA;
    context->m_InstructionSet[TLVM_XRA_H]    = tlvmXRA;
    context->m_InstructionSet[TLVM_XRA_L]    = tlvmXRA;
    context->m_InstructionSet[TLVM_XRA_M]    = tlvmXRA;
    context->m_InstructionSet[TLVM_XRA_A]    = tlvmXRA;
   
    context->m_InstructionSet[TLVM_XRI]      = tlvmXRI;

    context->m_InstructionSet[TLVM_PUSH_B]   = tlvmPUSH;
    context->m_InstructionSet[TLVM_PUSH_D]   = tlvmPUSH;
    context->m_InstructionSet[TLVM_PUSH_H]   = tlvmPUSH;
    context->m_InstructionSet[TLVM_PUSH_PSW] = tlvmPUSH;

    context->m_InstructionSet[TLVM_POP_B]    = tlvmPOP;
    context->m_InstructionSet[TLVM_POP_D]    = tlvmPOP;
    context->m_InstructionSet[TLVM_POP_H]    = tlvmPOP;
    context->m_InstructionSet[TLVM_POP_PSW]  = tlvmPOP;

    context->m_InstructionSet[TLVM_SPHL]     = tlvmSPHL;
    context->m_InstructionSet[TLVM_XTHL]     = tlvmXTHL;

    context->m_InstructionSet[TLVM_JNZ]      = tlvmJMP;
    context->m_InstructionSet[TLVM_JZ]       = tlvmJMP;
    context->m_InstructionSet[TLVM_JNC]      = tlvmJMP;
    context->m_InstructionSet[TLVM_JC]       = tlvmJMP;
    context->m_InstructionSet[TLVM_JPO]      = tlvmJMP;
    context->m_InstructionSet[TLVM_JPE]      = tlvmJMP;
    context->m_InstructionSet[TLVM_JP]       = tlvmJMP;
    context->m_InstructionSet[TLVM_JM]       = tlvmJMP;
    context->m_InstructionSet[TLVM_JMP]      = tlvmJMP;

    context->m_InstructionSet[TLVM_CNZ]      = tlvmCALL;
    context->m_InstructionSet[TLVM_CZ]       = tlvmCALL;
    context->m_InstructionSet[TLVM_CNC]      = tlvmCALL;
    context->m_InstructionSet[TLVM_CC]       = tlvmCALL;
    context->m_InstructionSet[TLVM_CPO]      = tlvmCALL;
    context->m_InstructionSet[TLVM_CPE]      = tlvmCALL;
    context->m_InstructionSet[TLVM_CP]       = tlvmCALL;
    context->m_InstructionSet[TLVM_CM]       = tlvmCALL;
    context->m_InstructionSet[TLVM_CALL]     = tlvmCALL;

    context->m_InstructionSet[TLVM_RNZ]      = tlvmRET;
    context->m_InstructionSet[TLVM_RZ]       = tlvmRET;
    context->m_InstructionSet[TLVM_RNC]      = tlvmRET;
    context->m_InstructionSet[TLVM_RC]       = tlvmRET;
    context->m_InstructionSet[TLVM_RPO]      = tlvmRET;
    context->m_InstructionSet[TLVM_RPE]      = tlvmRET;
    context->m_InstructionSet[TLVM_RP]       = tlvmRET;
    context->m_InstructionSet[TLVM_RM]       = tlvmRET;
    context->m_InstructionSet[TLVM_RET]      = tlvmRET;
    context->m_InstructionSet[TLVM_ADD_B] = tlvmADD;
    context->m_InstructionSet[TLVM_ADD_C] = tlvmADD;
    context->m_InstructionSet[TLVM_ADD_D] = tlvmADD;
    context->m_InstructionSet[TLVM_ADD_E] = tlvmADD;
    context->m_InstructionSet[TLVM_ADD_H] = tlvmADD;
    context->m_InstructionSet[TLVM_ADD_L] = tlvmADD;
    context->m_InstructionSet[TLVM_ADD_M] = tlvmADD;
    context->m_InstructionSet[TLVM_ADD_A] = tlvmADD;

    context->m_InstructionSet[TLVM_SUB_B] = tlvmSUB;
    context->m_InstructionSet[TLVM_SUB_C] = tlvmSUB;
    context->m_InstructionSet[TLVM_SUB_D] = tlvmSUB;
    context->m_InstructionSet[TLVM_SUB_E] = tlvmSUB;
    context->m_InstructionSet[TLVM_SUB_H] = tlvmSUB;
    context->m_InstructionSet[TLVM_SUB_L] = tlvmSUB;
    context->m_InstructionSet[TLVM_SUB_M] = tlvmSUB;
    context->m_InstructionSet[TLVM_SUB_A] = tlvmSUB;

    context->m_InstructionSet[TLVM_INR_B] = tlvmINR;
    context->m_InstructionSet[TLVM_INR_C] = tlvmINR;
    context->m_InstructionSet[TLVM_INR_D] = tlvmINR;
    context->m_InstructionSet[TLVM_INR_E] = tlvmINR;
    context->m_InstructionSet[TLVM_INR_H] = tlvmINR;
    context->m_InstructionSet[TLVM_INR_L] = tlvmINR;
    context->m_InstructionSet[TLVM_INR_M] = tlvmINR;
    context->m_InstructionSet[TLVM_INR_A] = tlvmINR;

    context->m_InstructionSet[TLVM_INX_B] = tlvmINX;
    context->m_InstructionSet[TLVM_INX_D] = tlvmINX;
    context->m_InstructionSet[TLVM_INX_H] = tlvmINX;
    context->m_InstructionSet[TLVM_INX_SP]= tlvmINX;

    context->m_InstructionSet[TLVM_DCR_B] = tlvmDCR;
    context->m_InstructionSet[TLVM_DCR_C] = tlvmDCR;
    context->m_InstructionSet[TLVM_DCR_D] = tlvmDCR;
    context->m_InstructionSet[TLVM_DCR_E] = tlvmDCR;
    context->m_InstructionSet[TLVM_DCR_H] = tlvmDCR;
    context->m_InstructionSet[TLVM_DCR_L] = tlvmDCR;
    context->m_InstructionSet[TLVM_DCR_M] = tlvmDCR;
    context->m_InstructionSet[TLVM_DCR_A] = tlvmDCR;

    context->m_InstructionSet[TLVM_DCX_B] = tlvmDCX;
    context->m_InstructionSet[TLVM_DCX_D] = tlvmDCX;
    context->m_InstructionSet[TLVM_DCX_H] = tlvmDCX;
    context->m_InstructionSet[TLVM_DCX_SP]= tlvmDCX;

    context->m_InstructionSet[TLVM_ADI] = tlvmADI;
    context->m_InstructionSet[TLVM_SUI] = tlvmSUI;


    
    tlvmReturnCode(SUCCESS);
}

tlvmReturn tlvmNOP(tlvmContext* context, tlvmByte* cycles)
{
    if(context == NULL)
        tlvmReturnCode(NO_CONTEXT);
    
    context->m_ProgramCounter += 1;
    if(cycles)
    	*cycles =1;
    
    tlvmReturnCode(SUCCESS);
}

tlvmReturn tlvmHLT(tlvmContext* context, tlvmByte* cycles)
{
    if(context == NULL)
        tlvmReturnCode(NO_CONTEXT);
    
    context->m_ProgramCounter += 1;
    if(cycles)
    	*cycles =1;
    
    tlvmReturnCode(EXIT);
}

tlvmReturn tlvmLXI(tlvmContext* context, tlvmByte* cycles)
{
    if(context == NULL)
        tlvmReturnCode(NO_CONTEXT);
    
	TLVM_GET_OP(opcode, 0);
	TLVM_GET_OP(opLow,  1);
	TLVM_GET_OP(opHigh, 2);

    switch(opcode)
    {
    case TLVM_LXI_B:
        context->m_Registers[TLVM_REG_B] = opHigh;
        context->m_Registers[TLVM_REG_C] = opLow;
	break;
    case TLVM_LXI_D:
        context->m_Registers[TLVM_REG_D] = opHigh;
        context->m_Registers[TLVM_REG_E] = opLow;
	break;
    case TLVM_LXI_H:
        context->m_Registers[TLVM_REG_H] = opHigh;
        context->m_Registers[TLVM_REG_L] = opLow;
	break;
    case TLVM_LXI_SP:
        context->m_StackPointer = (tlvmShort)opHigh << 8 | (tlvmShort)opLow;
	break;
    }
    
    // size of instruction    = 1
    // size of operand        = 2
    context->m_ProgramCounter += 3;
    if(cycles)
    	*cycles =3;
    
    tlvmReturnCode(SUCCESS);
}

tlvmReturn tlvmSTAX(tlvmContext* context, tlvmByte* cycles)
{
    if(context == NULL)
        tlvmReturnCode(NO_CONTEXT);
    
	TLVM_GET_OP(opcode, 0);

    tlvmShort addr = 0;
    switch(opcode)
    {
    case TLVM_STAX_B:
    	addr = TLVM_GET_16BIT(TLVM_REG_B, TLVM_REG_C);
	break;
    case TLVM_STAX_D:
    	addr = TLVM_GET_16BIT(TLVM_REG_D, TLVM_REG_E);
	break;
    }
    tlvmByte* dst = tlvmGetMemory(context, addr, TLVM_FLAG_WRITE);
    if(dst == NULL)
    	tlvmReturnCode(INVALID_INPUT);
    *dst = context->m_Registers[TLVM_REG_A];
    
    // size of instruction    = 1
    context->m_ProgramCounter += 1;
    if(cycles)
    	*cycles =1;
    
    tlvmReturnCode(SUCCESS);
}

tlvmReturn tlvmMVI(tlvmContext* context, tlvmByte* cycles)
{
	if(context == NULL)
		tlvmReturnCode(NO_CONTEXT);

	TLVM_GET_OP(opcode,  0);
	TLVM_GET_OP(operand, 1);

	switch(opcode)
	{
	case TLVM_MVI_B:
		context->m_Registers[TLVM_REG_B] = operand;
	break;
	case TLVM_MVI_C:
		context->m_Registers[TLVM_REG_C] = operand;
	break;
	case TLVM_MVI_D:
		context->m_Registers[TLVM_REG_D] = operand;
	break;
	case TLVM_MVI_E:
		context->m_Registers[TLVM_REG_E] = operand;
	break;
	case TLVM_MVI_H:
		context->m_Registers[TLVM_REG_H] = operand;
	break;
	case TLVM_MVI_L:
		context->m_Registers[TLVM_REG_L] = operand;
	break;
	case TLVM_MVI_M:
		{
			tlvmShort addr = TLVM_GET_16BIT(TLVM_REG_H, TLVM_REG_L);
			tlvmByte* dst = tlvmGetMemory(context, addr, TLVM_FLAG_WRITE);
			if(dst == NULL)
				tlvmReturnCode(INVALID_INPUT);
			*dst = operand;
		}
	break;
	case TLVM_MVI_A:
		context->m_Registers[TLVM_REG_A] = operand;
	break;
	default:
		tlvmReturnCode(INVALID_INPUT)
	}

	// size of instruction    = 1
	// size of operand        = 1
	context->m_ProgramCounter += 2;
    if(cycles)
    	*cycles =2;

	tlvmReturnCode(SUCCESS);
}

tlvmReturn tlvmSHLD(tlvmContext* context, tlvmByte* cycles)
{
	if(context == NULL)
		tlvmReturnCode(NO_CONTEXT);


	TLVM_GET_OP(opLow, 1);
	TLVM_GET_OP(opHigh, 2);

    tlvmShort addr = (tlvmShort)opHigh << 8 | (tlvmShort)opLow;
    tlvmByte* dstLo = tlvmGetMemory(context, addr+0, TLVM_FLAG_WRITE);
    tlvmByte* dstHi = tlvmGetMemory(context, addr+0, TLVM_FLAG_WRITE);
    if(dstLo == NULL || dstHi == NULL)
    	tlvmReturnCode(INVALID_INPUT);
    *dstLo = context->m_Registers[TLVM_REG_L];
    *dstHi = context->m_Registers[TLVM_REG_H];

	// size of instruction    = 1
	// size of operand        = 2
	context->m_ProgramCounter += 3;
    if(cycles)
    	*cycles =3;

	tlvmReturnCode(SUCCESS);
}

tlvmReturn tlvmLDA(tlvmContext* context, tlvmByte* cycles)
{
	if(context == NULL)
		tlvmReturnCode(NO_CONTEXT);

	TLVM_GET_OP(opLow, 1);
	TLVM_GET_OP(opHigh, 2);

    tlvmShort addr = (tlvmShort)opHigh << 8 | (tlvmShort)opLow;

    tlvmByte* src = tlvmGetMemory(context, addr, TLVM_FLAG_READ);
    if(src == NULL)
    	tlvmReturnCode(INVALID_INPUT);
    context->m_Registers[TLVM_REG_A] = *src;

	// size of instruction    = 1
	// size of operand        = 1
	context->m_ProgramCounter += 2;
    if(cycles)
    	*cycles =3;

	tlvmReturnCode(SUCCESS);
}

tlvmReturn tlvmLDAX(tlvmContext* context, tlvmByte* cycles)
{
	if(context == NULL)
		tlvmReturnCode(NO_CONTEXT);

	TLVM_GET_OP(opcode, 0);
	tlvmShort addr = 0;
	switch(opcode)
	{
	case TLVM_LDAX_B:
		addr = TLVM_GET_16BIT(TLVM_REG_B, TLVM_REG_C);
	break;
	case TLVM_LDAX_D:
		addr = TLVM_GET_16BIT(TLVM_REG_D, TLVM_REG_E);
	break;
	default:
		tlvmReturnCode(INVALID_INPUT);
	}

	tlvmByte* src = tlvmGetMemory(context, addr, TLVM_FLAG_READ);
	if(src == NULL)
		tlvmReturnCode(INVALID_INPUT);

	if(*src == 0)
		TLVM_FLAG_SET(Z);
	else
		TLVM_FLAG_UNSET(Z);
	context->m_Registers[TLVM_REG_A] = *src;

	// size of instruction    = 1
	context->m_ProgramCounter += 1;
    if(cycles)
    	*cycles =1;

	tlvmReturnCode(SUCCESS);
}

#define TEST_MOV(x) ((opcode & x) == x)
tlvmReturn tlvmMOV(tlvmContext* context, tlvmByte* cycles)
{
	if(context == NULL)
		tlvmReturnCode(NO_CONTEXT);

	TLVM_GET_OP(opcode, 0);

	tlvmByte* dst = NULL;
	tlvmByte* src = NULL;

	if( (TEST_MOV(TLVM_MOV_TO_A)) && (opcode & TLVM_MOV_HI) )
		dst = &context->m_Registers[TLVM_REG_A];
	else if( (TEST_MOV(TLVM_MOV_TO_M)) && !(opcode & TLVM_MOV_HI) )
		dst = tlvmGetMemory(context, TLVM_GET_16BIT(TLVM_REG_H, TLVM_REG_L), TLVM_FLAG_WRITE);
	else if( (TEST_MOV(TLVM_MOV_TO_L)) && (opcode & TLVM_MOV_HI) )
		dst = &context->m_Registers[TLVM_REG_L];
	else if( (TEST_MOV(TLVM_MOV_TO_H)) && !(opcode & TLVM_MOV_HI) )
		dst = &context->m_Registers[TLVM_REG_H];
	else if( (TEST_MOV(TLVM_MOV_TO_E)) && (opcode & TLVM_MOV_HI) )
		dst = &context->m_Registers[TLVM_REG_E];
	else if( (TEST_MOV(TLVM_MOV_TO_D)) && !(opcode & TLVM_MOV_HI) )
		dst = &context->m_Registers[TLVM_REG_D];
	else if( (TEST_MOV(TLVM_MOV_TO_C)) && (opcode & TLVM_MOV_HI) )
		dst = &context->m_Registers[TLVM_REG_C];
	else if( (TEST_MOV(TLVM_MOV_TO_B)) && !(opcode & TLVM_MOV_HI) )
		dst = &context->m_Registers[TLVM_REG_B];

	if( (TEST_MOV(TLVM_MOV_FROM_A)) )
		src = &context->m_Registers[TLVM_REG_A];
	else if( (TEST_MOV(TLVM_MOV_FROM_M)) )
		src = tlvmGetMemory(context, TLVM_GET_16BIT(TLVM_REG_H, TLVM_REG_L), TLVM_FLAG_READ);
	else if( (TEST_MOV(TLVM_MOV_FROM_L)) )
		src = &context->m_Registers[TLVM_REG_L];
	else if( (TEST_MOV(TLVM_MOV_FROM_H)) )
		src = &context->m_Registers[TLVM_REG_H];
	else if( (TEST_MOV(TLVM_MOV_FROM_E)) )
		src = &context->m_Registers[TLVM_REG_E];
	else if( (TEST_MOV(TLVM_MOV_FROM_D)) )
		src = &context->m_Registers[TLVM_REG_D];
	else if( (TEST_MOV(TLVM_MOV_FROM_C)) )
		src = &context->m_Registers[TLVM_REG_C];
	else if( (TEST_MOV(TLVM_MOV_FROM_B)) )
		src = &context->m_Registers[TLVM_REG_B];


	if(src == NULL || dst == NULL)
		tlvmReturnCode(INVALID_INPUT);

	*dst = *src;

	// size of instruction    = 1
	context->m_ProgramCounter += 1;
    if(cycles)
    	*cycles =1;

	tlvmReturnCode(SUCCESS);
}

tlvmReturn tlvmANA(tlvmContext* context, tlvmByte* cycles)
{
	if(context == NULL)
		tlvmReturnCode(NO_CONTEXT);

	TLVM_GET_OP(opcode, 0);

	tlvmByte* src = NULL;

	switch(opcode)
	{
	case TLVM_ANA_B:
		src = &context->m_Registers[TLVM_REG_B];
	break;
	case TLVM_ANA_C:
		src = &context->m_Registers[TLVM_REG_C];
	break;
	case TLVM_ANA_D:
		src = &context->m_Registers[TLVM_REG_D];
	break;
	case TLVM_ANA_E:
		src = &context->m_Registers[TLVM_REG_E];
	break;
	case TLVM_ANA_H:
		src = &context->m_Registers[TLVM_REG_H];
	break;
	case TLVM_ANA_L:
		src = &context->m_Registers[TLVM_REG_L];
	break;
	case TLVM_ANA_M:
		{
			tlvmShort addr = TLVM_GET_16BIT(TLVM_REG_H, TLVM_REG_L);
			src = tlvmGetMemory(context, addr, TLVM_FLAG_READ);
		}
	break;
	case TLVM_ANA_A:
		src = &context->m_Registers[TLVM_REG_A];
	break;
	}

	if(src == NULL)
		tlvmReturnCode(INVALID_INPUT);

	context->m_Registers[TLVM_REG_A] &= *src;

	// size of instruction    = 1
	context->m_ProgramCounter += 1;
    if(cycles)
    	*cycles =1;

	tlvmReturnCode(SUCCESS);
}

tlvmReturn tlvmANI(tlvmContext* context, tlvmByte* cycles)
{
	if(context == NULL)
		tlvmReturnCode(NO_CONTEXT);

	TLVM_GET_OP(operand, 1);

	context->m_Registers[TLVM_REG_A] &= operand;

	// size of instruction    = 1
	// size of operand        = 1
	context->m_ProgramCounter += 2;
    if(cycles)
    	*cycles =2;

	tlvmReturnCode(SUCCESS);
}

tlvmReturn tlvmORA(tlvmContext* context, tlvmByte* cycles)
{
	if(context == NULL)
		tlvmReturnCode(NO_CONTEXT);

	TLVM_GET_OP(opcode, 0);

	tlvmByte* src = NULL;

	switch(opcode)
	{
	case TLVM_ORA_B:
		src = &context->m_Registers[TLVM_REG_B];
	break;
	case TLVM_ORA_C:
		src = &context->m_Registers[TLVM_REG_C];
	break;
	case TLVM_ORA_D:
		src = &context->m_Registers[TLVM_REG_D];
	break;
	case TLVM_ORA_E:
		src = &context->m_Registers[TLVM_REG_E];
	break;
	case TLVM_ORA_H:
		src = &context->m_Registers[TLVM_REG_H];
	break;
	case TLVM_ORA_L:
		src = &context->m_Registers[TLVM_REG_L];
	break;
	case TLVM_ORA_M:
		{
			tlvmShort addr = TLVM_GET_16BIT(TLVM_REG_H, TLVM_REG_L);
			src = tlvmGetMemory(context, addr, TLVM_FLAG_READ);
		}
	break;
	case TLVM_ORA_A:
		src = &context->m_Registers[TLVM_REG_A];
	break;
	}

	if(src == NULL)
		tlvmReturnCode(INVALID_INPUT);

	context->m_Registers[TLVM_REG_A] |= *src;

	// size of instruction    = 1
	context->m_ProgramCounter += 1;
    if(cycles)
    	*cycles =1;

	tlvmReturnCode(SUCCESS);
}

tlvmReturn tlvmORI(tlvmContext* context, tlvmByte* cycles)
{
	if(context == NULL)
		tlvmReturnCode(NO_CONTEXT);

	TLVM_GET_OP(operand, 0);

	context->m_Registers[TLVM_REG_A] |= operand;

	// size of instruction    = 1
	// size of operand        = 1
	context->m_ProgramCounter += 2;
    if(cycles)
    	*cycles =2;

	tlvmReturnCode(SUCCESS);
}

tlvmReturn tlvmXRA(tlvmContext* context, tlvmByte* cycles)
{
	if(context == NULL)
		tlvmReturnCode(NO_CONTEXT);

	TLVM_GET_OP(opcode, 0);

	tlvmByte* src = NULL;

	switch(opcode)
	{
	case TLVM_XRA_B:
		src = &context->m_Registers[TLVM_REG_B];
	break;
	case TLVM_XRA_C:
		src = &context->m_Registers[TLVM_REG_C];
	break;
	case TLVM_XRA_D:
		src = &context->m_Registers[TLVM_REG_D];
	break;
	case TLVM_XRA_E:
		src = &context->m_Registers[TLVM_REG_E];
	break;
	case TLVM_XRA_H:
		src = &context->m_Registers[TLVM_REG_H];
	break;
	case TLVM_XRA_L:
		src = &context->m_Registers[TLVM_REG_L];
	break;
	case TLVM_XRA_M:
		{
			tlvmShort addr = TLVM_GET_16BIT(TLVM_REG_H, TLVM_REG_L);
			src = tlvmGetMemory(context, addr, TLVM_FLAG_READ);
		}
	break;
	case TLVM_XRA_A:
		src = &context->m_Registers[TLVM_REG_A];
	break;
	}

	if(src == NULL)
		tlvmReturnCode(INVALID_INPUT);

	context->m_Registers[TLVM_REG_A] ^= *src;

	// size of instruction    = 1
	context->m_ProgramCounter += 1;
    if(cycles)
    	*cycles =1;

	tlvmReturnCode(SUCCESS);
}

tlvmReturn tlvmXRI(tlvmContext* context, tlvmByte* cycles)
{
	if(context == NULL)
		tlvmReturnCode(NO_CONTEXT);

	TLVM_GET_OP(operand, 1);

	context->m_Registers[TLVM_REG_A] ^= operand;

	// size of instruction    = 1
	// size of operand        = 1
	context->m_ProgramCounter += 2;
    if(cycles)
    	*cycles =2;

	tlvmReturnCode(SUCCESS);
}

tlvmReturn tlvmPUSH(tlvmContext* context, tlvmByte* cycles)
{
	if(context == NULL)
		tlvmReturnCode(NO_CONTEXT);

	TLVM_GET_OP(opcode, 0);

	tlvmByte srcHi = 0;
	tlvmByte srcLo = 0;
	switch(opcode)
	{
	case TLVM_PUSH_B:
    	srcHi = context->m_Registers[TLVM_REG_B];
    	srcLo = context->m_Registers[TLVM_REG_C];
	break;
	case TLVM_PUSH_D:
    	srcHi = context->m_Registers[TLVM_REG_D];
    	srcLo = context->m_Registers[TLVM_REG_E];
	break;
	case TLVM_PUSH_H:
    	srcHi = context->m_Registers[TLVM_REG_H];
    	srcLo = context->m_Registers[TLVM_REG_L];
	break;
	case TLVM_PUSH_PSW:
    	srcHi = context->m_Registers[TLVM_REG_A];
    	srcLo = context->m_Registers[TLVM_REG_F];
	break;
	}

	// rather than just getting one address, get each location manually
	// as in theory it might go across memory boundaries
	tlvmByte* dstHi = tlvmGetMemory(context, context->m_StackPointer - 1, TLVM_FLAG_WRITE);
	tlvmByte* dstLo = tlvmGetMemory(context, context->m_StackPointer - 2, TLVM_FLAG_WRITE);
	if(dstHi == NULL || dstLo == NULL)
		tlvmReturnCode(INVALID_INPUT);

	*dstHi = srcHi;
	*dstLo = srcLo;

	context->m_StackPointer -= 2;

	// size of instruction    = 1
	context->m_ProgramCounter += 1;
    if(cycles)
    	*cycles = 11;

	tlvmReturnCode(SUCCESS);
}

tlvmReturn tlvmPOP(tlvmContext* context, tlvmByte* cycles)
{
	if(context == NULL)
		tlvmReturnCode(NO_CONTEXT);

	TLVM_GET_OP(opcode, 0);

	tlvmByte* dstHi = NULL;
	tlvmByte* dstLo = NULL;
	switch(opcode)
	{
	case TLVM_POP_B:
    	dstHi = &context->m_Registers[TLVM_REG_B];
    	dstLo = &context->m_Registers[TLVM_REG_C];
	break;
	case TLVM_POP_D:
    	dstHi = &context->m_Registers[TLVM_REG_D];
    	dstLo = &context->m_Registers[TLVM_REG_E];
	break;
	case TLVM_POP_H:
    	dstHi = &context->m_Registers[TLVM_REG_H];
    	dstLo = &context->m_Registers[TLVM_REG_L];
	break;
	case TLVM_POP_PSW:
    	dstHi = &context->m_Registers[TLVM_REG_A];
    	dstLo = &context->m_Registers[TLVM_REG_F];
	break;
	}

	// rather than just getting one address, get each location manually
	// as in theory it might go across memory boundaries
	tlvmByte* srcHi = tlvmGetMemory(context, context->m_StackPointer + 1, TLVM_FLAG_READ);
	tlvmByte* srcLo = tlvmGetMemory(context, context->m_StackPointer + 0, TLVM_FLAG_READ);
	if(srcHi == NULL || srcLo == NULL || dstHi == NULL || dstLo == NULL)
		tlvmReturnCode(INVALID_INPUT);

	*dstHi = *srcHi;
	*dstLo = *srcLo;

	context->m_StackPointer += 2;

	// size of instruction    = 1
	context->m_ProgramCounter += 1;
    if(cycles)
    	*cycles = 10;

	tlvmReturnCode(SUCCESS);
}

tlvmReturn tlvmSPHL(tlvmContext* context, tlvmByte* cycles)
{
	if(context == NULL)
		tlvmReturnCode(NO_CONTEXT);

	context->m_StackPointer = TLVM_GET_16BIT(TLVM_REG_H, TLVM_REG_L);
	// size of instruction    = 1
	context->m_ProgramCounter += 1;
    if(cycles)
    	*cycles =5;

	tlvmReturnCode(SUCCESS);
}

tlvmReturn tlvmXTHL(tlvmContext* context, tlvmByte* cycles)
{
	if(context == NULL)
		tlvmReturnCode(NO_CONTEXT);

	tlvmByte* dstHi = tlvmGetMemory(context, context->m_StackPointer+1, TLVM_FLAG_WRITE);
	tlvmByte* dstLo = tlvmGetMemory(context, context->m_StackPointer+0, TLVM_FLAG_WRITE);

	if(dstHi == NULL || dstLo == NULL)
		tlvmReturnCode(INVALID_INPUT);

	tlvmByte tmpHi = *dstHi;
	tlvmByte tmpLo = *dstLo;

	*dstHi = context->m_Registers[TLVM_REG_H];
	*dstLo = context->m_Registers[TLVM_REG_L];

	context->m_Registers[TLVM_REG_H] = tmpHi;
	context->m_Registers[TLVM_REG_L] = tmpLo;

	// size of instruction    = 1
	context->m_ProgramCounter += 1;
    if(cycles)
    	*cycles =18;

	tlvmReturnCode(SUCCESS);
}

tlvmReturn tlvmJMP(tlvmContext* context, tlvmByte* cycles)
{
	if(context == NULL)
		tlvmReturnCode(NO_CONTEXT);

	TLVM_GET_OP(opcode, 0);
	TLVM_GET_OP(opLow,  1);
	TLVM_GET_OP(opHigh, 2);
	tlvmShort addr = (tlvmShort)opHigh << 8 | (tlvmShort)opLow;

	// increment PC before logic as it is fallback
	// size of instruction    = 1
	// size of address        = 2
	context->m_ProgramCounter += 3;

	switch(opcode)
	{
	case TLVM_JNZ:
		if(!TLVM_FLAG_ISSET(Z))
			context->m_ProgramCounter = addr;
	break;
	case TLVM_JZ:
		if(TLVM_FLAG_ISSET(Z))
			context->m_ProgramCounter = addr;
	break;
	case TLVM_JNC:
		if(!TLVM_FLAG_ISSET(C))
			context->m_ProgramCounter = addr;
	break;
	case TLVM_JC:
		if(TLVM_FLAG_ISSET(C))
			context->m_ProgramCounter = addr;
	break;
	case TLVM_JPO:
		if(!TLVM_FLAG_ISSET(P))
			context->m_ProgramCounter = addr;
	break;
	case TLVM_JPE:
		if(TLVM_FLAG_ISSET(P))
			context->m_ProgramCounter = addr;
	break;
	case TLVM_JP:
		if(!TLVM_FLAG_ISSET(S))
			context->m_ProgramCounter = addr;
	break;
	case TLVM_JM:
		if(TLVM_FLAG_ISSET(S))
			context->m_ProgramCounter = addr;
	break;
	case TLVM_JMP:
		context->m_ProgramCounter = addr;
	break;
	}

    if(cycles)
    	*cycles =10;

	tlvmReturnCode(SUCCESS);
}

tlvmReturn tlvmCALL(tlvmContext* context, tlvmByte* cycles)
{
	if(context == NULL)
		tlvmReturnCode(NO_CONTEXT);

	TLVM_GET_OP(opcode, 0);
	TLVM_GET_OP(opLow,  1);
	TLVM_GET_OP(opHigh, 2);
	tlvmShort addr = (tlvmShort)opHigh << 8 | (tlvmShort)opLow;

	// increment PC before logic as it is fallback
	// size of instruction    = 1
	// size of address        = 2
	context->m_ProgramCounter += 3;

	// rather than just getting one address, get each location manually
	// as in theory it might go across memory boundaries
	tlvmByte* dstHi = tlvmGetMemory(context, context->m_StackPointer - 1, TLVM_FLAG_WRITE);
	tlvmByte* dstLo = tlvmGetMemory(context, context->m_StackPointer - 2, TLVM_FLAG_WRITE);
	if(dstHi == NULL || dstLo == NULL)
		tlvmReturnCode(INVALID_INPUT);
	tlvmByte srcHi = (tlvmByte)(context->m_ProgramCounter >> 8);
	tlvmByte srcLo = (tlvmByte)(context->m_ProgramCounter & 0xFF);

	tlvmByte cycleCnt = 11;
	switch(opcode)
	{
	case TLVM_CNZ:
		if(!TLVM_FLAG_ISSET(Z))
		{
			*dstHi = srcHi; *dstLo = srcLo;
			context->m_ProgramCounter = addr;
			cycleCnt = 17;
		}
	break;
	case TLVM_CZ:
		if(TLVM_FLAG_ISSET(Z))
		{
			*dstHi = srcHi; *dstLo = srcLo;
			context->m_ProgramCounter = addr;
			cycleCnt = 17;
		}
	break;
	case TLVM_CNC:
		if(!TLVM_FLAG_ISSET(C))
		{
			*dstHi = srcHi; *dstLo = srcLo;
			context->m_ProgramCounter = addr;
			cycleCnt = 17;
		}
	break;
	case TLVM_CC:
		if(TLVM_FLAG_ISSET(C))
		{
			*dstHi = srcHi; *dstLo = srcLo;
			context->m_ProgramCounter = addr;
			cycleCnt = 17;
		}
	break;
	case TLVM_CPO:
		if(!TLVM_FLAG_ISSET(P))
		{
			*dstHi = srcHi; *dstLo = srcLo;
			context->m_ProgramCounter = addr;
			cycleCnt = 17;
		}
	break;
	case TLVM_CPE:
		if(TLVM_FLAG_ISSET(P))
		{
			*dstHi = srcHi; *dstLo = srcLo;
			context->m_ProgramCounter = addr;
			cycleCnt = 17;
		}
	break;
	case TLVM_CP:
		if(!TLVM_FLAG_ISSET(S))
		{
			*dstHi = srcHi; *dstLo = srcLo;
			context->m_ProgramCounter = addr;
			cycleCnt = 17;
		}
	break;
	case TLVM_CM:
		if(TLVM_FLAG_ISSET(S))
		{
			*dstHi = srcHi; *dstLo = srcLo;
			context->m_ProgramCounter = addr;
			cycleCnt = 17;
		}
	break;
	case TLVM_CALL:
	{
		*dstHi = srcHi; *dstLo = srcLo;
		context->m_ProgramCounter = addr;
		cycleCnt = 17;
	}
	break;
	}

    context->m_StackPointer -= 2;

    if(cycles)
    	*cycles = cycleCnt;

	tlvmReturnCode(SUCCESS);
}

tlvmReturn tlvmRET(tlvmContext* context, tlvmByte* cycles)
{
	if(context == NULL)
		tlvmReturnCode(NO_CONTEXT);

	TLVM_GET_OP(opcode, 0);

	// increment PC before logic as it is fallback
	// size of instruction    = 1
	context->m_ProgramCounter += 1;

	// rather than just getting one address, get each location manually
	// as in theory it might go across memory boundaries
	tlvmByte* srcHi = tlvmGetMemory(context, context->m_StackPointer + 1, TLVM_FLAG_WRITE);
	tlvmByte* srcLo = tlvmGetMemory(context, context->m_StackPointer + 0, TLVM_FLAG_WRITE);
	if(srcHi == NULL || srcLo == NULL)
		tlvmReturnCode(INVALID_INPUT);
	tlvmShort addr = (tlvmShort)((*srcHi) << 8) | ((tlvmShort)(*srcLo));

	tlvmByte cycleCnt = 5;
	switch(opcode)
	{
	case TLVM_CNZ:
		if(!TLVM_FLAG_ISSET(Z))
		{
			context->m_ProgramCounter = addr;
			cycleCnt = 11;
		}
	break;
	case TLVM_CZ:
		if(TLVM_FLAG_ISSET(Z))
		{
			context->m_ProgramCounter = addr;
			cycleCnt = 11;
		}
	break;
	case TLVM_CNC:
		if(!TLVM_FLAG_ISSET(C))
		{
			context->m_ProgramCounter = addr;
			cycleCnt = 11;
		}
	break;
	case TLVM_CC:
		if(TLVM_FLAG_ISSET(C))
		{
			context->m_ProgramCounter = addr;
			cycleCnt = 11;
		}
	break;
	case TLVM_CPO:
		if(!TLVM_FLAG_ISSET(P))
		{
			context->m_ProgramCounter = addr;
			cycleCnt = 11;
		}
	break;
	case TLVM_CPE:
		if(TLVM_FLAG_ISSET(P))
		{
			context->m_ProgramCounter = addr;
			cycleCnt = 11;
		}
	break;
	case TLVM_CP:
		if(!TLVM_FLAG_ISSET(S))
		{
			context->m_ProgramCounter = addr;
			cycleCnt = 11;
		}
	break;
	case TLVM_CM:
		if(TLVM_FLAG_ISSET(S))
		{
			context->m_ProgramCounter = addr;
			cycleCnt = 11;
		}
	break;
	case TLVM_CALL:
	{
		context->m_ProgramCounter = addr;
		cycleCnt = 10;
	}
	break;
	}

    context->m_StackPointer += 2;

    if(cycles)
    	*cycles = cycleCnt;

	tlvmReturnCode(SUCCESS);
}

tlvmReturn tlvmADD(tlvmContext* context, tlvmByte* cycles)
{
    if(context == NULL)
        tlvmReturnCode(NO_CONTEXT);

    TLVM_GET_OP(opcode, 0);

    tlvmByte* src = NULL;

    switch(opcode)
    {
    case TLVM_ADD_B:
        src = &context->m_Registers[TLVM_REG_B];
    break;
    case TLVM_ADD_C:
        src = &context->m_Registers[TLVM_REG_C];
    break;
    case TLVM_ADD_D:
        src = &context->m_Registers[TLVM_REG_D];
    break;
    case TLVM_ADD_E:
        src = &context->m_Registers[TLVM_REG_E];
    break;
    case TLVM_ADD_H:
        src = &context->m_Registers[TLVM_REG_H];
    break;
    case TLVM_ADD_L:
        src = &context->m_Registers[TLVM_REG_L];
    break;
    case TLVM_ADD_M:
        {
            tlvmShort addr = TLVM_GET_16BIT(TLVM_REG_H, TLVM_REG_L);
            src = tlvmGetMemory(context, addr, TLVM_FLAG_READ);
        }
    break;
    case TLVM_ADD_A:
        src = &context->m_Registers[TLVM_REG_A];
    break;
    }

    if(src == NULL)
        tlvmReturnCode(INVALID_INPUT);

    tlvmShort res = (tlvmShort)context->m_Registers[TLVM_REG_A] + (tlvmShort)*src;
    TLVM_SET_FLAGS(res);
    context->m_Registers[TLVM_REG_A] = (tlvmByte)(res & 0xFF);

    // size of instruction    = 1
    context->m_ProgramCounter += 1;
    if(cycles)
        *cycles = 1;

    tlvmReturnCode(SUCCESS);
}

tlvmReturn tlvmADI(tlvmContext* context, tlvmByte* cycles)
{
    if(context == NULL)
        tlvmReturnCode(NO_CONTEXT);

    TLVM_GET_OP(op1, 1);

    tlvmShort res = (tlvmShort)context->m_Registers[TLVM_REG_A] + (tlvmShort)op1;
    TLVM_SET_FLAGS(res);
    context->m_Registers[TLVM_REG_A] = (tlvmByte)(res & 0xFF);

    // size of instruction    = 1
    // size of operand        = 1
    context->m_ProgramCounter += 2;
    if(cycles)
        *cycles = 2;

    tlvmReturnCode(SUCCESS);
}

tlvmReturn tlvmSUB(tlvmContext* context, tlvmByte* cycles)
{
    if(context == NULL)
        tlvmReturnCode(NO_CONTEXT);

    TLVM_GET_OP(opcode, 0);

    tlvmByte* src = NULL;

    switch(opcode)
    {
    case TLVM_SUB_B:
        src = &context->m_Registers[TLVM_REG_B];
    break;
    case TLVM_SUB_C:
        src = &context->m_Registers[TLVM_REG_C];
    break;
    case TLVM_SUB_D:
        src = &context->m_Registers[TLVM_REG_D];
    break;
    case TLVM_SUB_E:
        src = &context->m_Registers[TLVM_REG_E];
    break;
    case TLVM_SUB_H:
        src = &context->m_Registers[TLVM_REG_H];
    break;
    case TLVM_SUB_L:
        src = &context->m_Registers[TLVM_REG_L];
    break;
    case TLVM_SUB_M:
        {
            tlvmShort addr = TLVM_GET_16BIT(TLVM_REG_H, TLVM_REG_L);
            src = tlvmGetMemory(context, addr, TLVM_FLAG_READ);
        }
    break;
    case TLVM_SUB_A:
        src = &context->m_Registers[TLVM_REG_A];
    break;
    }

    if(src == NULL)
        tlvmReturnCode(INVALID_INPUT);

    tlvmShort res = (tlvmShort)context->m_Registers[TLVM_REG_A] - (tlvmShort)*src;
    TLVM_SET_FLAGS(res);
    context->m_Registers[TLVM_REG_A] = (tlvmByte)(res & 0xFF);

    // size of instruction    = 1
    context->m_ProgramCounter += 1;
    if(cycles)
        *cycles = 1;

    tlvmReturnCode(SUCCESS);
}

tlvmReturn tlvmSUI(tlvmContext* context, tlvmByte* cycles)
{
    if(context == NULL)
        tlvmReturnCode(NO_CONTEXT);

    TLVM_GET_OP(op1, 1);

    tlvmShort res = (tlvmShort)context->m_Registers[TLVM_REG_A] - (tlvmShort)op1;
    TLVM_SET_FLAGS(res);
    context->m_Registers[TLVM_REG_A] = (tlvmByte)(res & 0xFF);


    // size of instruction    = 1
    // size of operand        = 1
    context->m_ProgramCounter += 2;
    if(cycles)
        *cycles = 2;

    tlvmReturnCode(SUCCESS);
}

tlvmReturn tlvmINR(tlvmContext* context, tlvmByte* cycles)
{
    if(context == NULL)
        tlvmReturnCode(NO_CONTEXT);

    TLVM_GET_OP(opcode, 0);

    switch(opcode)
    {
    case TLVM_INR_B:
        context->m_Registers[TLVM_REG_B]++;
    break;
    case TLVM_INR_C:
        context->m_Registers[TLVM_REG_C]++;
    break;
    case TLVM_INR_D:
        context->m_Registers[TLVM_REG_D]++;
    break;
    case TLVM_INR_E:
        context->m_Registers[TLVM_REG_E]++;
    break;
    case TLVM_INR_H:
        context->m_Registers[TLVM_REG_H]++;
    break;
    case TLVM_INR_L:
        context->m_Registers[TLVM_REG_L]++;
    break;
    case TLVM_INR_M:
        {
            tlvmShort addr = TLVM_GET_16BIT(TLVM_REG_H, TLVM_REG_L);
            tlvmByte* val = tlvmGetMemory(context, addr, TLVM_FLAG_WRITE);
            if(val != NULL)
                (*val)++;
        }
    break;
    case TLVM_INR_A:
        context->m_Registers[TLVM_REG_A]++;
    break;
    }

    // size of instruction    = 1
    context->m_ProgramCounter += 1;
    if(cycles)
        *cycles = 1;

    tlvmReturnCode(SUCCESS);
}

tlvmReturn tlvmDCR(tlvmContext* context, tlvmByte* cycles)
{
    if(context == NULL)
        tlvmReturnCode(NO_CONTEXT);

    TLVM_GET_OP(opcode, 0);

    switch(opcode)
    {
    case TLVM_DCR_B:
        context->m_Registers[TLVM_REG_B]--;
    break;
    case TLVM_DCR_C:
        context->m_Registers[TLVM_REG_C]--;
    break;
    case TLVM_DCR_D:
        context->m_Registers[TLVM_REG_D]--;
    break;
    case TLVM_DCR_E:
        context->m_Registers[TLVM_REG_E]--;
    break;
    case TLVM_DCR_H:
        context->m_Registers[TLVM_REG_H]--;
    break;
    case TLVM_DCR_L:
        context->m_Registers[TLVM_REG_L]--;
    break;
    case TLVM_DCR_M:
        {
            tlvmShort addr = TLVM_GET_16BIT(TLVM_REG_H, TLVM_REG_L);
            tlvmByte* val = tlvmGetMemory(context, addr, TLVM_FLAG_WRITE);
            if(val != NULL)
                (*val)--;
        }
    break;
    case TLVM_DCR_A:
        context->m_Registers[TLVM_REG_A]--;
    break;
    }

    // size of instruction    = 1
    context->m_ProgramCounter += 1;
    if(cycles)
        *cycles = 1;

    tlvmReturnCode(SUCCESS);
}

tlvmReturn tlvmINX  (tlvmContext* context, tlvmByte* cycles)
{
    if(context == NULL)
        tlvmReturnCode(NO_CONTEXT);

    TLVM_GET_OP(opcode, 0);

    switch(opcode)
    {
    case TLVM_INX_B:
        {
            tlvmShort val = TLVM_GET_16BIT(TLVM_REG_B, TLVM_REG_C);
            TLVM_SET_16BIT(TLVM_REG_B, TLVM_REG_C, val + 1);
        }
    break;
    case TLVM_INX_D:
        {
            tlvmShort val = TLVM_GET_16BIT(TLVM_REG_D, TLVM_REG_E);
            TLVM_SET_16BIT(TLVM_REG_D, TLVM_REG_E, val + 1);
        }
    break;
    case TLVM_INX_H:
        {
            tlvmShort val = TLVM_GET_16BIT(TLVM_REG_H, TLVM_REG_L);
            TLVM_SET_16BIT(TLVM_REG_H, TLVM_REG_L, val + 1);
        }
    break;
    case TLVM_INX_SP:
        context->m_StackPointer++;
    break;
    }

    // size of instruction    = 1
    context->m_ProgramCounter += 1;
    if(cycles)
        *cycles = 5;

    tlvmReturnCode(SUCCESS);

}

tlvmReturn tlvmDCX  (tlvmContext* context, tlvmByte* cycles)
{
    if(context == NULL)
        tlvmReturnCode(NO_CONTEXT);

    TLVM_GET_OP(opcode, 0);

    switch(opcode)
    {
    case TLVM_DCX_B:
        TLVM_SET_16BIT(TLVM_REG_B, TLVM_REG_C, TLVM_GET_16BIT(TLVM_REG_B, TLVM_REG_C) - 1);
    break;
    case TLVM_DCX_D:
        TLVM_SET_16BIT(TLVM_REG_D, TLVM_REG_E, TLVM_GET_16BIT(TLVM_REG_D, TLVM_REG_E) - 1);
    break;
    case TLVM_DCX_H:
        TLVM_SET_16BIT(TLVM_REG_H, TLVM_REG_L, TLVM_GET_16BIT(TLVM_REG_H, TLVM_REG_L) - 1);
    break;
    case TLVM_DCX_SP:
        context->m_StackPointer--;
    break;
    }

    // size of instruction    = 1
    context->m_ProgramCounter += 1;
    if(cycles)
        *cycles = 5;

    tlvmReturnCode(SUCCESS);

}
