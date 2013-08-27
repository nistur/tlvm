#include "tmpl_internal.h"

tmplReturn tmplClearContext(tmplContext* context)
{
    tmplReturn(SUCCESS);
}

tmplContext* tmplInitContext()
{
    tmplContext* context = tmplMalloc(tmplContext);
    if(tmplClearContext(context) != TMPL_SUCCESS)
	tmplTerminateContext(&context);
    return context;
}

tmplReturn tmplTerminateContext(tmplContext** context)
{
    if(*context == 0)
	tmplReturn(NO_CONTEXT);

    tmplFree(*context);
    *context = 0;
    tmplReturn(SUCCESS);
}

const char* tmplError()
{
    return g_tmplErrors[g_tmplError];
}
