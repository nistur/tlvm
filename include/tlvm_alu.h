#ifndef __TLVM_ALU_H__
#define __TLVM_ALU_H__

#ifndef __TLVM_H__
#error Do not #include tlvm_alu.h manually, please use tlvm.h
#endif

/* tlvmAddALU
 *     Add integer arithmetric functions to the CPU context
 * parameters:
 *     context - the CPU context to add ALU support to
 */
TLVM_EXPORT tlvmReturn  tlvmAddALU    (tlvmContext* context);

#endif/*__TLVM_ALU_H__*/