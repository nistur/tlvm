#pragma once
#ifndef __TEMPLATE_H__
#define __TEMPLATE_H__
#ifdef __cplusplus
extern "C" {
#endif/*__cplusplus*/

#ifdef TMPL_DYNAMIC
# ifdef WIN32
#  ifdef TMPL_BUILD
#   define TMPL_EXPORT __declspec( dllexport )
#  else
#   define TMPL_EXPORT __declspec( dllimport )
#  endif
# endif
#endif
 
#ifndef TMPL_EXPORT
# define TMPL_EXPORT
#endif

typedef int tmplReturn;

typedef struct _tmplContext tmplContext;

#define TMPL_SUCCESS    0
#define TMPL_NO_CONTEXT 1

TMPL_EXPORT tmplContext* tmplInitContext     ();
TMPL_EXPORT tmplReturn   tmplTerminateContext(tmplContext** context);


#ifdef __cplusplus
}
#endif/*__cplusplus*/
#endif/*__TEMPLATE_H__*/
