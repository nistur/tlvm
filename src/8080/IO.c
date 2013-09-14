#include "tlvm_internal.h"

tlvmReturn tlvmOUT(tlvmContext* context, tlvmByte* cycles)
{
	if(context == NULL)
		tlvmReturnCode(NO_CONTEXT);

	TLVM_GET_OP(dest, 1);

	context->m_Ports[dest] = context->m_Registers[TLVM_REG_A];

    // size of instruction    = 1
    // size of operand        = 1
    context->m_ProgramCounter += 2;
    if(cycles)
    	*cycles =10;

	tlvmReturnCode(SUCCESS);
}

tlvmReturn tlvmIN(tlvmContext* context, tlvmByte* cycles)
{
	if(context == NULL)
		tlvmReturnCode(NO_CONTEXT);

	TLVM_GET_OP(dest, 1);

	context->m_Registers[TLVM_REG_A] = context->m_Ports[dest];

    // size of instruction    = 1
    // size of operand        = 1
    context->m_ProgramCounter += 2;
    if(cycles)
    	*cycles =10;

	tlvmReturnCode(SUCCESS);
}
