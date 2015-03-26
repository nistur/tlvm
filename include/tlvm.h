/*
Copyright (c) 2015 Philipp Geyer

This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not
   claim that you wrote the original software. If you use this software
   in a product, an acknowledgement in the product documentation would be
   appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be
   misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.

Philipp Geyer
nistur@gmail.com
*/

/*********************************************
 * TINY LITTLE VIRTUAL MACHINE
 *
 * tlvm.h
 *
 * Public header.
 * No other file should be #included other
 * than this.
 *
 * Example:
 *********************************************
 * tlvmContext* vm = NULL;
 * if(tlvmInitContext(&vm) != TLVM_SUCCESS)
 * {
 *    printf("TLVM Error: %s\n", tlvmError());
 *    return();	
 * }
 * if(tlvm8080Init(vm) != TLVM_SUCCESS)
 * {
 *    printf("TLVM Error: %s\n", tlvmError());
 *    return();	
 * }
 * if(tlvmSetClockspeed(vm, TLVM_MHZ(2,5)) != TLVM_SUCCESS)
 * {
 *    printf("TLVM Error: %s\n", tlvmError());
 *    return();	
 * }
 * tlvmByte mem[256];
 * // -- the processor will probably start
 * // -- trying to run from address 0x0000
 * // -- so this is where you might want to
 * // -- populate a bootloader
 * if(tlvmSetMemory(vm, mem, 0, 256, TLVM_FLAG_READ | TLVM_FLAG_WRITE) != TLVM_SUCCESS)
 * {
 *    printf("TLVM Error: %s\n", tlvmError());
 *    return();	
 * }
 * tlvmRun(vm);
 *********************************************
 * Current supported processor instruction
 * sets:
 * Intel 8080 (95%)
 * 
 *********************************************/

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
typedef unsigned char  tlvmChar;
typedef unsigned short tlvmShort;
typedef unsigned long  tlvmLong;
typedef unsigned char  tlvmBool;

#define TLVM_FALSE 				 0
#define TLVM_TRUE 				 1

typedef struct _tlvmContext tlvmContext;

typedef void(*tlvmClockFn)(tlvmContext*, tlvmByte*);

/*********************************************
 * ERROR CODES
 *********************************************/
#define TLVM_SUCCESS             0
#define TLVM_NO_CONTEXT          1
#define TLVM_NO_MEMORY           2
#define TLVM_INVALID_INPUT       3
#define TLVM_UNKNOWN_INSTRUCTION 4
#define TLVM_EXIT                5
#define TLVM_MEMORY_OVERLAP      6
#define TLVM_UNIMPLEMENTED      -1

/*********************************************
 * MEMORY FLAGS
 *********************************************/
#define TLVM_FLAG_READ			(1<<0)
#define TLVM_FLAG_WRITE			(1<<1)

/*********************************************
 * CLOCKSPEED
 *********************************************/
#define _TLVM_MHZ(x)  (x << 10)
#define _TLVM_KHZ(x)  (x & 0x3FF)

#define TLVM_MHZ(x,y) (_TLVM_MHZ(x) | _TLVM_KHZ(y))

/*********************************************
 * PROCESSOR INSTRUCTION SETS
 *********************************************/
#define TLVM_CPU_8080          1
#define TLVM_CPU_6303          2

#include "tlvm_8080.h"
#include "tlvm_6303.h"

/*********************************************
 * TLVM DEBUGGER SUPPORT
 *
 * Note:
 *   requires TLVM_DEBUG to build with debugger
 *  support
 *********************************************/
#include "tlvm_debug.h"

/*********************************************
 * tlvmInitContext
 *     Creates a new CPU context
 *   parameters:
 *     context - the pointer to where the CPU
 *       context should be created
 *     cpuid - the type of CPU to create
 *             - TLVM_CPU_8080
 *   return:
 *     TLVM_SUCCESS - no error
 *     TLVM_NO_CONTEXT - context pointer is NULL
 *********************************************/
TLVM_EXPORT tlvmReturn   tlvmInitContext     (tlvmContext** context, tlvmByte cpuid);

/*********************************************
 * tlvmTerminateContext
 *     Cleans up the CPU after use
 *   parameters:
 *     context - the CPU context
 *   return:
 *     TLVM_SUCCESS - no error
 *     TLVM_NO_CONTEXT - NULL context passed
 *********************************************/
TLVM_EXPORT tlvmReturn   tlvmTerminateContext(tlvmContext** context);

/*********************************************
 * tlvmSetClockspeed
 *     Sets the clockspeed of the processor
 *   parameters:
 *     context - the CPU context
 *     clockspeed - the speed of the processor
 *   return:
 *     TLVM_SUCCESS - no error
 *     TLVM_NO_CONTEXT - NULL context passed
 *
 * Note: Currently not implemented.
 *   Use TLVM_MHZ(x, y) to calculate speed
 *    eg: tlvmSetClockSpeed(context, TLVM_MHZ(2,500));
 *        // sets clockspeed to 2.5MHz
 *********************************************/
TLVM_EXPORT tlvmReturn   tlvmSetClockspeed   (tlvmContext* context, 
											  tlvmShort clockspeed);

/*********************************************
 * tlvmSetMemory
 *     Sets the buffer used for the processor memory
 *   parameters:
 *     context - the CPU context
 *     memory - the buffer to use for the memory
 *     offset - the offset of the memory buffer in the processor's address space
 *     size - the width of the memory buffer
 *   return:
 *     TLVM_SUCCESS - no error
 *     TLVM_NO_CONTEXT - NULL context passed
 *     TLVM_NO_MEMORY - NULL memory buffer passed
 *     TLVM_INVALID_INPUT - zero size specified
 *     TLVM_MEMORY_OVERLAP - memory already exists at the specified addresses
 *
 * Note: the context will not own the memory and lifetime should
 *   be handled manually
 *********************************************/
TLVM_EXPORT tlvmReturn   tlvmSetMemory       (tlvmContext* context, 
									          tlvmByte* memory, 
									          tlvmShort offset, 
									          tlvmShort size,
									          tlvmByte flags);

TLVM_EXPORT tlvmReturn   tlvmUnsetMemory     (tlvmContext* context,
										      tlvmByte* memory);

TLVM_EXPORT tlvmReturn   tlvmGetPort		 (tlvmContext* context,
											  tlvmByte port,
											  tlvmByte* outport);

TLVM_EXPORT tlvmReturn   tlvmSetPort		 (tlvmContext* context,
											  tlvmByte port,
											  tlvmByte portval);

TLVM_EXPORT tlvmReturn   tlvmStep            (tlvmContext* context, 
											  tlvmByte* cycles);

TLVM_EXPORT tlvmReturn   tlvmRun             (tlvmContext* context);

TLVM_EXPORT tlvmReturn   tlvmReset			 (tlvmContext* context);

TLVM_EXPORT tlvmReturn   tlvmSetClock        (tlvmContext* context, tlvmClockFn clockFn);

TLVM_EXPORT tlvmReturn   tlvmInterrupt       (tlvmContext* context, tlvmByte interrupt);

TLVM_EXPORT tlvmReturn   tlvmHalt            (tlvmContext* context);

TLVM_EXPORT const char*  tlvmError();

#ifdef __cplusplus
}
#endif/*__cplusplus*/
#endif/*__TLVM_H__*/
