#include "tlvm.h"

tlvmReturn g_tlvmStatus;
const char* g_tlvmStatusMessages[] = 
{
    "Success",							//TLVM_SUCCESS
    "Null context",						//TLVM_NO_CONTEXT
    "Memory has not been set",			//TLVM_NO_MEMORY
    "Undefined invalid input",			//TLVM_INVALID_INPUT
    "Unrecognised instruction",			//TLVM_UNKNOWN_INSTRUCTION
    "",									//TLVM_EXIT (internal only)
    "Memory overlaps existing address",	//TLVM_MEMORY_OVERLAP
};
