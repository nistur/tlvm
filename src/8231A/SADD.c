#ifdef  TLVM_HAS_8231A
#include "tlvm_internal.h"

tlvmReturn tlvm8231ASADD(tlvmContext* context, tlvmByte* cycles)
{
	if(context == NULL)
		tlvmReturnCode(NO_CONTEXT);

	tlvmShort A = 0;
	tlvmShort B = 0;
	((tlvmByte*)&B)[0] = tlvm8231AStackPop(context);
	((tlvmByte*)&B)[1] = tlvm8231AStackPop(context);
	((tlvmByte*)&A)[0] = tlvm8231AStackPop(context);
	((tlvmByte*)&A)[1] = tlvm8231AStackPop(context);
	tlvmShort R = A + B;
	tlvm8231AStackPush(context, ((tlvmByte*)&R)[0]);
	tlvm8231AStackPush(context, ((tlvmByte*)&R)[1]);

	context->m_Registers[TLVM_8231A_COMMAND] = 0x0;

	tlvmReturnCode(SUCCESS);
}

#endif/*TLVM_HAS_8231A*/