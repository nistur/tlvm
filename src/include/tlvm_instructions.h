#pragma once
#ifndef __TLVM_INSTRUCTIONS_H__
#define __TLVM_INSTRUCTIONS_H__

/*********************************************
 * Core instruction opcodes
 *********************************************/
#define TLVM_NOOP         0x00

/*********************************************
 * ALU instruction opcodes
 *********************************************/
 #define TLVM_ADD_RM      0x40 // add from register to memory
 #define TLVM_ADD_MR      0x41 // add from memory to register

/*********************************************
 * FPU instruction opcodes
 *********************************************/
 #define TLVM_ADDF_RM     0xA0 // add from register to memory
 #define TLVM_ADDF_MR     0xA1 // add from memory to register


/*********************************************
 * Core instructions
 *********************************************/
tlvmReturn tlvmNOOP(tlvmContext* context);

/*********************************************
 * ALU instructions
 *********************************************/
 tlvmReturn tlvmADD(tlvmContext* context);

/*********************************************
 * FPU instructions
 *********************************************/
 tlvmReturn tlvmADDF(tlvmContext* context);

#endif/*__TLVM_INSTRUCTIONS_H__*/