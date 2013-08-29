#include "tlvm_internal.h"


tlvmReturn tlvmInitCore(tlvmContext* context)
{
	if(context == NULL)
		tlvmReturnCode(NO_CONTEXT);

    context->m_InstructionSet[TLVM_NOOP] = tlvmNOOP;

    context->m_InstructionSet[TLVM_MOV_B] = tlvmMOV;
    context->m_InstructionSet[TLVM_MOV_C] = tlvmMOV;
    context->m_InstructionSet[TLVM_MOV_D] = tlvmMOV;
    context->m_InstructionSet[TLVM_MOV_E] = tlvmMOV;
    context->m_InstructionSet[TLVM_MOV_H] = tlvmMOV;
    context->m_InstructionSet[TLVM_MOV_L] = tlvmMOV;
    context->m_InstructionSet[TLVM_MOV_A] = tlvmMOV;

    context->m_InstructionSet[TLVM_ANA_B] = tlvmANA;
    context->m_InstructionSet[TLVM_ANA_C] = tlvmANA;
    context->m_InstructionSet[TLVM_ANA_D] = tlvmANA;
    context->m_InstructionSet[TLVM_ANA_E] = tlvmANA;
    context->m_InstructionSet[TLVM_ANA_H] = tlvmANA;
    context->m_InstructionSet[TLVM_ANA_L] = tlvmANA;
    context->m_InstructionSet[TLVM_ANA_M] = tlvmANA;
    context->m_InstructionSet[TLVM_ANA_A] = tlvmANA;

    context->m_InstructionSet[TLVM_ANI]   = tlvmANI;

	tlvmReturnCode(SUCCESS);
}

tlvmReturn tlvmNOOP(tlvmContext* context)
{
	if(context == NULL)
		tlvmReturnCode(NO_CONTEXT);

	context->m_ProgramCounter += 1;

	tlvmReturnCode(SUCCESS);
}

tlvmReturn tlvmMOV(tlvmContext* context)
{
	if(context == NULL)
		tlvmReturnCode(NO_CONTEXT);

	tlvmByte opcode = context->m_Program[context->m_ProgramCounter+0];

	tlvmShort addr = ((tlvmShort)context->m_Registers[TLVM_REG_H]) << 8 | (tlvmShort)context->m_Registers[TLVM_REG_L];
	tlvmByte* src = NULL;

	switch(opcode)
	{
	case TLVM_MOV_B:
		src = &context->m_Registers[TLVM_REG_B];
	break;
	case TLVM_MOV_C:
		src = &context->m_Registers[TLVM_REG_C];
	break;
	case TLVM_MOV_D:
		src = &context->m_Registers[TLVM_REG_D];
	break;
	case TLVM_MOV_E:
		src = &context->m_Registers[TLVM_REG_E];
	break;
	case TLVM_MOV_H:
		src = &context->m_Registers[TLVM_REG_H];
	break;
	case TLVM_MOV_L:
		src = &context->m_Registers[TLVM_REG_L];
	break;
	case TLVM_MOV_A:
		src = &context->m_Registers[TLVM_REG_A];
	break;
	}

	if(src == NULL)
		tlvmReturnCode(INVALID_INPUT);

	context->m_Memory[addr] = *src;

	// size of instruction    = 1
	context->m_ProgramCounter += 1;

	tlvmReturnCode(SUCCESS);
}

tlvmReturn tlvmANA(tlvmContext* context)
{
	if(context == NULL)
		tlvmReturnCode(NO_CONTEXT);

	tlvmByte opcode = context->m_Program[context->m_ProgramCounter+0];

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
			tlvmShort addr = ((tlvmShort)context->m_Registers[TLVM_REG_H]) << 8 | (tlvmShort)context->m_Registers[TLVM_REG_L];
			src = &context->m_Memory[addr];
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

	tlvmReturnCode(SUCCESS);
}

tlvmReturn tlvmANI(tlvmContext* context)
{
	if(context == NULL)
		tlvmReturnCode(NO_CONTEXT);

	tlvmByte operand = context->m_Program[context->m_ProgramCounter+1];

	context->m_Registers[TLVM_REG_A] &= operand;

	// size of instruction    = 1
	// size of operand        = 1
	context->m_ProgramCounter += 2;

	tlvmReturnCode(SUCCESS);
}