#ifndef __TLVM_8080_H__
#define __TLVM_8080_H__

#ifdef  TLVM_HAS_8080

#ifndef __TLVM_H__
#error Do not #include tlvm_8080.h manually, please use tlvm.h
#endif

typedef void(*tlvm8080IOCallback)(tlvmContext* context, tlvmByte port);

/*********************************************
 * tlvmInit8080
 *     Setup the entire 8080 CPU. This will
 * initialise all the registers and I/O ports 
 * and then setup the instruction set
 * parameters:
 *     context - the CPU context to add 8080 
 * support to
 *********************************************/
TLVM_EXPORT tlvmReturn  tlvmInit8080  (tlvmContext* context);

TLVM_EXPORT tlvmReturn  tlvm8080SetIOCallback(tlvmContext* context, tlvm8080IOCallback callback);

#endif/*TLVM_HAS_8080*/

#endif/*__TLVM_ALU_H__*/