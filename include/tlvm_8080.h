#ifndef __TLVM_8080_H__
#define __TLVM_8080_H__

#ifdef  TLVM_HAS_8080

#ifndef __TLVM_H__
#error Do not #include tlvm_8080.h manually, please use tlvm.h
#endif

typedef void(*tlvm8080IOCallback)(tlvmContext* context, tlvmByte port);

/*********************************************
 * tlvm8080Init
 *     Setup the entire 8080 CPU. This will
 * initialise all the registers and I/O ports 
 * and then setup the instruction set
 * parameters:
 *     context - the CPU context to add 8080 
 * support to
 *********************************************/
TLVM_EXPORT tlvmReturn  tlvm8080Init  (tlvmContext* context);

/*********************************************
 * tlvm8080SetIOCallback
 *     Provides a callback for when any of the
 *   8080's ports have been written to.
 * parameters:
 *     context - the CPU context to add the
 *   callback to
 *     callback - the function pointer of the
 *   callback
 *********************************************/
TLVM_EXPORT tlvmReturn  tlvm8080SetIOCallback(tlvmContext* context, tlvm8080IOCallback callback);

#endif/*TLVM_HAS_8080*/

#endif/*__TLVM_6502_H__*/