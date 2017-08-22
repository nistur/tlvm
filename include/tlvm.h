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
 * if(tlvmInitContext(&vm, TLVM_CPU_8080) != TLVM_SUCCESS)
 * {
 *    printf("TLVM Error: %s\n", tlvmError());
 *    return;	
 * }
 * if(tlvmSetClockspeed(vm, TLVM_MHZ(2,5)) != TLVM_SUCCESS)
 * {
 *    printf("TLVM Error: %s\n", tlvmError());
 *    tlvmTerminateContext(&vm);
 *    return;	
 * }
 * tlvmByte mem[256];
 * // -- the processor will probably start
 * // -- trying to run from address 0x0000
 * // -- so this is where you might want to
 * // -- populate a bootloader
 * if(tlvmSetMemory(vm, mem, 0, 256, TLVM_FLAG_READ | TLVM_FLAG_WRITE) != TLVM_SUCCESS)
 * {
 *    printf("TLVM Error: %s\n", tlvmError());
 *    tlvmTerminateContext(&vm);
 *    return;	
 * }
 * tlvmRun(vm);
 * tlvmTerminateContext(&vm);
 *********************************************
 * Current supported processor instruction
 * sets:
 * Intel 8080 (99%)
 * Hitachi 6303 (10%)
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
typedef unsigned long long tlvmLong;
typedef unsigned char  tlvmBool;
typedef signed   char  tlvmSByte;

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
#define TLVM_STALL               7
#define TLVM_UNIMPLEMENTED      -1

/*********************************************
 * MEMORY FLAGS
 *********************************************/
#define TLVM_FLAG_READ			(1<<0)
#define TLVM_FLAG_WRITE			(1<<1)

/*********************************************
 * EMULATION FLAGS
 *********************************************/
#define TLVM_FLAG_HALT          (1<<2)
#define TLVM_FLAG_STALL         (1<<3)
#define TLVM_FLAG_HALT_ON_STALL (1<<4)
    
/*********************************************
 * CLOCKSPEED
 *********************************************/
#define _TLVM_MHZ(x)  (x << 10)
#define _TLVM_KHZ(x)  (x & 0x3FF)

#define TLVM_MHZ(x,y) (_TLVM_MHZ(x) | _TLVM_KHZ(y))

/*********************************************
 * PROCESSOR INSTRUCTION SETS
 *********************************************/
typedef enum _tlvmCpuId
{
    /* TLVM_CPU_NONE
     * No CPU instruction set
     */
    TLVM_CPU_NONE,

    /* TLVM_CPU_8080
     * Intel 8080 Processor
     */
    TLVM_CPU_8080,

    /* TLVM_CPU_6800
     *Motorola 6800 Processor
     */
    TLVM_CPU_6800,

    /* TLVM_CPU_6303
     * Hitachi 6303 Processor
     */
    TLVM_CPU_6303,
    
    /* TLVM_CPU_Z80
     * Zilog Z80 Processor
     */
    TLVM_CPU_Z80,
} tlvmCpuId;
    
/*********************************************
 * CALLBACK DEFINITIONS
 *********************************************/
typedef void(*tlvmIOCallback)(tlvmContext* context, tlvmByte port);

/*********************************************
 * TLVM DEBUGGER SUPPORT
 *
 * Note:
 *    This requires the library to be build
 *  with TLVM_DEBUG to compile in debug support
 *********************************************/
#include "tlvm_debug.h"

/*********************************************
 * tlvmInitContext
 *     Creates a new CPU context
 *   parameters:
 *     context - the pointer to where the CPU
 *       context should be created
 *     cpuid - the type of CPU to create
 *             - TLVM_CPU_8080 - Intel 8080
 *             - TLVM_CPU_6303 - Hitachi 6303
 *   return:
 *     TLVM_SUCCESS - no error
 *     TLVM_NO_CONTEXT - context pointer is NULL
 *********************************************/
TLVM_EXPORT tlvmReturn   tlvmInitContext     (tlvmContext** context, tlvmCpuId cpuid);

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
 * Note:
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

/*********************************************
 * tlvmUnsetMemory
 *     Removes a memory region from the processor
 *  parameters:
 *     context - the CPU context
 *     memory - the memory buffer that was set with tlvmSetMemory
 *  return:
 *     TLVM_SUCCESS - no error
 *     TLVM_NO_CONTEXT - NULL context passed
 *     TLVM_NO_MEMORY - NULL memory buffer passed or
 *                      no memory attached to CPU instance
 *     TLVM_INVALID_INPUT - Memory buffer not attached to CPU
 *********************************************/
TLVM_EXPORT tlvmReturn   tlvmUnsetMemory     (tlvmContext* context,
                                              tlvmByte* memory);

/*********************************************
 * tlvmGetPort
 *     Retrieves current value written to one of the CPU's ports
 *  parameters:
 *     context - the CPU context
 *     port - the port ID to retrieve data from
 *     outport - the value to popupate with the port data 
 *  return:
 *     TLVM_SUCCESS - no error
 *     TLVM_NO_CONTEXT - NULL context passed
 *     TLVM_INVALID_INPUT - NULL outport parameter passed
 *  note: 
 *     This will not work for CPUs with memory mapped io 
 *********************************************/    
TLVM_EXPORT tlvmReturn   tlvmGetPort         (tlvmContext* context,
                                              tlvmByte port,
                                              tlvmByte* outport);

