#include "tlvm_internal.h"

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
