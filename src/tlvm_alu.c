#include "tlvm_internal.h"

tlvmReturn tlvmAddALU(tlvmContext* context)
{
	if(context == NULL)
		tlvmReturnCode(NO_CONTEXT);

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

	unsigned char t = 0;
	for(unsigned char i = 0; i < 255; ++i)
		if(context->m_InstructionSet[i]) t++;

	tlvmReturnCode(SUCCESS);
}

/*********************************************
 * INSTRUCTIONS
 *********************************************/
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