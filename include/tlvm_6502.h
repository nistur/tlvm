#ifndef __TLVM_6502_H__
#define __TLVM_6502_H__

#ifdef  TLVM_HAS_6502

#ifndef __TLVM_H__
#error Do not #include tlvm_6502.h manually, please use tlvm.h
#endif

/*********************************************
 * tlvm8080Init
 *     Setup the entire 6502 CPU. This will
 * initialise all the registers and I/O ports 
 * and then setup the instruction set
 * parameters:
 *     context - the CPU context to add 6502 
 * support to
 *********************************************/
TLVM_EXPORT tlvmReturn  tlvm6502Init  (tlvmContext* context);

#endif/*TLVM_HAS_6502*/

#endif/*__TLVM_6502_H__*/