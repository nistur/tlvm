#ifdef  TLVM_HAS_8231A
#include "tlvm_internal.h"

tlvmReturn tlvm8231APOPS(tlvmContext* context, tlvmByte* cycles)
{
	if(context == NULL)
		tlvmReturnCode(NO_CONTEXT);

	// pop off 16 bits from the stack
	tlvmShort val = 0;
	((tlvmByte*)&val)[0] = tlvm8231AStackPop(context);
	((tlvmByte*)&val)[1] = tlvm8231AStackPop(context);

	context->m_Registers[TLVM_8231A_COMMAND] = 0x0;

	tlvmReturnCode(SUCCESS);
}

#endif/*TLVM_HAS_8231A*/