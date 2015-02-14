/*
Copyright (c) 2015 Philipp Geyer

This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not
   claim that you wrote the original software. If you use this software
   in a product, an acknowledgement in the product documentation would be
   appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be
   misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.

Philipp Geyer
nistur@gmail.com
*/

#ifdef  TLVM_HAS_8080
#include "tlvm_internal.h"

tlvm8080data g_8080Data;

tlvmReturn tlvm8080Init(tlvmContext* context)
{
    TLVM_NULL_CHECK(context, NO_CONTEXT);

    if(g_8080Data.m_Header.m_ProcessorID == 0)
        tlvm8080SetupData();

    context->m_ProcessorData = &g_8080Data.m_Header;
    context->m_InstructionSet = g_8080Data.m_InstructionSet;

    // initialise all the 8080 registers
    if(context->m_Registers)
        tlvmFree(context->m_Registers);
    context->m_Registers = tlvmMallocArray(tlvmByte, 8);

    // create default I/O ports
    if(context->m_Ports)
        tlvmFree(context->m_Ports);
    context->m_Ports = tlvmMallocArray(tlvmByte, 255);

    TLVM_RETURN_CODE(SUCCESS);
}

void tlvm8080SetupData()
{
    g_8080Data.m_Header.m_ProcessorID = TLVM_CPU_8080;

    g_8080Data.m_InstructionSet[TLVM_NOP]      = tlvmNOP;
    g_8080Data.m_InstructionSet[TLVM_HLT]      = tlvmHLT;
      
    g_8080Data.m_InstructionSet[TLVM_LXI_B]    = tlvmLXI;
    g_8080Data.m_InstructionSet[TLVM_LXI_D]    = tlvmLXI;
    g_8080Data.m_InstructionSet[TLVM_LXI_H]    = tlvmLXI;
    g_8080Data.m_InstructionSet[TLVM_LXI_SP]   = tlvmLXI;
      
    g_8080Data.m_InstructionSet[TLVM_LDAX_B]   = tlvmLDAX;
    g_8080Data.m_InstructionSet[TLVM_LDAX_D]   = tlvmLDAX;
  
    g_8080Data.m_InstructionSet[TLVM_STAX_B]   = tlvmSTAX;
    g_8080Data.m_InstructionSet[TLVM_STAX_D]   = tlvmSTAX;
      
    g_8080Data.m_InstructionSet[TLVM_MVI_B]    = tlvmMVI;
    g_8080Data.m_InstructionSet[TLVM_MVI_C]    = tlvmMVI;
    g_8080Data.m_InstructionSet[TLVM_MVI_D]    = tlvmMVI;
    g_8080Data.m_InstructionSet[TLVM_MVI_E]    = tlvmMVI;
    g_8080Data.m_InstructionSet[TLVM_MVI_H]    = tlvmMVI;
    g_8080Data.m_InstructionSet[TLVM_MVI_L]    = tlvmMVI;
    g_8080Data.m_InstructionSet[TLVM_MVI_M]    = tlvmMVI;
    g_8080Data.m_InstructionSet[TLVM_MVI_A]    = tlvmMVI;
  
    g_8080Data.m_InstructionSet[TLVM_LDA]      = tlvmLDA;
    
    g_8080Data.m_InstructionSet[TLVM_MOV_BB]   = tlvmMOV;
    g_8080Data.m_InstructionSet[TLVM_MOV_BC]   = tlvmMOV;
    g_8080Data.m_InstructionSet[TLVM_MOV_BD]   = tlvmMOV;
    g_8080Data.m_InstructionSet[TLVM_MOV_BE]   = tlvmMOV;
    g_8080Data.m_InstructionSet[TLVM_MOV_BH]   = tlvmMOV;
    g_8080Data.m_InstructionSet[TLVM_MOV_BL]   = tlvmMOV;
    g_8080Data.m_InstructionSet[TLVM_MOV_BM]   = tlvmMOV;
    g_8080Data.m_InstructionSet[TLVM_MOV_BA]   = tlvmMOV;
    
    g_8080Data.m_InstructionSet[TLVM_MOV_CB]   = tlvmMOV;
    g_8080Data.m_InstructionSet[TLVM_MOV_CC]   = tlvmMOV;
    g_8080Data.m_InstructionSet[TLVM_MOV_CD]   = tlvmMOV;
    g_8080Data.m_InstructionSet[TLVM_MOV_CE]   = tlvmMOV;
    g_8080Data.m_InstructionSet[TLVM_MOV_CH]   = tlvmMOV;
    g_8080Data.m_InstructionSet[TLVM_MOV_CL]   = tlvmMOV;
    g_8080Data.m_InstructionSet[TLVM_MOV_CM]   = tlvmMOV;
    g_8080Data.m_InstructionSet[TLVM_MOV_CA]   = tlvmMOV;
    
    g_8080Data.m_InstructionSet[TLVM_MOV_DB]   = tlvmMOV;
    g_8080Data.m_InstructionSet[TLVM_MOV_DC]   = tlvmMOV;
    g_8080Data.m_InstructionSet[TLVM_MOV_DD]   = tlvmMOV;
    g_8080Data.m_InstructionSet[TLVM_MOV_DE]   = tlvmMOV;
    g_8080Data.m_InstructionSet[TLVM_MOV_DH]   = tlvmMOV;
    g_8080Data.m_InstructionSet[TLVM_MOV_DL]   = tlvmMOV;
    g_8080Data.m_InstructionSet[TLVM_MOV_DM]   = tlvmMOV;
    g_8080Data.m_InstructionSet[TLVM_MOV_DA]   = tlvmMOV;
    
    g_8080Data.m_InstructionSet[TLVM_MOV_EB]   = tlvmMOV;
    g_8080Data.m_InstructionSet[TLVM_MOV_EC]   = tlvmMOV;
    g_8080Data.m_InstructionSet[TLVM_MOV_ED]   = tlvmMOV;
    g_8080Data.m_InstructionSet[TLVM_MOV_EE]   = tlvmMOV;
    g_8080Data.m_InstructionSet[TLVM_MOV_EH]   = tlvmMOV;
    g_8080Data.m_InstructionSet[TLVM_MOV_EL]   = tlvmMOV;
    g_8080Data.m_InstructionSet[TLVM_MOV_EM]   = tlvmMOV;
    g_8080Data.m_InstructionSet[TLVM_MOV_EA]   = tlvmMOV;
    
    g_8080Data.m_InstructionSet[TLVM_MOV_HB]   = tlvmMOV;
    g_8080Data.m_InstructionSet[TLVM_MOV_HC]   = tlvmMOV;
    g_8080Data.m_InstructionSet[TLVM_MOV_HD]   = tlvmMOV;
    g_8080Data.m_InstructionSet[TLVM_MOV_HE]   = tlvmMOV;
    g_8080Data.m_InstructionSet[TLVM_MOV_HH]   = tlvmMOV;
    g_8080Data.m_InstructionSet[TLVM_MOV_HL]   = tlvmMOV;
    g_8080Data.m_InstructionSet[TLVM_MOV_HM]   = tlvmMOV;
    g_8080Data.m_InstructionSet[TLVM_MOV_HA]   = tlvmMOV;
    
    g_8080Data.m_InstructionSet[TLVM_MOV_LB]   = tlvmMOV;
    g_8080Data.m_InstructionSet[TLVM_MOV_LC]   = tlvmMOV;
    g_8080Data.m_InstructionSet[TLVM_MOV_LD]   = tlvmMOV;
    g_8080Data.m_InstructionSet[TLVM_MOV_LE]   = tlvmMOV;
    g_8080Data.m_InstructionSet[TLVM_MOV_LH]   = tlvmMOV;
    g_8080Data.m_InstructionSet[TLVM_MOV_LL]   = tlvmMOV;
    g_8080Data.m_InstructionSet[TLVM_MOV_LM]   = tlvmMOV;
    g_8080Data.m_InstructionSet[TLVM_MOV_LA]   = tlvmMOV;
    
    g_8080Data.m_InstructionSet[TLVM_MOV_MB]   = tlvmMOV;
    g_8080Data.m_InstructionSet[TLVM_MOV_MC]   = tlvmMOV;
    g_8080Data.m_InstructionSet[TLVM_MOV_MD]   = tlvmMOV;
    g_8080Data.m_InstructionSet[TLVM_MOV_ME]   = tlvmMOV;
    g_8080Data.m_InstructionSet[TLVM_MOV_MH]   = tlvmMOV;
    g_8080Data.m_InstructionSet[TLVM_MOV_ML]   = tlvmMOV;
    g_8080Data.m_InstructionSet[TLVM_MOV_MA]   = tlvmMOV;
    
    g_8080Data.m_InstructionSet[TLVM_MOV_AB]   = tlvmMOV;
    g_8080Data.m_InstructionSet[TLVM_MOV_AC]   = tlvmMOV;
    g_8080Data.m_InstructionSet[TLVM_MOV_AD]   = tlvmMOV;
    g_8080Data.m_InstructionSet[TLVM_MOV_AE]   = tlvmMOV;
    g_8080Data.m_InstructionSet[TLVM_MOV_AH]   = tlvmMOV;
    g_8080Data.m_InstructionSet[TLVM_MOV_AL]   = tlvmMOV;
    g_8080Data.m_InstructionSet[TLVM_MOV_AM]   = tlvmMOV;
    g_8080Data.m_InstructionSet[TLVM_MOV_AA]   = tlvmMOV;
    
    g_8080Data.m_InstructionSet[TLVM_ANA_B]    = tlvmANA;
    g_8080Data.m_InstructionSet[TLVM_ANA_C]    = tlvmANA;
    g_8080Data.m_InstructionSet[TLVM_ANA_D]    = tlvmANA;
    g_8080Data.m_InstructionSet[TLVM_ANA_E]    = tlvmANA;
    g_8080Data.m_InstructionSet[TLVM_ANA_H]    = tlvmANA;
    g_8080Data.m_InstructionSet[TLVM_ANA_L]    = tlvmANA;
    g_8080Data.m_InstructionSet[TLVM_ANA_M]    = tlvmANA;
    g_8080Data.m_InstructionSet[TLVM_ANA_A]    = tlvmANA;
    
    g_8080Data.m_InstructionSet[TLVM_ANI]      = tlvmANI;
    
    g_8080Data.m_InstructionSet[TLVM_ORA_B]    = tlvmORA;
    g_8080Data.m_InstructionSet[TLVM_ORA_C]    = tlvmORA;
    g_8080Data.m_InstructionSet[TLVM_ORA_D]    = tlvmORA;
    g_8080Data.m_InstructionSet[TLVM_ORA_E]    = tlvmORA;
    g_8080Data.m_InstructionSet[TLVM_ORA_H]    = tlvmORA;
    g_8080Data.m_InstructionSet[TLVM_ORA_L]    = tlvmORA;
    g_8080Data.m_InstructionSet[TLVM_ORA_M]    = tlvmORA;
    g_8080Data.m_InstructionSet[TLVM_ORA_A]    = tlvmORA;
    
    g_8080Data.m_InstructionSet[TLVM_ORI]      = tlvmORI;
    
    g_8080Data.m_InstructionSet[TLVM_XRA_B]    = tlvmXRA;
    g_8080Data.m_InstructionSet[TLVM_XRA_C]    = tlvmXRA;
    g_8080Data.m_InstructionSet[TLVM_XRA_D]    = tlvmXRA;
    g_8080Data.m_InstructionSet[TLVM_XRA_E]    = tlvmXRA;
    g_8080Data.m_InstructionSet[TLVM_XRA_H]    = tlvmXRA;
    g_8080Data.m_InstructionSet[TLVM_XRA_L]    = tlvmXRA;
    g_8080Data.m_InstructionSet[TLVM_XRA_M]    = tlvmXRA;
    g_8080Data.m_InstructionSet[TLVM_XRA_A]    = tlvmXRA;
   
    g_8080Data.m_InstructionSet[TLVM_XRI]      = tlvmXRI;

    g_8080Data.m_InstructionSet[TLVM_PUSH_B]   = tlvmPUSH;
    g_8080Data.m_InstructionSet[TLVM_PUSH_D]   = tlvmPUSH;
    g_8080Data.m_InstructionSet[TLVM_PUSH_H]   = tlvmPUSH;
    g_8080Data.m_InstructionSet[TLVM_PUSH_PSW] = tlvmPUSH;

    g_8080Data.m_InstructionSet[TLVM_POP_B]    = tlvmPOP;
    g_8080Data.m_InstructionSet[TLVM_POP_D]    = tlvmPOP;
    g_8080Data.m_InstructionSet[TLVM_POP_H]    = tlvmPOP;
    g_8080Data.m_InstructionSet[TLVM_POP_PSW]  = tlvmPOP;

    g_8080Data.m_InstructionSet[TLVM_SPHL]     = tlvmSPHL;
    g_8080Data.m_InstructionSet[TLVM_XTHL]     = tlvmXTHL;
    g_8080Data.m_InstructionSet[TLVM_XCHG]     = tlvmXCHG;
    g_8080Data.m_InstructionSet[TLVM_PCHL]     = tlvmPCHL;

    g_8080Data.m_InstructionSet[TLVM_JNZ]      = tlvmJMP;
    g_8080Data.m_InstructionSet[TLVM_JZ]       = tlvmJMP;
    g_8080Data.m_InstructionSet[TLVM_JNC]      = tlvmJMP;
    g_8080Data.m_InstructionSet[TLVM_JC]       = tlvmJMP;
    g_8080Data.m_InstructionSet[TLVM_JPO]      = tlvmJMP;
    g_8080Data.m_InstructionSet[TLVM_JPE]      = tlvmJMP;
    g_8080Data.m_InstructionSet[TLVM_JP]       = tlvmJMP;
    g_8080Data.m_InstructionSet[TLVM_JM]       = tlvmJMP;
    g_8080Data.m_InstructionSet[TLVM_JMP]      = tlvmJMP;

    g_8080Data.m_InstructionSet[TLVM_CNZ]      = tlvmCALL;
    g_8080Data.m_InstructionSet[TLVM_CZ]       = tlvmCALL;
    g_8080Data.m_InstructionSet[TLVM_CNC]      = tlvmCALL;
    g_8080Data.m_InstructionSet[TLVM_CC]       = tlvmCALL;
    g_8080Data.m_InstructionSet[TLVM_CPO]      = tlvmCALL;
    g_8080Data.m_InstructionSet[TLVM_CPE]      = tlvmCALL;
    g_8080Data.m_InstructionSet[TLVM_CP]       = tlvmCALL;
    g_8080Data.m_InstructionSet[TLVM_CM]       = tlvmCALL;
    g_8080Data.m_InstructionSet[TLVM_CALL]     = tlvmCALL;

    g_8080Data.m_InstructionSet[TLVM_RNZ]      = tlvmRET;
    g_8080Data.m_InstructionSet[TLVM_RZ]       = tlvmRET;
    g_8080Data.m_InstructionSet[TLVM_RNC]      = tlvmRET;
    g_8080Data.m_InstructionSet[TLVM_RC]       = tlvmRET;
    g_8080Data.m_InstructionSet[TLVM_RPO]      = tlvmRET;
    g_8080Data.m_InstructionSet[TLVM_RPE]      = tlvmRET;
    g_8080Data.m_InstructionSet[TLVM_RP]       = tlvmRET;
    g_8080Data.m_InstructionSet[TLVM_RM]       = tlvmRET;
    g_8080Data.m_InstructionSet[TLVM_RET]      = tlvmRET;

    g_8080Data.m_InstructionSet[TLVM_ADD_B]    = tlvmADD;
    g_8080Data.m_InstructionSet[TLVM_ADD_C]    = tlvmADD;
    g_8080Data.m_InstructionSet[TLVM_ADD_D]    = tlvmADD;
    g_8080Data.m_InstructionSet[TLVM_ADD_E]    = tlvmADD;
    g_8080Data.m_InstructionSet[TLVM_ADD_H]    = tlvmADD;
    g_8080Data.m_InstructionSet[TLVM_ADD_L]    = tlvmADD;
    g_8080Data.m_InstructionSet[TLVM_ADD_M]    = tlvmADD;
    g_8080Data.m_InstructionSet[TLVM_ADD_A]    = tlvmADD;
   
    g_8080Data.m_InstructionSet[TLVM_ADC_B]    = tlvmADD;
    g_8080Data.m_InstructionSet[TLVM_ADC_C]    = tlvmADD;
    g_8080Data.m_InstructionSet[TLVM_ADC_D]    = tlvmADD;
    g_8080Data.m_InstructionSet[TLVM_ADC_E]    = tlvmADD;
    g_8080Data.m_InstructionSet[TLVM_ADC_H]    = tlvmADD;
    g_8080Data.m_InstructionSet[TLVM_ADC_L]    = tlvmADD;
    g_8080Data.m_InstructionSet[TLVM_ADC_M]    = tlvmADD;
    g_8080Data.m_InstructionSet[TLVM_ADC_A]    = tlvmADD;
   
    g_8080Data.m_InstructionSet[TLVM_SUB_B]    = tlvmSUB;
    g_8080Data.m_InstructionSet[TLVM_SUB_C]    = tlvmSUB;
    g_8080Data.m_InstructionSet[TLVM_SUB_D]    = tlvmSUB;
    g_8080Data.m_InstructionSet[TLVM_SUB_E]    = tlvmSUB;
    g_8080Data.m_InstructionSet[TLVM_SUB_H]    = tlvmSUB;
    g_8080Data.m_InstructionSet[TLVM_SUB_L]    = tlvmSUB;
    g_8080Data.m_InstructionSet[TLVM_SUB_M]    = tlvmSUB;
    g_8080Data.m_InstructionSet[TLVM_SUB_A]    = tlvmSUB;
   
    g_8080Data.m_InstructionSet[TLVM_SBB_B]    = tlvmSUB;
    g_8080Data.m_InstructionSet[TLVM_SBB_C]    = tlvmSUB;
    g_8080Data.m_InstructionSet[TLVM_SBB_D]    = tlvmSUB;
    g_8080Data.m_InstructionSet[TLVM_SBB_E]    = tlvmSUB;
    g_8080Data.m_InstructionSet[TLVM_SBB_H]    = tlvmSUB;
    g_8080Data.m_InstructionSet[TLVM_SBB_L]    = tlvmSUB;
    g_8080Data.m_InstructionSet[TLVM_SBB_M]    = tlvmSUB;
    g_8080Data.m_InstructionSet[TLVM_SBB_A]    = tlvmSUB;
   
    g_8080Data.m_InstructionSet[TLVM_CMP_B]    = tlvmCMP;
    g_8080Data.m_InstructionSet[TLVM_CMP_C]    = tlvmCMP;
    g_8080Data.m_InstructionSet[TLVM_CMP_D]    = tlvmCMP;
    g_8080Data.m_InstructionSet[TLVM_CMP_E]    = tlvmCMP;
    g_8080Data.m_InstructionSet[TLVM_CMP_H]    = tlvmCMP;
    g_8080Data.m_InstructionSet[TLVM_CMP_L]    = tlvmCMP;
    g_8080Data.m_InstructionSet[TLVM_CMP_M]    = tlvmCMP;
    g_8080Data.m_InstructionSet[TLVM_CMP_A]    = tlvmCMP;
   
    g_8080Data.m_InstructionSet[TLVM_INR_B]    = tlvmINR;
    g_8080Data.m_InstructionSet[TLVM_INR_C]    = tlvmINR;
    g_8080Data.m_InstructionSet[TLVM_INR_D]    = tlvmINR;
    g_8080Data.m_InstructionSet[TLVM_INR_E]    = tlvmINR;
    g_8080Data.m_InstructionSet[TLVM_INR_H]    = tlvmINR;
    g_8080Data.m_InstructionSet[TLVM_INR_L]    = tlvmINR;
    g_8080Data.m_InstructionSet[TLVM_INR_M]    = tlvmINR;
    g_8080Data.m_InstructionSet[TLVM_INR_A]    = tlvmINR;
   
    g_8080Data.m_InstructionSet[TLVM_INX_B]    = tlvmINX;
    g_8080Data.m_InstructionSet[TLVM_INX_D]    = tlvmINX;
    g_8080Data.m_InstructionSet[TLVM_INX_H]    = tlvmINX;
    g_8080Data.m_InstructionSet[TLVM_INX_SP]   = tlvmINX;
   
    g_8080Data.m_InstructionSet[TLVM_DCR_B]    = tlvmDCR;
    g_8080Data.m_InstructionSet[TLVM_DCR_C]    = tlvmDCR;
    g_8080Data.m_InstructionSet[TLVM_DCR_D]    = tlvmDCR;
    g_8080Data.m_InstructionSet[TLVM_DCR_E]    = tlvmDCR;
    g_8080Data.m_InstructionSet[TLVM_DCR_H]    = tlvmDCR;
    g_8080Data.m_InstructionSet[TLVM_DCR_L]    = tlvmDCR;
    g_8080Data.m_InstructionSet[TLVM_DCR_M]    = tlvmDCR;
    g_8080Data.m_InstructionSet[TLVM_DCR_A]    = tlvmDCR;
   
    g_8080Data.m_InstructionSet[TLVM_DCX_B]    = tlvmDCX;
    g_8080Data.m_InstructionSet[TLVM_DCX_D]    = tlvmDCX;
    g_8080Data.m_InstructionSet[TLVM_DCX_H]    = tlvmDCX;
    g_8080Data.m_InstructionSet[TLVM_DCX_SP]   = tlvmDCX;
   
    g_8080Data.m_InstructionSet[TLVM_ADI]      = tlvmADI;
    g_8080Data.m_InstructionSet[TLVM_ACI]      = tlvmADI;
    g_8080Data.m_InstructionSet[TLVM_SUI]      = tlvmSUI;
    g_8080Data.m_InstructionSet[TLVM_SBI]      = tlvmSUI;
    g_8080Data.m_InstructionSet[TLVM_CPI]      = tlvmCPI;
   
    g_8080Data.m_InstructionSet[TLVM_DAD_B]    = tlvmDAD;
    g_8080Data.m_InstructionSet[TLVM_DAD_D]    = tlvmDAD;
    g_8080Data.m_InstructionSet[TLVM_DAD_H]    = tlvmDAD;
    g_8080Data.m_InstructionSet[TLVM_DAD_SP]   = tlvmDAD;
   
    g_8080Data.m_InstructionSet[TLVM_STA]      = tlvmSTA;
   
    g_8080Data.m_InstructionSet[TLVM_OUT]      = tlvmOUT;
    g_8080Data.m_InstructionSet[TLVM_IN]       = tlvmIN;

    g_8080Data.m_InstructionSet[TLVM_RST_0]    = tlvmRST;
    g_8080Data.m_InstructionSet[TLVM_RST_1]    = tlvmRST;
    g_8080Data.m_InstructionSet[TLVM_RST_2]    = tlvmRST;
    g_8080Data.m_InstructionSet[TLVM_RST_3]    = tlvmRST;
    g_8080Data.m_InstructionSet[TLVM_RST_4]    = tlvmRST;
    g_8080Data.m_InstructionSet[TLVM_RST_5]    = tlvmRST;
    g_8080Data.m_InstructionSet[TLVM_RST_6]    = tlvmRST;
    g_8080Data.m_InstructionSet[TLVM_RST_7]    = tlvmRST;

    g_8080Data.m_InstructionSet[TLVM_EI]       = tlvmEI;
    g_8080Data.m_InstructionSet[TLVM_DI]       = tlvmDI;

    g_8080Data.m_InstructionSet[TLVM_RLC]      = tlvmROT;
    g_8080Data.m_InstructionSet[TLVM_RAL]      = tlvmROT;
    g_8080Data.m_InstructionSet[TLVM_RRC]      = tlvmROT;
    g_8080Data.m_InstructionSet[TLVM_RAR]      = tlvmROT;

    g_8080Data.m_InstructionSet[TLVM_SHLD]     = tlvmSHLD;
    g_8080Data.m_InstructionSet[TLVM_LHLD]     = tlvmLHLD;

    g_8080Data.m_InstructionSet[TLVM_STC]      = tlvmSTC;
    g_8080Data.m_InstructionSet[TLVM_CMC]      = tlvmCMC;

    g_8080Data.m_InstructionSet[TLVM_CMA]      = tlvmCMA;

    g_8080Data.m_InstructionSet[TLVM_DAA]      = tlvmDAA;
}

