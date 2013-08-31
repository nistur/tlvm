#pragma once
#ifndef __TLVM_INSTRUCTIONS_H__
#define __TLVM_INSTRUCTIONS_H__

#define TLVM_MOV_FROM_B    0x00
#define TLVM_MOV_FROM_C    0x01
#define TLVM_MOV_FROM_D    0x02
#define TLVM_MOV_FROM_E    0x03
#define TLVM_MOV_FROM_H    0x04
#define TLVM_MOV_FROM_L    0x05
#define TLVM_MOV_FROM_M    0x06
#define TLVM_MOV_FROM_A    0x07

#define TLVM_MOV_HI        0x08

#define TLVM_MOV_TO_B      0x40
#define TLVM_MOV_TO_C      0x48
#define TLVM_MOV_TO_D      0x50
#define TLVM_MOV_TO_E      0x58
#define TLVM_MOV_TO_H      0x60
#define TLVM_MOV_TO_L      0x68
#define TLVM_MOV_TO_M      0x70
#define TLVM_MOV_TO_A      0x78

/*********************************************
 * Core instruction opcodes
 *********************************************/
#define TLVM_NOP           0x00
#define TLVM_HLT           0x76
#define TLVM_LXI_B         0x01
#define TLVM_STAX_B        0x02
#define TLVM_MVI_B         0x06
#define TLVM_LDAX_B        0x0A
#define TLVM_MVI_C         0x0E
#define TLVM_LXI_D         0x11
#define TLVM_STAX_D        0x12
#define TLVM_MVI_D         0x16
#define TLVM_LDAX_D        0x1A
#define TLVM_MVI_E         0x1E
#define TLVM_LXI_H         0x21
#define TLVM_SHLD          0x22
#define TLVM_MVI_H         0x26
#define TLVM_MVI_L         0x2E
#define TLVM_LXI_SP        0x31
#define TLVM_MVI_M         0x36
#define TLVM_LDA           0x3A
#define TLVM_MVI_A         0x3E

#define TLVM_MOV_BB        (TLVM_MOV_TO_B | TLVM_MOV_FROM_B)
#define TLVM_MOV_BC        (TLVM_MOV_TO_B | TLVM_MOV_FROM_C)
#define TLVM_MOV_BD        (TLVM_MOV_TO_B | TLVM_MOV_FROM_D)
#define TLVM_MOV_BE        (TLVM_MOV_TO_B | TLVM_MOV_FROM_E)
#define TLVM_MOV_BH        (TLVM_MOV_TO_B | TLVM_MOV_FROM_H)
#define TLVM_MOV_BL        (TLVM_MOV_TO_B | TLVM_MOV_FROM_L)
#define TLVM_MOV_BM        (TLVM_MOV_TO_B | TLVM_MOV_FROM_M)
#define TLVM_MOV_BA        (TLVM_MOV_TO_B | TLVM_MOV_FROM_A)

#define TLVM_MOV_CB        (TLVM_MOV_TO_C | TLVM_MOV_FROM_B)
#define TLVM_MOV_CC        (TLVM_MOV_TO_C | TLVM_MOV_FROM_C)
#define TLVM_MOV_CD        (TLVM_MOV_TO_C | TLVM_MOV_FROM_D)
#define TLVM_MOV_CE        (TLVM_MOV_TO_C | TLVM_MOV_FROM_E)
#define TLVM_MOV_CH        (TLVM_MOV_TO_C | TLVM_MOV_FROM_H)
#define TLVM_MOV_CL        (TLVM_MOV_TO_C | TLVM_MOV_FROM_L)
#define TLVM_MOV_CM        (TLVM_MOV_TO_C | TLVM_MOV_FROM_M)
#define TLVM_MOV_CA        (TLVM_MOV_TO_C | TLVM_MOV_FROM_A)

#define TLVM_MOV_DB        (TLVM_MOV_TO_D | TLVM_MOV_FROM_B)
#define TLVM_MOV_DC        (TLVM_MOV_TO_D | TLVM_MOV_FROM_C)
#define TLVM_MOV_DD        (TLVM_MOV_TO_D | TLVM_MOV_FROM_D)
#define TLVM_MOV_DE        (TLVM_MOV_TO_D | TLVM_MOV_FROM_E)
#define TLVM_MOV_DH        (TLVM_MOV_TO_D | TLVM_MOV_FROM_H)
#define TLVM_MOV_DL        (TLVM_MOV_TO_D | TLVM_MOV_FROM_L)
#define TLVM_MOV_DM        (TLVM_MOV_TO_D | TLVM_MOV_FROM_M)
#define TLVM_MOV_DA        (TLVM_MOV_TO_D | TLVM_MOV_FROM_A)

#define TLVM_MOV_EB        (TLVM_MOV_TO_E | TLVM_MOV_FROM_B)
#define TLVM_MOV_EC        (TLVM_MOV_TO_E | TLVM_MOV_FROM_C)
#define TLVM_MOV_ED        (TLVM_MOV_TO_E | TLVM_MOV_FROM_D)
#define TLVM_MOV_EE        (TLVM_MOV_TO_E | TLVM_MOV_FROM_E)
#define TLVM_MOV_EH        (TLVM_MOV_TO_E | TLVM_MOV_FROM_H)
#define TLVM_MOV_EL        (TLVM_MOV_TO_E | TLVM_MOV_FROM_L)
#define TLVM_MOV_EM        (TLVM_MOV_TO_E | TLVM_MOV_FROM_M)
#define TLVM_MOV_EA        (TLVM_MOV_TO_E | TLVM_MOV_FROM_A)

