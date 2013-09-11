#ifndef __TLVM_8080_H__
#define __TLVM_8080_H__

#ifndef __TLVM_H__
#error Do not #include tlvm_alu.h manually, please use tlvm.h
#endif

/* tlvmAdd8080
 *     Add Intel 8080 instruction set to CPU
 * parameters:
 *     context - the CPU context to add ALU support to
 */
TLVM_EXPORT tlvmReturn  tlvmAdd8080    (tlvmContext* context);

#endif/*__TLVM_ALU_H__*/