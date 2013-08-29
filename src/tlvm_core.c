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