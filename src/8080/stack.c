#include "tlvm_internal.h"

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
	TLVM_STACK_PUSH(srcHi);
	TLVM_STACK_PUSH(srcLo);

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

	TLVM_STACK_POP(*dstLo);
	TLVM_STACK_POP(*dstHi);

	// size of instruction    = 1
	context->m_ProgramCounter += 1;
    if(cycles)
    	*cycles = 10;

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

tlvmReturn tlvmSTA(tlvmContext* context, tlvmByte* cycles)
{
	if(context == NULL)
		tlvmReturnCode(NO_CONTEXT);

	TLVM_GET_OP(opLo,  1);
	TLVM_GET_OP(opHi, 2);
	tlvmShort addr = ((tlvmShort)opHi) << 8 | opLo;

	context->m_StackPointer = addr;


	// size of instruction    = 1
	// size of address        = 2
	context->m_ProgramCounter += 3;
    if(cycles)
    	*cycles =13;

	tlvmReturnCode(SUCCESS);
}