tlvmReturn tlvm8080SetIOCallback(tlvmContext* context, tlvm8080IOCallback callback)
{
    TLVM_NULL_CHECK(context, NO_CONTEXT);

    ((tlvm8080data*)context->m_ProcessorData)->m_IOCallback = callback;

    TLVM_RETURN_CODE(SUCCESS);
}

tlvmReturn tlvm8080GetPort(tlvmContext* context, tlvmByte port, tlvmByte* outPort)
{
    TLVM_NULL_CHECK(context, NO_CONTEXT);
    TLVM_NULL_CHECK(outPort, INVALID_INPUT);
    *outPort = context->m_Ports[port];
    TLVM_RETURN_CODE(SUCCESS);
}

tlvmReturn tlvm8080SetPort(tlvmContext* context, tlvmByte port, tlvmByte portval)
{
    TLVM_NULL_CHECK(context, NO_CONTEXT);
    context->m_Ports[port] = portval;
    TLVM_RETURN_CODE(SUCCESS);
}

tlvmReturn tlvm8080Interrupt(tlvmContext* context, tlvmByte interrupt)
{
    TLVM_NULL_CHECK(context, NO_CONTEXT);

    if(TLVM_FLAG_ISSET(I))
        tlvm8080HandleInterrupt(context, interrupt);
    else
        context->m_Registers[TLVM_REG_I] = interrupt;

    TLVM_RETURN_CODE(SUCCESS);
}

