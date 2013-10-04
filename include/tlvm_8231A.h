#ifndef __TLVM_8231A_H__
#define __TLVM_8231A_H__

#ifndef __TLVM_H__
#error Do not #include tlvm_8231A.h manually, please use tlvm.h
#endif

/* tlvmAdd8231A
 *     Add Intel 8231A instruction set to CPU.
 *   Intel 8231A Arithmetic Processing Unit 
 *   Fixed point single and double precision (16/32 bit)
 *   Floating point single precision (32 bit)
 *   Binary data formats
 *   Add, subtract, multiply and divide
 *   Trigonometric and inverse trigonometric functions
 *   Square roots, logarithms, exponentiation
 *   Float to fixed and fixed to float conversions
 * parameters:
 *     context - the CPU context to add 8231A support to
 */
TLVM_EXPORT tlvmReturn  tlvmAdd8231A   (tlvmContext* context);

#endif/*__TLVM_8231A_H__*/
