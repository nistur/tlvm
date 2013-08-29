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

#define TLVM_ANA_B        0xA0
#define TLVM_ANA_C        0xA1
#define TLVM_ANA_D        0xA2
#define TLVM_ANA_E        0xA3
#define TLVM_ANA_H        0xA4
#define TLVM_ANA_L        0xA5
#define TLVM_ANA_M        0xA6
#define TLVM_ANA_A        0xA7
#define TLVM_ANI          0xE6

/*********************************************
 * ALU instruction opcodes
 *********************************************/
 #define TLVM_ADD_B       0x80 // add register B to A
 #define TLVM_ADD_C       0x81 // add register C to A


/*********************************************
 * Core instructions
 *********************************************/
tlvmReturn tlvmNOOP(tlvmContext* context);
tlvmReturn tlvmMOV (tlvmContext* context);
tlvmReturn tlvmANA (tlvmContext* context);
tlvmReturn tlvmANI (tlvmContext* context);

/*********************************************
 * ALU instructions
 *********************************************/
 tlvmReturn tlvmADD(tlvmContext* context);

#endif/*__TLVM_INSTRUCTIONS_H__*/