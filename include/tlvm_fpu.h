#ifndef __TLVM_FPU_H__
#define __TLVM_FPU_H__

#ifndef __TLVM_H__
#error Do not #include tlvm_fpu.h manually, please use tlvm.h
#endif

/* tlvmAddFPU
 *     Add 16 bit floating point support to the CPU context
 *   in s10e5 format
 * parameters:
 *     context - the CPU context to add FPU support to
 */
TLVM_EXPORT tlvmReturn  tlvmAddFPU    (tlvmContext* context);

#endif/*__TLVM_FPU_H__*/