/*********************************************
 * tlvmSetPort
 *     Writes a byte to one of the CPU's I/O ports
 *  parameters:
 *     context - the CPU context
 *     port - the port ID to retrieve data from
 *     portval - the value to write to the port 
 *  return:
 *     TLVM_SUCCESS - no error
 *     TLVM_NO_CONTEXT - NULL context passed
 *  note: 
 *     This will not work for CPUs with memory mapped io 
 *********************************************/    
TLVM_EXPORT tlvmReturn   tlvmSetPort	     (tlvmContext* context,
                                              tlvmByte port,
                                              tlvmByte portval);

/*********************************************
 * tlvmStep
 *     Steps the processor one instruction
 *  parameters:
 *     context - the CPU context
 *     cycles - (output) number of cycles taken by the instruction
 *  return:
 *     TLVM_SUCCESS - no error
 *     TLVM_NO_CONTEXT - NULL context passed
 *     TLVM_INVALID_INPUT - current executable memory address is invalid
 *     TLVM_UNKNOWN_INSTRUCTION - memory address returned opcode not
 *                                recognised by the CPU
 *     TLVM_EXIT - Program called for the CPU to halt
 *  note: 
 *     This function can return other error codes, based on the outcome
 *   of the CPU instruction 
 *********************************************/
TLVM_EXPORT tlvmReturn   tlvmStep            (tlvmContext* context, 
                                              tlvmByte* cycles);

/*********************************************
 * tlvmRun
 *     Starts the CPU running based on the clockspeed provided by
 *   tlvmSetClockspeed, or as fast as possible if the clockspeed is
 *   unset. Will not return until the CPU is forced to halt.
 *  parameters:
 *     context - the CPU context
 *  return:
 *     TLVM_SUCCESS - no error
 *     TLVM_NO_CONTEXT - NULL context passed
 *     TLVM_INVALID_INPUT - current executable memory address is invalid
 *     TLVM_UNKNOWN_INSTRUCTION - memory address returned opcode not
 *                                recognised by the CPU
 *     TLVM_EXIT - Program called for the CPU to halt
 *  note: 
 *     This function can return other error codes, based on the outcome
 *   of the CPU instruction s
 *********************************************/
TLVM_EXPORT tlvmReturn   tlvmRun             (tlvmContext* context);
    
/*********************************************
 * tlvmReset
 *     Resets the CPU to as close to a 'fresh boot' as possible.
 *  parameters:
 *     context - the CPU context to reset 
 *  return:
 *     TLVM_SUCCESS - no error
 *     TLVM_NO_CONTEXT - NULL context passed
 *  note: 
 *     This will not reset memory to the state before initial run
 *********************************************/
TLVM_EXPORT tlvmReturn   tlvmReset	     (tlvmContext* context);

/*********************************************
 * tlvmSetClock
 *     Sets a clock callback function. This will call once per CPU cycle
 *   on the provided CPU context and can be used to synchronise with a
 *   coprocessor or similar
 *  parameters:
 *     context - the CPU context
 *     clockFn - the clock callback function
 *  return:
 *     TLVM_SUCCESS - no error
 *     TLVM_NO_CONTEXT - NULL context passed
 *  note: 
 *     As tlvm executes each instruction instantaneously and then waits
 *   for the relevant time, the callback funtion will be receieved after
 *   the instruction has run. The callback will also be provided with a
 *   pointer to the amount of cycles that the CPU is currently running for
 *   so it would be possible to modify this value and either add artificial
 *   delays to CPUs, or allow them to run quicker, by modifying this. This
 *   may lead to unexpected effects occuring though.
 *********************************************/
TLVM_EXPORT tlvmReturn   tlvmSetClock        (tlvmContext* context, 
                                              tlvmClockFn clockFn);

/*********************************************
 * tlvmInterrrupt
 *     Performs a 'hardware' interrupt of the CPU
 *  parameters:
 *     context - the CPU context
 *     interrupt - the CPU interrupt routine to call
 *  return:
 *     TLVM_SUCCESS - no error
 *     TLVM_NO_CONTEXT - NULL context passed
 *  note: 
 *     The effect of this will depend on the CPU implementation
 *********************************************/
TLVM_EXPORT tlvmReturn   tlvmInterrupt       (tlvmContext* context, 
                                              tlvmByte interrupt);

/*********************************************
 * tlvmHalt
 *     Halts the CPU operation
 *  parameters:
 *     context - the CPU context
 *  return:
 *     TLVM_SUCCESS - no error
 *     TLVM_NO_CONTEXT - NULL context passed
 *  note: 
 *     This will return immediately after flagging the CPU
 *   to halt. The CPU may still be completing the instruction
 *   that is was last on.
 *********************************************/
TLVM_EXPORT tlvmReturn   tlvmHalt            (tlvmContext* context);


TLVM_EXPORT tlvmReturn   tlvmSetFlags        (tlvmContext* context, tlvmByte flags);
TLVM_EXPORT tlvmReturn   tlvmUnsetFlags      (tlvmContext* context, tlvmByte flags);
TLVM_EXPORT tlvmReturn   tlvmGetFlags        (tlvmContext* context, tlvmByte* flags);
    
/*********************************************
 * tlvmSetIOCallback
 *     Provides a callback for when any of the
 *   CPU's ports have been written to.
 * parameters:
 *     context - the CPU context to add the
 *               callback to
 *     callback - the function pointer of the
 *                callback
 *********************************************/
TLVM_EXPORT tlvmReturn  tlvmSetIOCallback    (tlvmContext* context, 
                                              tlvmIOCallback callback);

TLVM_EXPORT const char*  tlvmError();

#ifdef __cplusplus
}
#endif/*__cplusplus*/
#endif/*__TLVM_H__*/