tlvmReturn tlvm8080HandleInterrupt(tlvmContext* context, tlvmByte interrupt)
{
    TLVM_NULL_CHECK(context, NO_CONTEXT);

    TLVM_PUSH_PC(interrupt << 3);

    TLVM_RETURN_CODE(SUCCESS);
}

tlvmReturn tlvmSTC(tlvmContext* context, tlvmByte* cycles)
{
    TLVM_NULL_CHECK(context, NO_CONTEXT);

    TLVM_FLAG_SET(C);
    
    // size of instruction - 1

    context->m_ProgramCounter += 1;
    if(cycles)
    	*cycles = 4;
    
    TLVM_RETURN_CODE(SUCCESS);
}

tlvmReturn tlvmCMC(tlvmContext* context, tlvmByte* cycles)
{
    TLVM_NULL_CHECK(context, NO_CONTEXT);

    TLVM_FLAG_SET_IF(TLVM_FLAG_ISSET(C) == 0, C);
    
    // size of instruction - 1

    context->m_ProgramCounter += 1;
    if(cycles)
    	*cycles = 4;
    
    TLVM_RETURN_CODE(SUCCESS);
}

tlvmReturn tlvmNOP(tlvmContext* context, tlvmByte* cycles)
{
    TLVM_NULL_CHECK(context, NO_CONTEXT);
    
    context->m_ProgramCounter += 1;
    if(cycles)
    	*cycles =1;
    
    TLVM_RETURN_CODE(SUCCESS);
}

