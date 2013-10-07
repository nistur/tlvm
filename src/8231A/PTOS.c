#ifdef  TLVM_HAS_8231A
#include "tlvm_internal.h"

tlvmReturn tlvm8231APTOS(tlvmContext* context, tlvmByte* cycles)
{
	if(context == NULL)
		tlvmReturnCode(NO_CONTEXT);

	tlvmShort val = 0;
	((tlvmByte*)&val)[0] = tlvm8231AStackPop(context);
	((tlvmByte*)&val)[1] = tlvm8231AStackPop(context);

	// push the value back onto the stack so it's there twice
	tlvm8231AStackPush(context, ((tlvmByte*)&val)[1]);
	tlvm8231AStackPush(context, ((tlvmByte*)&val)[0]);
	tlvm8231AStackPush(context, ((tlvmByte*)&val)[1]);
	tlvm8231AStackPush(context, ((tlvmByte*)&val)[0]);

	context->m_Registers[TLVM_8231A_COMMAND] = 0x0;

	tlvmReturnCode(SUCCESS);
}

#endif/*TLVM_HAS_8231A*/