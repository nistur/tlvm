#ifndef __TLVM_Z80_H__
#define __TLVM_Z80_H__

#ifdef  TLVM_HAS_Z80

#ifndef __TLVM_H__
#error Do not #include tlvm_z80.h manually, please use tlvm.h
#endif

/*********************************************
 * tlvmInit8080
 *     Setup the entire Z80 CPU. This will
 * initialise all the registers and I/O ports 
 * and then setup the instruction set
 * parameters:
 *     context - the CPU context to add Z80 
 * support to
 *********************************************/
TLVM_EXPORT tlvmReturn  tlvmInitZ80  (tlvmContext* context);

#endif/*TLVM_HAS_Z80*/

#endif/*__TLVM_ALU_H__*/