tlvmReturn tlvmHLT(tlvmContext* context, tlvmByte* cycles)
{
    TLVM_NULL_CHECK(context, NO_CONTEXT);
    
    context->m_ProgramCounter += 1;
    if(cycles)
    	*cycles =1;
    
    TLVM_RETURN_CODE(EXIT);
}


tlvmReturn tlvmCMA(tlvmContext* context, tlvmByte* cycles)
{
    TLVM_NULL_CHECK(context, NO_CONTEXT);
    
    TLVM_REGISTER_COMPLEMENT(TLVM_REG_A);

    context->m_ProgramCounter += 1;
    if(cycles)
    	*cycles = 4;
    
    TLVM_RETURN_CODE(SUCCESS);
}

tlvmReturn tlvmLXI(tlvmContext* context, tlvmByte* cycles)
{
    TLVM_NULL_CHECK(context, NO_CONTEXT);
    
	TLVM_GET_OP(opcode, 0);
	TLVM_GET_OP(opLow,  1);
	TLVM_GET_OP(opHigh, 2);

    switch(opcode)
    {
    case TLVM_LXI_B:
        context->m_Registers[TLVM_REG_B] = opHigh;
        context->m_Registers[TLVM_REG_C] = opLow;
	break;
    case TLVM_LXI_D:
        context->m_Registers[TLVM_REG_D] = opHigh;
        context->m_Registers[TLVM_REG_E] = opLow;
	break;
    case TLVM_LXI_H:
        context->m_Registers[TLVM_REG_H] = opHigh;
        context->m_Registers[TLVM_REG_L] = opLow;
	break;
    case TLVM_LXI_SP:
        context->m_StackPointer = (tlvmShort)opHigh << 8 | (tlvmShort)opLow;
	break;
    }
    
    // size of instruction    = 1
    // size of operand        = 2
    context->m_ProgramCounter += 3;
    if(cycles)
    	*cycles =3;
    
    TLVM_RETURN_CODE(SUCCESS);
}

