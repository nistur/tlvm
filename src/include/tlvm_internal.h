#pragma once
#ifndef __TLVM_INTERNAL_H__
#define __TLVM_INTERNAL_H__

#include "tlvm.h"

/***************************************
 * Library context
 * - holds current state
 ***************************************/
struct _tlvmContext
{
};

/***************************************
 * Some basic memory management wrappers
 ***************************************/
#include <stdlib.h>
#define tlvmMalloc(x) (x*)malloc(sizeof(x))
#define tlvmFree(x)   free(x)

/***************************************
 * Error handling
 ***************************************/
extern tlvmReturn  g_tlvmError;
extern const char* g_tlvmErrors[];
#define tlvmReturn(x)				\
    {						\
	g_tlvmError = TLVM_##x;			\
	return TLVM_##x;			\
    }



#endif/*__TLVM_INTERNAL_H__*/
