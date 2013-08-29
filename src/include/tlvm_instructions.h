#pragma once
#ifndef __TLVM_INSTRUCTIONS_H__
#define __TLVM_INSTRUCTIONS_H__

/*********************************************
 * Core instruction opcodes
 *********************************************/
#define TLVM_NOOP         0x00
#define TLVM_MOV_B        0x70
#define TLVM_MOV_C        0x71
#define TLVM_MOV_D        0x72
#define TLVM_MOV_E        0x73
#define TLVM_MOV_H        0x74
#define TLVM_MOV_L        0x75
#define TLVM_MOV_A        0x77

/*********************************************
 * ALU instruction opcodes
 *********************************************/
 #define TLVM_ADD_B       0x80 // add register B to A
 #define TLVM_ADD_C       0x81 // add register C to A

/*********************************************
 * FPU instruction opcodes
 *********************************************/
 #define TLVM_ADDF_RM     0xA0 // add from register to memory
 #define TLVM_ADDF_MR     0xA1 // add from memory to register


/*********************************************
 * Core instructions
 *********************************************/
tlvmReturn tlvmNOOP(tlvmContext* context);
tlvmReturn tlvmMOV (tlvmContext* context);

/*********************************************
 * ALU instructions
 *********************************************/
 tlvmReturn tlvmADD(tlvmContext* context);

#endif/*__TLVM_INSTRUCTIONS_H__*/