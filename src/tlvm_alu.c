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

	context->m_InstructionSet[TLVM_ADI] = tlvmADI;

	tlvmReturnCode(SUCCESS);
}

/*********************************************
 * INSTRUCTIONS
 *********************************************/
tlvmReturn tlvmADD(tlvmContext* context)
{
	if(context == NULL)
		tlvmReturnCode(NO_CONTEXT);

	tlvmByte opcode = context->m_Program[context->m_ProgramCounter+0];

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
			tlvmShort addr = ((tlvmShort)context->m_Registers[TLVM_REG_H]) << 8 | (tlvmShort)context->m_Registers[TLVM_REG_L];
			src = &context->m_Memory[addr];
		}
	break;
	case TLVM_ADD_A:
		src = &context->m_Registers[TLVM_REG_A];
	break;
	}

	if(src == NULL)
		tlvmReturnCode(INVALID_INPUT);

	// add src to dst
	context->m_Registers[TLVM_REG_A] += *src;

	// size of instruction    = 1
	context->m_ProgramCounter += 1;

	tlvmReturnCode(SUCCESS);
}

tlvmReturn tlvmADI(tlvmContext* context)
{
	if(context == NULL)
		tlvmReturnCode(NO_CONTEXT);

	tlvmByte op1    = context->m_Program[context->m_ProgramCounter+1];

	context->m_Registers[TLVM_REG_A] += op1;

	// size of instruction    = 1
	// size of operand        = 1
	context->m_ProgramCounter += 2;

	tlvmReturnCode(SUCCESS);
}