tlvmReturn tlvmSTAX(tlvmContext* context, tlvmByte* cycles)
{
    TLVM_NULL_CHECK(context, NO_CONTEXT);
    
	TLVM_GET_OP(opcode, 0);

    tlvmShort addr = 0;
    switch(opcode)
    {
    case TLVM_STAX_B:
    	addr = TLVM_GET_16BIT(TLVM_REG_B, TLVM_REG_C);
	break;
    case TLVM_STAX_D:
    	addr = TLVM_GET_16BIT(TLVM_REG_D, TLVM_REG_E);
	break;
    }
    tlvmByte* dst = tlvmGetMemory(context, addr, TLVM_FLAG_WRITE);
    TLVM_NULL_CHECK(dst, INVALID_INPUT);
    *dst = context->m_Registers[TLVM_REG_A];
    
    // size of instruction    = 1
    context->m_ProgramCounter += 1;
    if(cycles)
    	*cycles =1;
    
    TLVM_RETURN_CODE(SUCCESS);
}

tlvmReturn tlvmSHLD(tlvmContext* context, tlvmByte* cycles)
{
    TLVM_NULL_CHECK(context, NO_CONTEXT);


	TLVM_GET_OP(opLow, 1);
	TLVM_GET_OP(opHigh, 2);

    tlvmShort addr = (tlvmShort)opHigh << 8 | (tlvmShort)opLow;
    tlvmByte* dstLo = tlvmGetMemory(context, addr+0, TLVM_FLAG_WRITE);
    tlvmByte* dstHi = tlvmGetMemory(context, addr+1, TLVM_FLAG_WRITE);
    TLVM_NULL_CHECK(dstHi, INVALID_INPUT);
    TLVM_NULL_CHECK(dstLo, INVALID_INPUT);
    *dstLo = context->m_Registers[TLVM_REG_L];
    *dstHi = context->m_Registers[TLVM_REG_H];

	// size of instruction    = 1
	// size of operand        = 2
	context->m_ProgramCounter += 3;
    if(cycles)
    	*cycles = 16;

	TLVM_RETURN_CODE(SUCCESS);
}

