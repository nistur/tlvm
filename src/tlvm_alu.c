#include "tlvm_internal.h"

tlvmReturn tlvmAddALU(tlvmContext* context)
{
	if(context == NULL)
		tlvmReturnCode(NO_CONTEXT);
	context->m_InstructionSet[TLVM_ADD_RM] = tlvmADD;
	context->m_InstructionSet[TLVM_ADD_MR] = tlvmADD;

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
	tlvmByte op2    = context->m_Program[context->m_ProgramCounter+2];

	tlvmByte* src = NULL;
	tlvmByte* dst = NULL;

	if(opcode == TLVM_ADD_RM)
	{
		// src is a register, dst is a memory location
		src = &context->m_Registers[op2];
		dst = &context->m_Memory[op1];
	}
	else/*(opcode == TLVM_ADD_MR)*/
	{
		// dst is a register, src is a memory location
		dst = &context->m_Registers[op2];
		src = &context->m_Memory[op2];
	}

	if(src == NULL || dst == NULL)
		tlvmReturnCode(INVALID_INPUT);

	// add src to dst
	*dst += *src;

	// size of instruction    = 1
	// size of first operand  = 1
	// size of second operand = 1
	context->m_ProgramCounter += 3;

	tlvmReturnCode(SUCCESS);
}