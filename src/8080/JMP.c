#ifdef  TLVM_HAS_8080
#include "tlvm_internal.h"

tlvmReturn tlvmJMP(tlvmContext* context, tlvmByte* cycles)
{
	if(context == NULL)
		TLVM_RETURN_CODE(NO_CONTEXT);

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

	TLVM_RETURN_CODE(SUCCESS);
}

tlvmReturn tlvmCALL(tlvmContext* context, tlvmByte* cycles)
{
	if(context == NULL)
		TLVM_RETURN_CODE(NO_CONTEXT);

	TLVM_GET_OP(opcode, 0);
	TLVM_GET_OP(opLow,  1);
	TLVM_GET_OP(opHigh, 2);
	tlvmShort addr = (tlvmShort)opHigh << 8 | (tlvmShort)opLow;

	// increment PC before logic as it is after the current instruction
	// that we want to return to
	// size of instruction    = 1
	// size of address        = 2
	context->m_ProgramCounter += 3;

	tlvmByte cycleCnt = 11;
	switch(opcode)
	{
	case TLVM_CNZ:
		if(!TLVM_FLAG_ISSET(Z))
		{
			TLVM_PUSH_PC(addr);
			cycleCnt = 17;
		}
	break;
	case TLVM_CZ:
		if(TLVM_FLAG_ISSET(Z))
		{
			TLVM_PUSH_PC(addr);
			cycleCnt = 17;
		}
	break;
	case TLVM_CNC:
		if(!TLVM_FLAG_ISSET(C))
		{
			TLVM_PUSH_PC(addr);
			cycleCnt = 17;
		}
	break;
	case TLVM_CC:
		if(TLVM_FLAG_ISSET(C))
		{
			TLVM_PUSH_PC(addr);
			cycleCnt = 17;
		}
	break;
	case TLVM_CPO:
		if(!TLVM_FLAG_ISSET(P))
		{
			TLVM_PUSH_PC(addr);
			cycleCnt = 17;
		}
	break;
	case TLVM_CPE:
		if(TLVM_FLAG_ISSET(P))
		{
			TLVM_PUSH_PC(addr);
			cycleCnt = 17;
		}
	break;
	case TLVM_CP:
		if(!TLVM_FLAG_ISSET(S))
		{
			TLVM_PUSH_PC(addr);
			cycleCnt = 17;
		}
	break;
	case TLVM_CM:
		if(TLVM_FLAG_ISSET(S))
		{
			TLVM_PUSH_PC(addr);
			cycleCnt = 17;
		}
	break;
	case TLVM_CALL:
	{
		TLVM_PUSH_PC(addr);
		context->m_ProgramCounter = addr;
		cycleCnt = 17;
	}
	break;
	}

    //context->m_StackPointer -= 2;

    if(cycles)
    	*cycles = cycleCnt;

	TLVM_RETURN_CODE(SUCCESS);
}

tlvmReturn tlvmRET(tlvmContext* context, tlvmByte* cycles)
{
	if(context == NULL)
		TLVM_RETURN_CODE(NO_CONTEXT);

	TLVM_GET_OP(opcode, 0);

	// increment PC before logic as it is fallback
	// size of instruction    = 1
	context->m_ProgramCounter += 1;

	tlvmByte cycleCnt = 5;
	switch(opcode)
	{
	case TLVM_RNZ:
		if(!TLVM_FLAG_ISSET(Z))
		{
			TLVM_POP_PC();
			cycleCnt = 11;
		}
	break;
	case TLVM_RZ:
		if(TLVM_FLAG_ISSET(Z))
		{
			TLVM_POP_PC();
			cycleCnt = 11;
		}
	break;
	case TLVM_RNC:
		if(!TLVM_FLAG_ISSET(C))
		{
			TLVM_POP_PC();
			cycleCnt = 11;
		}
	break;
	case TLVM_RC:
		if(TLVM_FLAG_ISSET(C))
		{
			TLVM_POP_PC();
			cycleCnt = 11;
		}
	break;
	case TLVM_RPO:
		if(!TLVM_FLAG_ISSET(P))
		{
			TLVM_POP_PC();
			cycleCnt = 11;
		}
	break;
	case TLVM_RPE:
		if(TLVM_FLAG_ISSET(P))
		{
			TLVM_POP_PC();
			cycleCnt = 11;
		}
	break;
	case TLVM_RP:
		if(!TLVM_FLAG_ISSET(S))
		{
			TLVM_POP_PC();
			cycleCnt = 11;
		}
	break;
	case TLVM_RM:
		if(TLVM_FLAG_ISSET(S))
		{
			TLVM_POP_PC();
			cycleCnt = 11;
		}
	break;
	case TLVM_RET:
	{
		TLVM_POP_PC();
		cycleCnt = 10;
	}
	break;
	}

    //context->m_StackPointer += 2;

    if(cycles)
    	*cycles = cycleCnt;

	TLVM_RETURN_CODE(SUCCESS);
}
#endif/*TLVM_HAS_8080*/