tlvmReturn tlvmLHLD(tlvmContext* context, tlvmByte* cycles)
{
    TLVM_NULL_CHECK(context, NO_CONTEXT);
    
    
    TLVM_GET_OP(opLow, 1);
    TLVM_GET_OP(opHigh, 2);
    
    tlvmShort addr = (tlvmShort)opHigh << 8 | (tlvmShort)opLow;
    tlvmByte* dstLo = tlvmGetMemory(context, addr+0, TLVM_FLAG_WRITE);
    tlvmByte* dstHi = tlvmGetMemory(context, addr+1, TLVM_FLAG_WRITE);
    TLVM_NULL_CHECK(dstHi, INVALID_INPUT);
    TLVM_NULL_CHECK(dstLo, INVALID_INPUT);
    context->m_Registers[TLVM_REG_L] = *dstLo;
    context->m_Registers[TLVM_REG_H] = *dstHi;
    
    // size of instruction    = 1
    // size of operand        = 2
    context->m_ProgramCounter += 3;
    if(cycles)
    	*cycles = 13;
    
    TLVM_RETURN_CODE(SUCCESS);
}

tlvmReturn tlvmLDA(tlvmContext* context, tlvmByte* cycles)
{
    TLVM_NULL_CHECK(context, NO_CONTEXT);

	TLVM_GET_OP(opLow, 1);
	TLVM_GET_OP(opHigh, 2);

    tlvmShort addr = (tlvmShort)opHigh << 8 | (tlvmShort)opLow;

    tlvmByte* src = tlvmGetMemory(context, addr, TLVM_FLAG_READ);
    TLVM_NULL_CHECK(src, INVALID_INPUT);
    context->m_Registers[TLVM_REG_A] = *src;

    // size of instruction    = 1
    // size of operand        = 2
    context->m_ProgramCounter += 3;
    if(cycles)
    	*cycles = 13;

	TLVM_RETURN_CODE(SUCCESS);
}

tlvmReturn tlvmSTA(tlvmContext* context, tlvmByte* cycles)
{
    TLVM_NULL_CHECK(context, NO_CONTEXT);

	TLVM_GET_OP(opLow, 1);
	TLVM_GET_OP(opHigh, 2);

    tlvmShort addr = (tlvmShort)opHigh << 8 | (tlvmShort)opLow;

    tlvmByte* dst = tlvmGetMemory(context, addr, TLVM_FLAG_READ);
    TLVM_NULL_CHECK(dst, INVALID_INPUT);
    *dst = context->m_Registers[TLVM_REG_A];

    // size of instruction    = 1
    // size of operand        = 2
    context->m_ProgramCounter += 3;
    if(cycles)
    	*cycles = 13;

	TLVM_RETURN_CODE(SUCCESS);
}

tlvmReturn tlvmLDAX(tlvmContext* context, tlvmByte* cycles)
{
    TLVM_NULL_CHECK(context, NO_CONTEXT);

	TLVM_GET_OP(opcode, 0);
	tlvmShort addr = 0;
	switch(opcode)
	{
	case TLVM_LDAX_B:
		addr = TLVM_GET_16BIT(TLVM_REG_B, TLVM_REG_C);
	break;
	case TLVM_LDAX_D:
		addr = TLVM_GET_16BIT(TLVM_REG_D, TLVM_REG_E);
	break;
	default:
		TLVM_RETURN_CODE(INVALID_INPUT);
	}

	tlvmByte* src = tlvmGetMemory(context, addr, TLVM_FLAG_READ);
    TLVM_NULL_CHECK(src, INVALID_INPUT);

	context->m_Registers[TLVM_REG_A] = *src;

	// size of instruction    = 1
	context->m_ProgramCounter += 1;
    if(cycles)
    	*cycles =1;

	TLVM_RETURN_CODE(SUCCESS);
}

