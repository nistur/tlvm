#ifndef __TLVM_DEBUG_H__
#define __TLVM_DEBUG_H__

#ifdef  TLVM_DEBUG

#ifndef __TLVM_H__
#error Do not #include tlvm_debug.h manually, please use tlvm.h
#endif

#define TLVM_DEBUG_BREAKPOINT 0x00

typedef void(*tlvmDebugCallbackFn)(tlvmByte message, tlvmShort addr);

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
TLVM_EXPORT tlvmReturn  tlvmDebugAddBreakpoint(tlvmContext* context, tlvmShort addr, tlvmDebugCallbackFn callback);

#endif/*TLVM_DEBUG*/

#endif/*__TLVM_DEBUG_H__*/