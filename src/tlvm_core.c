#include "tlvm_internal.h"


tlvmReturn tlvmInitCore(tlvmContext* context)
{
    if(context == NULL)
        tlvmReturnCode(NO_CONTEXT);
    
    context->m_InstructionSet[TLVM_NOP]    = tlvmNOP;
    
    context->m_InstructionSet[TLVM_LXI_B]  = tlvmLXI;
    context->m_InstructionSet[TLVM_LXI_D]  = tlvmLXI;
    context->m_InstructionSet[TLVM_LXI_H]  = tlvmLXI;
    context->m_InstructionSet[TLVM_LXI_SP] = tlvmLXI;
    
    context->m_InstructionSet[TLVM_LDAX_B] = tlvmLDAX;
    context->m_InstructionSet[TLVM_LDAX_D] = tlvmLDAX;

    context->m_InstructionSet[TLVM_STAX_B] = tlvmSTAX;
    context->m_InstructionSet[TLVM_STAX_D] = tlvmSTAX;
    
    context->m_InstructionSet[TLVM_MVI_B]  = tlvmMVI;
    context->m_InstructionSet[TLVM_MVI_C]  = tlvmMVI;
    context->m_InstructionSet[TLVM_MVI_D]  = tlvmMVI;
    context->m_InstructionSet[TLVM_MVI_E]  = tlvmMVI;
    context->m_InstructionSet[TLVM_MVI_H]  = tlvmMVI;
    context->m_InstructionSet[TLVM_MVI_L]  = tlvmMVI;
    context->m_InstructionSet[TLVM_MVI_M]  = tlvmMVI;
    context->m_InstructionSet[TLVM_MVI_A]  = tlvmMVI;

    context->m_InstructionSet[TLVM_LDA]    = tlvmLDA;
    
    context->m_InstructionSet[TLVM_MOV_B]  = tlvmMOV;
    context->m_InstructionSet[TLVM_MOV_C]  = tlvmMOV;
    context->m_InstructionSet[TLVM_MOV_D]  = tlvmMOV;
    context->m_InstructionSet[TLVM_MOV_E]  = tlvmMOV;
    context->m_InstructionSet[TLVM_MOV_H]  = tlvmMOV;
    context->m_InstructionSet[TLVM_MOV_L]  = tlvmMOV;
    context->m_InstructionSet[TLVM_MOV_A]  = tlvmMOV;
    
    context->m_InstructionSet[TLVM_ANA_B]  = tlvmANA;
    context->m_InstructionSet[TLVM_ANA_C]  = tlvmANA;
    context->m_InstructionSet[TLVM_ANA_D]  = tlvmANA;
    context->m_InstructionSet[TLVM_ANA_E]  = tlvmANA;
    context->m_InstructionSet[TLVM_ANA_H]  = tlvmANA;
    context->m_InstructionSet[TLVM_ANA_L]  = tlvmANA;
    context->m_InstructionSet[TLVM_ANA_M]  = tlvmANA;
    context->m_InstructionSet[TLVM_ANA_A]  = tlvmANA;
    
    context->m_InstructionSet[TLVM_ANI]    = tlvmANI;
    
    tlvmReturnCode(SUCCESS);
}

tlvmReturn tlvmNOP(tlvmContext* context)
{
    if(context == NULL)
        tlvmReturnCode(NO_CONTEXT);
    
    context->m_ProgramCounter += 1;
    
    tlvmReturnCode(SUCCESS);
}

tlvmReturn tlvmLXI(tlvmContext* context)
{
    if(context == NULL)
        tlvmReturnCode(NO_CONTEXT);
    
    tlvmByte opcode = context->m_Program[context->m_ProgramCounter+0];
    tlvmByte opLow  = context->m_Program[context->m_ProgramCounter+1];
    tlvmByte opHigh = context->m_Program[context->m_ProgramCounter+2];
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
        tlvmReturnCode(UNIMPLEMENTED); // stack pointer
	break;
    }
    
    // size of instruction    = 1
    // size of operand        = 2
    context->m_ProgramCounter += 3;
    
    tlvmReturnCode(SUCCESS);
}

tlvmReturn tlvmSTAX(tlvmContext* context)
{
    if(context == NULL)
        tlvmReturnCode(NO_CONTEXT);
    
    tlvmByte opcode = context->m_Program[context->m_ProgramCounter+0];

    tlvmShort addr = 0;
    switch(opcode)
    {
    case TLVM_STAX_B:
    	addr = TLVM_GET_16BIT(TLVM_REG_B, TLVM_REG_C);
	break;
    case TLVM_STAX_D:
    	addr = TLVM_GET_16BIT(TLVM_REG_B, TLVM_REG_C);
	break;
    }
    context->m_Memory[addr] = context->m_Registers[TLVM_REG_A];
    
    // size of instruction    = 1
    context->m_ProgramCounter += 1;
    
    tlvmReturnCode(SUCCESS);
}

tlvmReturn tlvmMVI(tlvmContext* context)
{
	if(context == NULL)
		tlvmReturnCode(NO_CONTEXT);

	tlvmByte opcode = context->m_Program[context->m_ProgramCounter+0];
	tlvmByte operand  = context->m_Program[context->m_ProgramCounter+1];
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
		context->m_Memory[TLVM_GET_16BIT(TLVM_REG_H, TLVM_REG_L)] = operand;
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

	tlvmReturnCode(SUCCESS);
}

tlvmReturn tlvmSHLD(tlvmContext* context)
{
	if(context == NULL)
		tlvmReturnCode(NO_CONTEXT);

    tlvmShort opLow  = context->m_Program[context->m_ProgramCounter+1];
    tlvmByte opHigh = context->m_Program[context->m_ProgramCounter+2];

    tlvmShort addr = opHigh << 8 | opLow;
    context->m_Memory[addr+0] = context->m_Registers[TLVM_REG_L];
    context->m_Memory[addr+1] = context->m_Registers[TLVM_REG_H];

	// size of instruction    = 1
	// size of operand        = 2
	context->m_ProgramCounter += 3;

	tlvmReturnCode(SUCCESS);
}

tlvmReturn tlvmLDA(tlvmContext* context)
{
	if(context == NULL)
		tlvmReturnCode(NO_CONTEXT);

    tlvmShort opLow  = context->m_Program[context->m_ProgramCounter+1];
    tlvmByte opHigh = context->m_Program[context->m_ProgramCounter+2];

    tlvmShort addr = opHigh << 8 | opLow;

    context->m_Registers[TLVM_REG_A] = context->m_Memory[addr];

	// size of instruction    = 1
	// size of operand        = 1
	context->m_ProgramCounter += 2;

	tlvmReturnCode(SUCCESS);
}

tlvmReturn tlvmLDAX(tlvmContext* context)
{
	if(context == NULL)
		tlvmReturnCode(NO_CONTEXT);

	tlvmByte opcode = context->m_Program[context->m_ProgramCounter+0];
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
	context->m_Registers[TLVM_REG_A] = context->m_Memory[addr];

	// size of instruction    = 1
	context->m_ProgramCounter += 1;

	tlvmReturnCode(SUCCESS);
}

tlvmReturn tlvmMOV(tlvmContext* context)
{
	if(context == NULL)
		tlvmReturnCode(NO_CONTEXT);

	tlvmByte opcode = context->m_Program[context->m_ProgramCounter+0];

	tlvmShort addr = TLVM_GET_16BIT(TLVM_REG_H, TLVM_REG_L);
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
			tlvmShort addr = TLVM_GET_16BIT(TLVM_REG_H, TLVM_REG_L);
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
