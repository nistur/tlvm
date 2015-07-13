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

#ifndef __TLVM_DEBUG_H__
#define __TLVM_DEBUG_H__

#ifdef  TLVM_DEBUG

#ifndef __TLVM_H__
#error Do not #include tlvm_debug.h manually, please use tlvm.h
#endif

#define TLVM_DEBUG_BREAKPOINT 0x00
#define TLVM_DEBUG_STEP       0x01

typedef void(*tlvmDebugCallbackFn)(tlvmContext* context, tlvmByte message, tlvmShort addr);

/*********************************************
 * tlvmDebugAddBreakpoint
 *     Add a breakpoint to the execution. If
 *  the program counter reaches this address
 *  the execution will halt and call the
 *  provided callback function. Execution
 *  will halt until tlvmDebugContinue or
 *  tlvmDebugStep is called.
 * parameters:
 *     context - the CPU context to add the 
 *  breakpoint to
 *     addr - the address to break at
 *     callback - the function to call when
 *  the breakpoint is hit
 *********************************************/
TLVM_EXPORT tlvmReturn tlvmDebugAddBreakpoint(tlvmContext* context, tlvmShort addr, tlvmDebugCallbackFn callback);

/*********************************************
 * tlvmDebugStep
 *     Mark the currently running context to
 *  step through the instructions. This will
 *  usually be called from with a breakpoint
 *  callback just before it returns.
 * parameters:
 *     context - the CPU we're stepping through
 *     callback - the function to call when
 *  the next instruction is ready
 *********************************************/
TLVM_EXPORT tlvmReturn tlvmDebugStep(tlvmContext* context, tlvmDebugCallbackFn callback);

/*********************************************
 * tlvmDebugContinue
 *     Mark the currently running context to
 *  step through the instructions. This will
 *  usually be called from with a breakpoint
 *  callback just before it returns.
 * parameters:
 *     context - the CPU we're debugging
 *********************************************/
TLVM_EXPORT tlvmReturn tlvmDebugContinue(tlvmContext* context);

TLVM_EXPORT tlvmReturn tlvmDebugGetInstruction(tlvmContext* context, tlvmChar** instuction, tlvmByte* size);

TLVM_EXPORT tlvmReturn tlvmDebugGetMemory(tlvmContext* context, tlvmShort addr, tlvmShort size, tlvmByte** dst);

TLVM_EXPORT tlvmReturn tlvmDebugGetRegister(tlvmContext* context, tlvmByte regid, tlvmByte* outval);

TLVM_EXPORT tlvmReturn tlvmDebugParseRegister(tlvmContext* context, tlvmChar* regstr, tlvmByte* outreg);

TLVM_EXPORT tlvmReturn tlvmDebugHalt(tlvmContext* context);

TLVM_EXPORT tlvmReturn tlvmSetProgramCounter(tlvmContext* context, tlvmShort addr);

#endif/*TLVM_DEBUG*/

#endif/*__TLVM_DEBUG_H__*/