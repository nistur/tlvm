#include "tlvm_internal.h"

tlvmReturn tlvmJMP(tlvmContext* context, tlvmByte* cycles)
{
	if(context == NULL)
		tlvmReturnCode(NO_CONTEXT);

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

	tlvmReturnCode(SUCCESS);
}

tlvmReturn tlvmCALL(tlvmContext* context, tlvmByte* cycles)
{
	if(context == NULL)
		tlvmReturnCode(NO_CONTEXT);

	TLVM_GET_OP(opcode, 0);
	TLVM_GET_OP(opLow,  1);
	TLVM_GET_OP(opHigh, 2);
	tlvmShort addr = (tlvmShort)opHigh << 8 | (tlvmShort)opLow;

	// increment PC before logic as it is fallback
	// size of instruction    = 1
	// size of address        = 2
	context->m_ProgramCounter += 3;

	// rather than just getting one address, get each location manually
	// as in theory it might go across memory boundaries
	tlvmByte* dstHi = tlvmGetMemory(context, context->m_StackPointer - 1, TLVM_FLAG_WRITE);
	tlvmByte* dstLo = tlvmGetMemory(context, context->m_StackPointer - 2, TLVM_FLAG_WRITE);
	if(dstHi == NULL || dstLo == NULL)
		tlvmReturnCode(INVALID_INPUT);
	tlvmByte srcHi = (tlvmByte)(context->m_ProgramCounter >> 8);
	tlvmByte srcLo = (tlvmByte)(context->m_ProgramCounter & 0xFF);

	tlvmByte cycleCnt = 11;
	switch(opcode)
	{
	case TLVM_CNZ:
		if(!TLVM_FLAG_ISSET(Z))
		{
			*dstHi = srcHi; *dstLo = srcLo;
			context->m_ProgramCounter = addr;
			cycleCnt = 17;
		}
	break;
	case TLVM_CZ:
		if(TLVM_FLAG_ISSET(Z))
		{
			*dstHi = srcHi; *dstLo = srcLo;
			context->m_ProgramCounter = addr;
			cycleCnt = 17;
		}
	break;
	case TLVM_CNC:
		if(!TLVM_FLAG_ISSET(C))
		{
			*dstHi = srcHi; *dstLo = srcLo;
			context->m_ProgramCounter = addr;
			cycleCnt = 17;
		}
	break;
	case TLVM_CC:
		if(TLVM_FLAG_ISSET(C))
		{
			*dstHi = srcHi; *dstLo = srcLo;
			context->m_ProgramCounter = addr;
			cycleCnt = 17;
		}
	break;
	case TLVM_CPO:
		if(!TLVM_FLAG_ISSET(P))
		{
			*dstHi = srcHi; *dstLo = srcLo;
			context->m_ProgramCounter = addr;
			cycleCnt = 17;
		}
	break;
	case TLVM_CPE:
		if(TLVM_FLAG_ISSET(P))
		{
			*dstHi = srcHi; *dstLo = srcLo;
			context->m_ProgramCounter = addr;
			cycleCnt = 17;
		}
	break;
	case TLVM_CP:
		if(!TLVM_FLAG_ISSET(S))
		{
			*dstHi = srcHi; *dstLo = srcLo;
			context->m_ProgramCounter = addr;
			cycleCnt = 17;
		}
	break;
	case TLVM_CM:
		if(TLVM_FLAG_ISSET(S))
		{
			*dstHi = srcHi; *dstLo = srcLo;
			context->m_ProgramCounter = addr;
			cycleCnt = 17;
		}
	break;
	case TLVM_CALL:
	{
		*dstHi = srcHi; *dstLo = srcLo;
		context->m_ProgramCounter = addr;
		cycleCnt = 17;
	}
	break;
	}

    context->m_StackPointer -= 2;

    if(cycles)
    	*cycles = cycleCnt;

	tlvmReturnCode(SUCCESS);
}

tlvmReturn tlvmRET(tlvmContext* context, tlvmByte* cycles)
{
	if(context == NULL)
		tlvmReturnCode(NO_CONTEXT);

	TLVM_GET_OP(opcode, 0);

	// increment PC before logic as it is fallback
	// size of instruction    = 1
	context->m_ProgramCounter += 1;

	// rather than just getting one address, get each location manually
	// as in theory it might go across memory boundaries
	tlvmByte* srcHi = tlvmGetMemory(context, context->m_StackPointer + 1, TLVM_FLAG_WRITE);
	tlvmByte* srcLo = tlvmGetMemory(context, context->m_StackPointer + 0, TLVM_FLAG_WRITE);
	if(srcHi == NULL || srcLo == NULL)
		tlvmReturnCode(INVALID_INPUT);
	tlvmShort addr = (tlvmShort)((*srcHi) << 8) | ((tlvmShort)(*srcLo));

	tlvmByte cycleCnt = 5;
	switch(opcode)
	{
	case TLVM_CNZ:
		if(!TLVM_FLAG_ISSET(Z))
		{
			context->m_ProgramCounter = addr;
			cycleCnt = 11;
		}
	break;
	case TLVM_CZ:
		if(TLVM_FLAG_ISSET(Z))
		{
			context->m_ProgramCounter = addr;
			cycleCnt = 11;
		}
	break;
	case TLVM_CNC:
		if(!TLVM_FLAG_ISSET(C))
		{
			context->m_ProgramCounter = addr;
			cycleCnt = 11;
		}
	break;
	case TLVM_CC:
		if(TLVM_FLAG_ISSET(C))
		{
			context->m_ProgramCounter = addr;
			cycleCnt = 11;
		}
	break;
	case TLVM_CPO:
		if(!TLVM_FLAG_ISSET(P))
		{
			context->m_ProgramCounter = addr;
			cycleCnt = 11;
		}
	break;
	case TLVM_CPE:
		if(TLVM_FLAG_ISSET(P))
		{
			context->m_ProgramCounter = addr;
			cycleCnt = 11;
		}
	break;
	case TLVM_CP:
		if(!TLVM_FLAG_ISSET(S))
		{
			context->m_ProgramCounter = addr;
			cycleCnt = 11;
		}
	break;
	case TLVM_CM:
		if(TLVM_FLAG_ISSET(S))
		{
			context->m_ProgramCounter = addr;
			cycleCnt = 11;
		}
	break;
	case TLVM_CALL:
	{
		context->m_ProgramCounter = addr;
		cycleCnt = 10;
	}
	break;
	}

    context->m_StackPointer += 2;

    if(cycles)
    	*cycles = cycleCnt;

	tlvmReturnCode(SUCCESS);
}
