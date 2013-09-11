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
 
#define TLVM_ORA_B         0xB0
#define TLVM_ORA_C         0xB1
#define TLVM_ORA_D         0xB2
#define TLVM_ORA_E         0xB3
#define TLVM_ORA_H         0xB4
#define TLVM_ORA_L         0xB5
#define TLVM_ORA_M         0xB6
#define TLVM_ORA_A         0xB7
#define TLVM_ORI           0xF6
 
#define TLVM_XRA_B         0xA8
#define TLVM_XRA_C         0xA9
#define TLVM_XRA_D         0xAA
#define TLVM_XRA_E         0xAB
#define TLVM_XRA_H         0xAC
#define TLVM_XRA_L         0xAD
#define TLVM_XRA_M         0xAE
#define TLVM_XRA_A         0xAF
#define TLVM_XRI           0xEE

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
 #define TLVM_SUI          0xD6 // subtract immediate from A

 #define TLVM_INR_B        0x04
 #define TLVM_INR_C        0x0C
 #define TLVM_INR_D        0x14
 #define TLVM_INR_E        0x1C
 #define TLVM_INR_H        0x24
 #define TLVM_INR_L        0x2C
 #define TLVM_INR_M        0x34
 #define TLVM_INR_A        0x3C

 #define TLVM_INX_B		   0x03
 #define TLVM_INX_D		   0x13
 #define TLVM_INX_H		   0x23
 #define TLVM_INX_SP	   0x33

 #define TLVM_DCR_B        0x05
 #define TLVM_DCR_C        0x0D
 #define TLVM_DCR_D        0x15
 #define TLVM_DCR_E        0x1D
 #define TLVM_DCR_H        0x25
 #define TLVM_DCR_L        0x2D
 #define TLVM_DCR_M        0x35
 #define TLVM_DCR_A        0x3D

 #define TLVM_DCX_B		   0x0B
 #define TLVM_DCX_D		   0x1B
 #define TLVM_DCX_H		   0x2B
 #define TLVM_DCX_SP	   0x3B

 #define TLVM_PUSH_B       0xC5
 #define TLVM_PUSH_D       0xD5
 #define TLVM_PUSH_H       0xE5
 #define TLVM_PUSH_PSW     0xF5

 #define TLVM_POP_B        0xC1
 #define TLVM_POP_D        0xD1
 #define TLVM_POP_H        0xE1
 #define TLVM_POP_PSW      0xF1

 #define TLVM_SPHL         0xF9
 #define TLVM_XTHL         0xE3

 #define TLVM_JNZ          0xC2
 #define TLVM_JZ           0xCA
 #define TLVM_JNC          0xD2
 #define TLVM_JC           0xDA
 #define TLVM_JPO          0xE2
 #define TLVM_JPE          0xEA
 #define TLVM_JP           0xF2
 #define TLVM_JM           0xFA
 #define TLVM_JMP          0xC3

 #define TLVM_CNZ          0xC4
 #define TLVM_CZ           0xCC
 #define TLVM_CNC          0xD4
 #define TLVM_CC           0xDC
 #define TLVM_CPO          0xE4
 #define TLVM_CPE          0xEC
 #define TLVM_CP           0xF4
 #define TLVM_CM           0xFC
 #define TLVM_CALL         0xCD

 #define TLVM_RNZ          0xC0
 #define TLVM_RZ           0xC8
 #define TLVM_RNC          0xD0
 #define TLVM_RC           0xD8
 #define TLVM_RPO          0xE0
 #define TLVM_RPE          0xE8
 #define TLVM_RP           0xF0
 #define TLVM_RM           0xF8
 #define TLVM_RET          0xC9


/*********************************************
 * Core instructions
 *********************************************/
tlvmReturn tlvmNOP  (tlvmContext* context, tlvmByte* cycles);
tlvmReturn tlvmHLT  (tlvmContext* context, tlvmByte* cycles);
tlvmReturn tlvmLXI  (tlvmContext* context, tlvmByte* cycles);
tlvmReturn tlvmSTAX (tlvmContext* context, tlvmByte* cycles);
tlvmReturn tlvmMVI  (tlvmContext* context, tlvmByte* cycles);
tlvmReturn tlvmLDAX (tlvmContext* context, tlvmByte* cycles);
tlvmReturn tlvmSHLD (tlvmContext* context, tlvmByte* cycles);
tlvmReturn tlvmLDA  (tlvmContext* context, tlvmByte* cycles);
tlvmReturn tlvmMOV  (tlvmContext* context, tlvmByte* cycles);
tlvmReturn tlvmANA  (tlvmContext* context, tlvmByte* cycles);
tlvmReturn tlvmANI  (tlvmContext* context, tlvmByte* cycles);
tlvmReturn tlvmORA  (tlvmContext* context, tlvmByte* cycles);
tlvmReturn tlvmORI  (tlvmContext* context, tlvmByte* cycles);
tlvmReturn tlvmXRA  (tlvmContext* context, tlvmByte* cycles);
tlvmReturn tlvmXRI  (tlvmContext* context, tlvmByte* cycles);
tlvmReturn tlvmPUSH (tlvmContext* context, tlvmByte* cycles);
tlvmReturn tlvmPOP  (tlvmContext* context, tlvmByte* cycles);
tlvmReturn tlvmSPHL (tlvmContext* context, tlvmByte* cycles);
tlvmReturn tlvmXTHL (tlvmContext* context, tlvmByte* cycles);
tlvmReturn tlvmJMP  (tlvmContext* context, tlvmByte* cycles);
tlvmReturn tlvmCALL (tlvmContext* context, tlvmByte* cycles);
tlvmReturn tlvmRET  (tlvmContext* context, tlvmByte* cycles);

/*********************************************
 * ALU instructions
 *********************************************/
tlvmReturn tlvmADD  (tlvmContext* context, tlvmByte* cycles);
tlvmReturn tlvmADI  (tlvmContext* context, tlvmByte* cycles);

tlvmReturn tlvmSUB  (tlvmContext* context, tlvmByte* cycles);
tlvmReturn tlvmSUI  (tlvmContext* context, tlvmByte* cycles);

tlvmReturn tlvmINR  (tlvmContext* context, tlvmByte* cycles);
tlvmReturn tlvmDCR  (tlvmContext* context, tlvmByte* cycles);

tlvmReturn tlvmINX  (tlvmContext* context, tlvmByte* cycles);
tlvmReturn tlvmDCX  (tlvmContext* context, tlvmByte* cycles);

#endif/*__TLVM_INSTRUCTIONS_H__*/