#define TLVM_MOV_HB        (TLVM_MOV_TO_H | TLVM_MOV_FROM_B)
#define TLVM_MOV_HC        (TLVM_MOV_TO_H | TLVM_MOV_FROM_C)
#define TLVM_MOV_HD        (TLVM_MOV_TO_H | TLVM_MOV_FROM_D)
#define TLVM_MOV_HE        (TLVM_MOV_TO_H | TLVM_MOV_FROM_E)
#define TLVM_MOV_HH        (TLVM_MOV_TO_H | TLVM_MOV_FROM_H)
#define TLVM_MOV_HL        (TLVM_MOV_TO_H | TLVM_MOV_FROM_L)
#define TLVM_MOV_HM        (TLVM_MOV_TO_H | TLVM_MOV_FROM_M)
#define TLVM_MOV_HA        (TLVM_MOV_TO_H | TLVM_MOV_FROM_A)

#define TLVM_MOV_LB        (TLVM_MOV_TO_L | TLVM_MOV_FROM_B)
#define TLVM_MOV_LC        (TLVM_MOV_TO_L | TLVM_MOV_FROM_C)
#define TLVM_MOV_LD        (TLVM_MOV_TO_L | TLVM_MOV_FROM_D)
#define TLVM_MOV_LE        (TLVM_MOV_TO_L | TLVM_MOV_FROM_E)
#define TLVM_MOV_LH        (TLVM_MOV_TO_L | TLVM_MOV_FROM_H)
#define TLVM_MOV_LL        (TLVM_MOV_TO_L | TLVM_MOV_FROM_L)
#define TLVM_MOV_LM        (TLVM_MOV_TO_L | TLVM_MOV_FROM_M)
#define TLVM_MOV_LA        (TLVM_MOV_TO_L | TLVM_MOV_FROM_A)

#define TLVM_MOV_MB        (TLVM_MOV_TO_M | TLVM_MOV_FROM_B)
#define TLVM_MOV_MC        (TLVM_MOV_TO_M | TLVM_MOV_FROM_C)
#define TLVM_MOV_MD        (TLVM_MOV_TO_M | TLVM_MOV_FROM_D)
#define TLVM_MOV_ME        (TLVM_MOV_TO_M | TLVM_MOV_FROM_E)
#define TLVM_MOV_MH        (TLVM_MOV_TO_M | TLVM_MOV_FROM_H)
#define TLVM_MOV_ML        (TLVM_MOV_TO_M | TLVM_MOV_FROM_L)
#define TLVM_MOV_MM        // doesn't exist
#define TLVM_MOV_MA        (TLVM_MOV_TO_M | TLVM_MOV_FROM_A)

#define TLVM_MOV_AB        (TLVM_MOV_TO_A | TLVM_MOV_FROM_B)
#define TLVM_MOV_AC        (TLVM_MOV_TO_A | TLVM_MOV_FROM_C)
#define TLVM_MOV_AD        (TLVM_MOV_TO_A | TLVM_MOV_FROM_D)
#define TLVM_MOV_AE        (TLVM_MOV_TO_A | TLVM_MOV_FROM_E)
#define TLVM_MOV_AH        (TLVM_MOV_TO_A | TLVM_MOV_FROM_H)
#define TLVM_MOV_AL        (TLVM_MOV_TO_A | TLVM_MOV_FROM_L)
#define TLVM_MOV_AM        (TLVM_MOV_TO_A | TLVM_MOV_FROM_M)
#define TLVM_MOV_AA        (TLVM_MOV_TO_A | TLVM_MOV_FROM_A)
 
#define TLVM_ANA_B         0xA0
#define TLVM_ANA_C         0xA1
#define TLVM_ANA_D         0xA2
#define TLVM_ANA_E         0xA3
#define TLVM_ANA_H         0xA4
#define TLVM_ANA_L         0xA5
#define TLVM_ANA_M         0xA6
#define TLVM_ANA_A         0xA7
#define TLVM_ANI           0xE6

/*********************************************
 * ALU instruction opcodes
 *********************************************/
 #define TLVM_ADD_B        0x80 // add register B to A
 #define TLVM_ADD_C        0x81 // add register C to A
 #define TLVM_ADD_D        0x82 // add register D to A
 #define TLVM_ADD_E        0x83 // add register E to A
 #define TLVM_ADD_H        0x84 // add register H to A
 #define TLVM_ADD_L        0x85 // add register L to A
 #define TLVM_ADD_M        0x86 // add (HL) to A
 #define TLVM_ADD_A        0x87 // add register A to A
 #define TLVM_SUB_B        0x90 // add register B to A
 #define TLVM_SUB_C        0x91 // add register C to A
 #define TLVM_SUB_D        0x92 // add register D to A
 #define TLVM_SUB_E        0x93 // add register E to A
 #define TLVM_SUB_H        0x94 // add register H to A
 #define TLVM_SUB_L        0x95 // add register L to A
 #define TLVM_SUB_M        0x96 // add (HL) to A
 #define TLVM_SUB_A        0x97 // add register A to A
 
 #define TLVM_ADI          0xC6 // add immediate to A

 #define TLVM_INR_B        0x04
 #define TLVM_INR_C        0x0C
 #define TLVM_INR_D        0x14
 #define TLVM_INR_E        0x1C
 #define TLVM_INR_H        0x24
 #define TLVM_INR_L        0x2C
 #define TLVM_INR_M        0x34
 #define TLVM_INR_A        0x3C


/*********************************************
 * Core instructions
 *********************************************/
tlvmReturn tlvmNOP  (tlvmContext* context);
tlvmReturn tlvmHLT  (tlvmContext* context);
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

tlvmReturn tlvmINR  (tlvmContext* context);

#endif/*__TLVM_INSTRUCTIONS_H__*/