tlvmReturn tlvmANA(tlvmContext* context, tlvmByte* cycles)
{
    TLVM_NULL_CHECK(context, NO_CONTEXT);

	TLVM_GET_OP(opcode, 0);

	tlvmByte* src = NULL;

	switch(opcode)
	{
	case TLVM_ANA_B:
		src = &context->m_Registers[TLVM_REG_B];
	break;
	case TLVM_ANA_C:
		src = &context->m_Registers[TLVM_REG_C];
	break;
	case TLVM_ANA_D:
		src = &context->m_Registers[TLVM_REG_D];
	break;
	case TLVM_ANA_E:
		src = &context->m_Registers[TLVM_REG_E];
	break;
	case TLVM_ANA_H:
		src = &context->m_Registers[TLVM_REG_H];
	break;
	case TLVM_ANA_L:
		src = &context->m_Registers[TLVM_REG_L];
	break;
	case TLVM_ANA_M:
		{
			tlvmShort addr = TLVM_GET_16BIT(TLVM_REG_H, TLVM_REG_L);
			src = tlvmGetMemory(context, addr, TLVM_FLAG_READ);
		}
	break;
	case TLVM_ANA_A:
		src = &context->m_Registers[TLVM_REG_A];
	break;
	}

    TLVM_NULL_CHECK(src, INVALID_INPUT);

	context->m_Registers[TLVM_REG_A] &= *src;

	// size of instruction    = 1
	context->m_ProgramCounter += 1;
    if(cycles)
    	*cycles =1;

	TLVM_RETURN_CODE(SUCCESS);
}

tlvmReturn tlvmANI(tlvmContext* context, tlvmByte* cycles)
{
    TLVM_NULL_CHECK(context, NO_CONTEXT);

	TLVM_GET_OP(operand, 1);

	context->m_Registers[TLVM_REG_A] &= operand;
    TLVM_SET_FLAGS(context->m_Registers[TLVM_REG_A]);

	// size of instruction    = 1
	// size of operand        = 1
	context->m_ProgramCounter += 2;
    if(cycles)
    	*cycles =2;

	TLVM_RETURN_CODE(SUCCESS);
}

tlvmReturn tlvmORA(tlvmContext* context, tlvmByte* cycles)
{
    TLVM_NULL_CHECK(context, NO_CONTEXT);

	TLVM_GET_OP(opcode, 0);

	tlvmByte* src = NULL;

	switch(opcode)
	{
	case TLVM_ORA_B:
		src = &context->m_Registers[TLVM_REG_B];
	break;
	case TLVM_ORA_C:
		src = &context->m_Registers[TLVM_REG_C];
	break;
	case TLVM_ORA_D:
		src = &context->m_Registers[TLVM_REG_D];
	break;
	case TLVM_ORA_E:
		src = &context->m_Registers[TLVM_REG_E];
	break;
	case TLVM_ORA_H:
		src = &context->m_Registers[TLVM_REG_H];
	break;
	case TLVM_ORA_L:
		src = &context->m_Registers[TLVM_REG_L];
	break;
	case TLVM_ORA_M:
		{
			tlvmShort addr = TLVM_GET_16BIT(TLVM_REG_H, TLVM_REG_L);
			src = tlvmGetMemory(context, addr, TLVM_FLAG_READ);
		}
	break;
	case TLVM_ORA_A:
		src = &context->m_Registers[TLVM_REG_A];
	break;
	}

    TLVM_NULL_CHECK(src, INVALID_INPUT);

	context->m_Registers[TLVM_REG_A] |= *src;

	// size of instruction    = 1
	context->m_ProgramCounter += 1;
    if(cycles)
    	*cycles =1;

	TLVM_RETURN_CODE(SUCCESS);
}

tlvmReturn tlvmORI(tlvmContext* context, tlvmByte* cycles)
{
    TLVM_NULL_CHECK(context, NO_CONTEXT);

	TLVM_GET_OP(operand, 1);

	context->m_Registers[TLVM_REG_A] |= operand;

	// size of instruction    = 1
	// size of operand        = 1
	context->m_ProgramCounter += 2;
    if(cycles)
    	*cycles =2;

	TLVM_RETURN_CODE(SUCCESS);
}

tlvmReturn tlvmXRA(tlvmContext* context, tlvmByte* cycles)
{
    TLVM_NULL_CHECK(context, NO_CONTEXT);

	TLVM_GET_OP(opcode, 0);

	tlvmByte* src = NULL;

	switch(opcode)
	{
	case TLVM_XRA_B:
		src = &context->m_Registers[TLVM_REG_B];
	break;
	case TLVM_XRA_C:
		src = &context->m_Registers[TLVM_REG_C];
	break;
	case TLVM_XRA_D:
		src = &context->m_Registers[TLVM_REG_D];
	break;
	case TLVM_XRA_E:
		src = &context->m_Registers[TLVM_REG_E];
	break;
	case TLVM_XRA_H:
		src = &context->m_Registers[TLVM_REG_H];
	break;
	case TLVM_XRA_L:
		src = &context->m_Registers[TLVM_REG_L];
	break;
	case TLVM_XRA_M:
		{
			tlvmShort addr = TLVM_GET_16BIT(TLVM_REG_H, TLVM_REG_L);
			src = tlvmGetMemory(context, addr, TLVM_FLAG_READ);
		}
	break;
	case TLVM_XRA_A:
		src = &context->m_Registers[TLVM_REG_A];
	break;
	}

    TLVM_NULL_CHECK(src, INVALID_INPUT);

	context->m_Registers[TLVM_REG_A] ^= *src;
    TLVM_FLAG_UNSET(H);
    TLVM_FLAG_UNSET(C);

	// size of instruction    = 1
	context->m_ProgramCounter += 1;
    if(cycles)
    	*cycles =1;

	TLVM_RETURN_CODE(SUCCESS);
}

