#pragma once
#ifndef __TLVM_INSTRUCTIONS_H__
#define __TLVM_INSTRUCTIONS_H__

/*********************************************
 * Core instruction opcodes
 *********************************************/
#define TLVM_NOP          0x00
#define TLVM_LXI_B        0x01
#define TLVM_STAX_B       0x02
#define TLVM_MVI_B        0x06
#define TLVM_LDAX_B       0x0A
#define TLVM_MVI_C        0x0E
#define TLVM_LXI_D        0x11
#define TLVM_STAX_D       0x12
#define TLVM_MVI_D        0x16
#define TLVM_LDAX_D       0x1A
#define TLVM_MVI_E        0x1E
#define TLVM_LXI_H        0x21
#define TLVM_SHLD         0x22
#define TLVM_MVI_H        0x26
#define TLVM_MVI_L        0x2E
#define TLVM_LXI_SP       0x31
#define TLVM_MVI_M        0x36
#define TLVM_LDA          0x3A
#define TLVM_MVI_A        0x3E

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
 #define TLVM_ADD_D       0x82 // add register D to A
 #define TLVM_ADD_E       0x83 // add register E to A
 #define TLVM_ADD_H       0x84 // add register H to A
 #define TLVM_ADD_L       0x85 // add register L to A
 #define TLVM_ADD_M       0x86 // add (HL) to A
 #define TLVM_ADD_A       0x87 // add register A to A
 #define TLVM_SUB_B       0x90 // add register B to A
 #define TLVM_SUB_C       0x91 // add register C to A
 #define TLVM_SUB_D       0x92 // add register D to A
 #define TLVM_SUB_E       0x93 // add register E to A
 #define TLVM_SUB_H       0x94 // add register H to A
 #define TLVM_SUB_L       0x95 // add register L to A
 #define TLVM_SUB_M       0x96 // add (HL) to A
 #define TLVM_SUB_A       0x97 // add register A to A

 #define TLVM_ADI         0xC6 // add immediate to A


/*********************************************
 * Core instructions
 *********************************************/
tlvmReturn tlvmNOP  (tlvmContext* context);
tlvmReturn tlvmLXI  (tlvmContext* context);
tlvmReturn tlvmSTAX (tlvmContext* context);
tlvmReturn tlvmMVI  (tlvmContext* context);
tlvmReturn tlvmLDAX (tlvmContext* context);
tlvmReturn tlvmSHLD (tlvmContext* context);
tlvmReturn tlvmLDA  (tlvmContext* context);
tlvmReturn tlvmMOV  (tlvmContext* context);
tlvmReturn tlvmANA  (tlvmContext* context);
tlvmReturn tlvmANI  (tlvmContext* context);

/*********************************************
 * ALU instructions
 *********************************************/
tlvmReturn tlvmADD  (tlvmContext* context);
tlvmReturn tlvmADI  (tlvmContext* context);

tlvmReturn tlvmSUB  (tlvmContext* context);

#endif/*__TLVM_INSTRUCTIONS_H__*/