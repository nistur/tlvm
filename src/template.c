#include "template.h"

#include <stdlib.h>

struct _tmplContext
{
};

tmplReturn tmplClearContext(tmplContext* context)
{
    return TMPL_SUCCESS;
}

tmplContext* tmplInitContext()
{
    tmplContext* context = (tmplContext*)malloc(sizeof(tmplContext));
    if(tmplClearContext(context) != TMPL_SUCCESS)
	tmplTerminateContext(&context);
    return context;
}

tmplReturn tmplTerminateContext(tmplContext** context)
{
    if(*context == 0)
	return TMPL_NO_CONTEXT;

    free(*context);
    *context = 0;
    return TMPL_SUCCESS;
}
