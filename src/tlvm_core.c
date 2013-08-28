#include "tlvm_internal.h"

tlvmReturn tlvmNOOP(tlvmContext* context)
{
	if(context == NULL)
		tlvmReturnCode(NO_CONTEXT);

	context->m_ProgramCounter += 1;

	tlvmReturnCode(SUCCESS);
}