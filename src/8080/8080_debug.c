#include "tlvm_internal.h"

#ifdef  TLVM_HAS_8080
#ifdef  TLVM_DEBUG

tlvmReturn tlvm8080DebugGetInstruction(tlvmContext* context, tlvmChar** instruction)
{
	if(context == NULL)
		tlvmReturnCode(NO_CONTEXT);

    TLVM_GET_OP(opcode, 0);
    if(opcode == TLVM_NOP)
    {
    	sprintf(*instruction, "NOP");
		tlvmReturnCode(SUCCESS);
    }
    else if(opcode = TLVM_MOV_BB)
    {
    	sprintf(*instruction, "MOV B B");
    	tlvmReturnCode(SUCCESS);
    }

    sprintf(*instruction, "UNKNOWN");
    tlvmReturnCode(UNKNOWN_INSTRUCTION);
}

#endif/*TLVM_DEBUG*/
#endif/*TLVM_HAS_8080*/