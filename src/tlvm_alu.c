#include "tlvm_internal.h"

tlvmReturn tlvmAddALU(tlvmContext* context)
{
	if(context == NULL)
		tlvmReturnCode(NO_CONTEXT);
	context->m_InstructionSet[TLVM_ADD_B] = tlvmADD;
	context->m_InstructionSet[TLVM_ADD_C] = tlvmADD;

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
	tlvmByte op1    = context->m_Program[context->m_ProgramCounter+1];

	tlvmByte* src = NULL;
	tlvmByte* dst = &context->m_Registers[TLVM_REG_A];

	if(opcode == TLVM_ADD_B)
	{
		src = &context->m_Registers[TLVM_REG_B];
	}
	else if(opcode == TLVM_ADD_C)
	{
		src = &context->m_Registers[TLVM_REG_C];
	}

	if(src == NULL || dst == NULL)
		tlvmReturnCode(INVALID_INPUT);

	// add src to dst
	*dst += *src;

	// size of instruction    = 1
	// size of operand        = 1
	context->m_ProgramCounter += 2;

	tlvmReturnCode(SUCCESS);
}