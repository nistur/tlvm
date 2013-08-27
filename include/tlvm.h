#pragma once
#ifndef __TEMPLATE_H__
#define __TEMPLATE_H__
#ifdef __cplusplus
extern "C" {
#endif/*__cplusplus*/

#ifdef TLVM_DYNAMIC
# ifdef WIN32
#  ifdef TLVM_BUILD
#   define TLVM_EXPORT __declspec( dllexport )
#  else
#   define TLVM_EXPORT __declspec( dllimport )
#  endif
# endif
#endif
 
#ifndef TLVM_EXPORT
# define TLVM_EXPORT
#endif

typedef int tlvmReturn;

typedef struct _tlvmContext tlvmContext;

#define TLVM_SUCCESS    0
#define TLVM_NO_CONTEXT 1

TLVM_EXPORT tlvmContext* tlvmInitContext     ();
TLVM_EXPORT tlvmReturn   tlvmTerminateContext(tlvmContext** context);
TLVM_EXPORT const char*  tlvmError();

#ifdef __cplusplus
}
#endif/*__cplusplus*/
#endif/*__TEMPLATE_H__*/