tlvmReturn tlvmXRI(tlvmContext* context, tlvmByte* cycles)
{
    TLVM_NULL_CHECK(context, NO_CONTEXT);

	TLVM_GET_OP(operand, 1);

	context->m_Registers[TLVM_REG_A] ^= operand;
    TLVM_FLAG_UNSET(H);
    TLVM_FLAG_UNSET(C);

	// size of instruction    = 1
	// size of operand        = 1
	context->m_ProgramCounter += 2;
    if(cycles)
    	*cycles =2;

	TLVM_RETURN_CODE(SUCCESS);
}

tlvmReturn tlvmINR(tlvmContext* context, tlvmByte* cycles)
{
    TLVM_NULL_CHECK(context, NO_CONTEXT);

    TLVM_GET_OP(opcode, 0);

    switch(opcode)
    {
    case TLVM_INR_B:
        context->m_Registers[TLVM_REG_B]++;
    break;
    case TLVM_INR_C:
        context->m_Registers[TLVM_REG_C]++;
    break;
    case TLVM_INR_D:
        context->m_Registers[TLVM_REG_D]++;
    break;
    case TLVM_INR_E:
        context->m_Registers[TLVM_REG_E]++;
    break;
    case TLVM_INR_H:
        context->m_Registers[TLVM_REG_H]++;
    break;
    case TLVM_INR_L:
        context->m_Registers[TLVM_REG_L]++;
    break;
    case TLVM_INR_M:
        {
            tlvmShort addr = TLVM_GET_16BIT(TLVM_REG_H, TLVM_REG_L);
            tlvmByte* val = tlvmGetMemory(context, addr, TLVM_FLAG_WRITE);
            if(val != NULL)
                (*val)++;
        }
    break;
    case TLVM_INR_A:
        context->m_Registers[TLVM_REG_A]++;
    break;
    }

    // size of instruction    = 1
    context->m_ProgramCounter += 1;
    if(cycles)
        *cycles = 5;

    TLVM_RETURN_CODE(SUCCESS);
}

tlvmReturn tlvmDCR(tlvmContext* context, tlvmByte* cycles)
{
    TLVM_NULL_CHECK(context, NO_CONTEXT);

    TLVM_GET_OP(opcode, 0);

    tlvmByte* val = NULL;
    switch(opcode)
    {
    case TLVM_DCR_B:
        val = &context->m_Registers[TLVM_REG_B];
    break;
    case TLVM_DCR_C:
        val = &context->m_Registers[TLVM_REG_C];
    break;
    case TLVM_DCR_D:
        val = &context->m_Registers[TLVM_REG_D];
    break;
    case TLVM_DCR_E:
        val = &context->m_Registers[TLVM_REG_E];
    break;
    case TLVM_DCR_H:
        val = &context->m_Registers[TLVM_REG_H];
    break;
    case TLVM_DCR_L:
        val = &context->m_Registers[TLVM_REG_L];
    break;
    case TLVM_DCR_M:
        val = tlvmGetMemory(context, TLVM_GET_16BIT(TLVM_REG_H, TLVM_REG_L), TLVM_FLAG_WRITE);
    break;
    case TLVM_DCR_A:
        val = &context->m_Registers[TLVM_REG_A];
    break;
    }

    if(val != NULL)
    {
        (*val)--;
        TLVM_FLAG_SET_IF((*val == 0), Z);
    }

    // size of instruction    = 1
    context->m_ProgramCounter += 1;
    if(cycles)
        *cycles = 5;

    TLVM_RETURN_CODE(SUCCESS);
}

tlvmReturn tlvmXCHG(tlvmContext* context, tlvmByte* cycles)
{
    TLVM_NULL_CHECK(context, NO_CONTEXT);

    tlvmShort tmp = TLVM_GET_16BIT(TLVM_REG_H, TLVM_REG_L);
    TLVM_SET_16BIT(TLVM_REG_H, TLVM_REG_L, TLVM_GET_16BIT(TLVM_REG_D, TLVM_REG_E));
    TLVM_SET_16BIT(TLVM_REG_D, TLVM_REG_E, tmp);
    // size of instruction    = 1
    context->m_ProgramCounter += 1;
    if(cycles)
        *cycles =5;

    TLVM_RETURN_CODE(SUCCESS);

}

tlvmReturn tlvmPCHL(tlvmContext* context, tlvmByte* cycles)
{
    TLVM_NULL_CHECK(context, NO_CONTEXT);

    context->m_ProgramCounter = TLVM_GET_16BIT(TLVM_REG_H, TLVM_REG_L);

    // size of instruction    = 1
    //context->m_ProgramCounter += 1;
    if(cycles)
        *cycles =5;

    TLVM_RETURN_CODE(SUCCESS);

}

tlvmReturn tlvmDAA(tlvmContext* context, tlvmByte* cycles)
{
    TLVM_NULL_CHECK(context, NO_CONTEXT);

    tlvmByte nibbleLo = context->m_Registers[TLVM_REG_A] & 0x0F;
    tlvmByte nibbleHi = (context->m_Registers[TLVM_REG_A] & 0xF0)>>4;

    if(nibbleLo>0x09 || TLVM_FLAG_ISSET(H))
    {
        nibbleLo += 0x06;
        TLVM_FLAG_SET_IF(nibbleLo & 0xF0, H);
        if(TLVM_FLAG_ISSET(H))
            nibbleHi += 0x01;
    }
    if(nibbleHi>0x09 || TLVM_FLAG_ISSET(C))
    {
        nibbleHi += 0x06;
    }
    context->m_Registers[TLVM_REG_A] = ((nibbleHi & 0x0F)<<4) | (nibbleLo & 0x0F);
    TLVM_SET_FLAGS(context->m_Registers[TLVM_REG_A]);
    TLVM_FLAG_SET_IF(nibbleHi & 0xF0, C);

    // size of instruction    = 1
    context->m_ProgramCounter += 1;
    if(cycles)
        *cycles = 4;

    TLVM_RETURN_CODE(SUCCESS);

}
#endif/*TLVM_HAS_8080*/
