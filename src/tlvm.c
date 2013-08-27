#include "tlvm_internal.h"

tlvmReturn tlvmClearContext(tlvmContext* context)
{
    tlvmReturn(SUCCESS);
}

tlvmContext* tlvmInitContext()
{
    tlvmContext* context = tlvmMalloc(tlvmContext);
    if(tlvmClearContext(context) != TLVM_SUCCESS)
	tlvmTerminateContext(&context);
    return context;
}

tlvmReturn tlvmTerminateContext(tlvmContext** context)
{
    if(*context == 0)
	tlvmReturn(NO_CONTEXT);

    tlvmFree(*context);
    *context = 0;
    tlvmReturn(SUCCESS);
}

const char* tlvmError()
{
    return g_tlvmErrors[g_tlvmError];
}
