#pragma once
#ifndef __TEMPLATE_H__
#define __TEMPLATE_H__

#ifdef __cplusplus
extern "C" {
#endif/*__cplusplus*/

typedef int tmplReturn;

typedef struct _tmplContext tmplContext;

#define TMPL_SUCCESS    0
#define TMPL_NO_CONTEXT 1

tmplContext* tmplInitContext     ();
tmplReturn   tmplTerminateContext(tmplContext** context);


#ifdef __cplusplus
}
#endif/*__cplusplus*/


#endif/*__TEMPLATE_H__*/
