#pragma once
#ifndef __TLVM_H__
#define __TLVM_H__
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

typedef unsigned char  tlvmByte;
typedef unsigned short tlvmShort;

typedef struct _tlvmContext tlvmContext;

#define TLVM_SUCCESS             0
#define TLVM_NO_CONTEXT          1
#define TLVM_NO_MEMORY           2
#define TLVM_INVALID_INPUT       3
#define TLVM_UNKNOWN_INSTRUCTION 4
#define TLVM_EXIT                5
#define TLVM_UNIMPLEMENTED      -1

#include "tlvm_alu.h"

TLVM_EXPORT tlvmReturn   tlvmInitContext     (tlvmContext** context);
TLVM_EXPORT tlvmReturn   tlvmTerminateContext(tlvmContext** context);

/* tlvmSetMemoryBuffer
 *     Sets the buffer used for the processor memory
 *   parameters:
 *     context - the CPU context
 *     memory - the buffer to use for the memory
 *     size - the width of the memory buffer
 *   return:
 *     TLVM_SUCCESS - no error
 *     TLVM_NO_CONTEXT - NULL context passed
 *     TLVM_NO_MEMORY - NULL memory buffer passed
 *     TLVM_INVALID_INPUT - zero size specified
 *
 * Note: the context will not own the memory and lifetime should
 *   be handled manually
 */
TLVM_EXPORT tlvmReturn   tlvmSetMemoryBuffer(tlvmContext* context, tlvmByte* memory, tlvmShort size);

/* tlvmLoadBootloader
 *     Loads the program into tlvm memory
 *   parameters:
 *     context: the CPU context
 *     bootloader: buffer containing the compiled tlvm program
 *   return:
 *     TLVM_SUCCESS - no error
 *     TLVM_NO_CONTEXT - NULL context passed
 *     TLVM_INVALID_INPUT - NULL program passed
 *
 * Note: tlvmLoadProgram will copy the booloader program into application memory,
 *   so the original program can be safely destroyed.
 */
TLVM_EXPORT tlvmReturn   tlvmLoadBootloader   (tlvmContext* context, tlvmByte* bootloader);

TLVM_EXPORT tlvmReturn   tlvmStep             (tlvmContext* context, tlvmByte* cycles);

TLVM_EXPORT tlvmReturn   tlvmRun              (tlvmContext* context);

TLVM_EXPORT const char*  tlvmError();

#ifdef __cplusplus
}
#endif/*__cplusplus*/
#endif/*__TLVM_H__*/
