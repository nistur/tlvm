#pragma once
#ifndef __TMPL_INTERNAL_H__
#define __TMPL_INTERNAL_H__

#include "template.h"

/***************************************
 * Library context
 * - holds current state
 ***************************************/
struct _tmplContext
{
};

/***************************************
 * Some basic memory management wrappers
 ***************************************/
#include <stdlib.h>
#define tmplMalloc(x) (x*)malloc(sizeof(x))
#define tmplFree(x)   free(x)

/***************************************
 * Error handling
 ***************************************/
extern tmplReturn  g_tmplError;
extern const char* g_tmplErrors[];
#define tmplReturn(x)				\
    {						\
	g_tmplError = TMPL_##x;			\
	return TMPL_##x;			\
    }



#endif/*__TMPL_INTERNAL_H__*/
