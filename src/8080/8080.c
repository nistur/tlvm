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

tlvmReturn tlvm8080Init(tlvmContext* context)
{
    if(context == NULL)
        TLVM_RETURN_CODE(NO_CONTEXT);

    // make sure we have enough space for instructions
    if(context->m_InstructionSet)
        tlvmFree(context->m_InstructionSet);
    context->m_InstructionSet = tlvmMallocArray(tlvmInstruction, 256);

    // initialise all the 8080 registers
    if(context->m_Registers)
        tlvmFree(context->m_Registers);
    context->m_Registers = tlvmMallocArray(tlvmByte, 8);

    // create default I/O ports
    if(context->m_Ports)
        tlvmFree(context->m_Ports);
    context->m_Ports = tlvmMallocArray(tlvmByte, 255);

    if(context->m_ProcessorData)
        tlvmFree(context->m_ProcessorData);
    context->m_ProcessorData = (tlvmProcessorData*)tlvmMalloc(tlvm8080data);

    return tlvmAdd8080Instructions(context);
}
tlvmReturn tlvmAdd8080Instructions(tlvmContext* context)
{
    if(context == NULL)
        TLVM_RETURN_CODE(NO_CONTEXT);
    
    context->m_InstructionSet[TLVM_NOP]      = tlvmNOP;
    context->m_InstructionSet[TLVM_HLT]      = tlvmHLT;
      
    context->m_InstructionSet[TLVM_LXI_B]    = tlvmLXI;
    context->m_InstructionSet[TLVM_LXI_D]    = tlvmLXI;
    context->m_InstructionSet[TLVM_LXI_H]    = tlvmLXI;
    context->m_InstructionSet[TLVM_LXI_SP]   = tlvmLXI;
      
    context->m_InstructionSet[TLVM_LDAX_B]   = tlvmLDAX;
    context->m_InstructionSet[TLVM_LDAX_D]   = tlvmLDAX;
  
    context->m_InstructionSet[TLVM_STAX_B]   = tlvmSTAX;
    context->m_InstructionSet[TLVM_STAX_D]   = tlvmSTAX;
      
    context->m_InstructionSet[TLVM_MVI_B]    = tlvmMVI;
    context->m_InstructionSet[TLVM_MVI_C]    = tlvmMVI;
    context->m_InstructionSet[TLVM_MVI_D]    = tlvmMVI;
    context->m_InstructionSet[TLVM_MVI_E]    = tlvmMVI;
    context->m_InstructionSet[TLVM_MVI_H]    = tlvmMVI;
    context->m_InstructionSet[TLVM_MVI_L]    = tlvmMVI;
    context->m_InstructionSet[TLVM_MVI_M]    = tlvmMVI;
    context->m_InstructionSet[TLVM_MVI_A]    = tlvmMVI;
  
    context->m_InstructionSet[TLVM_LDA]      = tlvmLDA;
    
    context->m_InstructionSet[TLVM_MOV_BB]   = tlvmMOV;
    context->m_InstructionSet[TLVM_MOV_BC]   = tlvmMOV;
    context->m_InstructionSet[TLVM_MOV_BD]   = tlvmMOV;
    context->m_InstructionSet[TLVM_MOV_BE]   = tlvmMOV;
    context->m_InstructionSet[TLVM_MOV_BH]   = tlvmMOV;
    context->m_InstructionSet[TLVM_MOV_BL]   = tlvmMOV;
    context->m_InstructionSet[TLVM_MOV_BM]   = tlvmMOV;
    context->m_InstructionSet[TLVM_MOV_BA]   = tlvmMOV;
    
    context->m_InstructionSet[TLVM_MOV_CB]   = tlvmMOV;
    context->m_InstructionSet[TLVM_MOV_CC]   = tlvmMOV;
    context->m_InstructionSet[TLVM_MOV_CD]   = tlvmMOV;
    context->m_InstructionSet[TLVM_MOV_CE]   = tlvmMOV;
    context->m_InstructionSet[TLVM_MOV_CH]   = tlvmMOV;
    context->m_InstructionSet[TLVM_MOV_CL]   = tlvmMOV;
    context->m_InstructionSet[TLVM_MOV_CM]   = tlvmMOV;
    context->m_InstructionSet[TLVM_MOV_CA]   = tlvmMOV;
    
    context->m_InstructionSet[TLVM_MOV_DB]   = tlvmMOV;
    context->m_InstructionSet[TLVM_MOV_DC]   = tlvmMOV;
    context->m_InstructionSet[TLVM_MOV_DD]   = tlvmMOV;
    context->m_InstructionSet[TLVM_MOV_DE]   = tlvmMOV;
    context->m_InstructionSet[TLVM_MOV_DH]   = tlvmMOV;
    context->m_InstructionSet[TLVM_MOV_DL]   = tlvmMOV;
    context->m_InstructionSet[TLVM_MOV_DM]   = tlvmMOV;
    context->m_InstructionSet[TLVM_MOV_DA]   = tlvmMOV;
    
    context->m_InstructionSet[TLVM_MOV_EB]   = tlvmMOV;
    context->m_InstructionSet[TLVM_MOV_EC]   = tlvmMOV;
    context->m_InstructionSet[TLVM_MOV_ED]   = tlvmMOV;
    context->m_InstructionSet[TLVM_MOV_EE]   = tlvmMOV;
    context->m_InstructionSet[TLVM_MOV_EH]   = tlvmMOV;
    context->m_InstructionSet[TLVM_MOV_EL]   = tlvmMOV;
    context->m_InstructionSet[TLVM_MOV_EM]   = tlvmMOV;
    context->m_InstructionSet[TLVM_MOV_EA]   = tlvmMOV;
    
    context->m_InstructionSet[TLVM_MOV_HB]   = tlvmMOV;
    context->m_InstructionSet[TLVM_MOV_HC]   = tlvmMOV;
    context->m_InstructionSet[TLVM_MOV_HD]   = tlvmMOV;
    context->m_InstructionSet[TLVM_MOV_HE]   = tlvmMOV;
    context->m_InstructionSet[TLVM_MOV_HH]   = tlvmMOV;
    context->m_InstructionSet[TLVM_MOV_HL]   = tlvmMOV;
    context->m_InstructionSet[TLVM_MOV_HM]   = tlvmMOV;
    context->m_InstructionSet[TLVM_MOV_HA]   = tlvmMOV;
    
    context->m_InstructionSet[TLVM_MOV_LB]   = tlvmMOV;
    context->m_InstructionSet[TLVM_MOV_LC]   = tlvmMOV;
    context->m_InstructionSet[TLVM_MOV_LD]   = tlvmMOV;
    context->m_InstructionSet[TLVM_MOV_LE]   = tlvmMOV;
    context->m_InstructionSet[TLVM_MOV_LH]   = tlvmMOV;
    context->m_InstructionSet[TLVM_MOV_LL]   = tlvmMOV;
    context->m_InstructionSet[TLVM_MOV_LM]   = tlvmMOV;
    context->m_InstructionSet[TLVM_MOV_LA]   = tlvmMOV;
    
    context->m_InstructionSet[TLVM_MOV_MB]   = tlvmMOV;
    context->m_InstructionSet[TLVM_MOV_MC]   = tlvmMOV;
    context->m_InstructionSet[TLVM_MOV_MD]   = tlvmMOV;
    context->m_InstructionSet[TLVM_MOV_ME]   = tlvmMOV;
    context->m_InstructionSet[TLVM_MOV_MH]   = tlvmMOV;
    context->m_InstructionSet[TLVM_MOV_ML]   = tlvmMOV;
    context->m_InstructionSet[TLVM_MOV_MA]   = tlvmMOV;
    
    context->m_InstructionSet[TLVM_MOV_AB]   = tlvmMOV;
    context->m_InstructionSet[TLVM_MOV_AC]   = tlvmMOV;
    context->m_InstructionSet[TLVM_MOV_AD]   = tlvmMOV;
    context->m_InstructionSet[TLVM_MOV_AE]   = tlvmMOV;
    context->m_InstructionSet[TLVM_MOV_AH]   = tlvmMOV;
    context->m_InstructionSet[TLVM_MOV_AL]   = tlvmMOV;
    context->m_InstructionSet[TLVM_MOV_AM]   = tlvmMOV;
    context->m_InstructionSet[TLVM_MOV_AA]   = tlvmMOV;
    
    context->m_InstructionSet[TLVM_ANA_B]    = tlvmANA;
    context->m_InstructionSet[TLVM_ANA_C]    = tlvmANA;
    context->m_InstructionSet[TLVM_ANA_D]    = tlvmANA;
    context->m_InstructionSet[TLVM_ANA_E]    = tlvmANA;
    context->m_InstructionSet[TLVM_ANA_H]    = tlvmANA;
    context->m_InstructionSet[TLVM_ANA_L]    = tlvmANA;
    context->m_InstructionSet[TLVM_ANA_M]    = tlvmANA;
    context->m_InstructionSet[TLVM_ANA_A]    = tlvmANA;
    
    context->m_InstructionSet[TLVM_ANI]      = tlvmANI;
    
    context->m_InstructionSet[TLVM_ORA_B]    = tlvmORA;
    context->m_InstructionSet[TLVM_ORA_C]    = tlvmORA;
    context->m_InstructionSet[TLVM_ORA_D]    = tlvmORA;
    context->m_InstructionSet[TLVM_ORA_E]    = tlvmORA;
    context->m_InstructionSet[TLVM_ORA_H]    = tlvmORA;
    context->m_InstructionSet[TLVM_ORA_L]    = tlvmORA;
    context->m_InstructionSet[TLVM_ORA_M]    = tlvmORA;
    context->m_InstructionSet[TLVM_ORA_A]    = tlvmORA;
    
    context->m_InstructionSet[TLVM_ORI]      = tlvmORI;
    
    context->m_InstructionSet[TLVM_XRA_B]    = tlvmXRA;
    context->m_InstructionSet[TLVM_XRA_C]    = tlvmXRA;
    context->m_InstructionSet[TLVM_XRA_D]    = tlvmXRA;
    context->m_InstructionSet[TLVM_XRA_E]    = tlvmXRA;
    context->m_InstructionSet[TLVM_XRA_H]    = tlvmXRA;
    context->m_InstructionSet[TLVM_XRA_L]    = tlvmXRA;
    context->m_InstructionSet[TLVM_XRA_M]    = tlvmXRA;
    context->m_InstructionSet[TLVM_XRA_A]    = tlvmXRA;
   
    context->m_InstructionSet[TLVM_XRI]      = tlvmXRI;

    context->m_InstructionSet[TLVM_PUSH_B]   = tlvmPUSH;
    context->m_InstructionSet[TLVM_PUSH_D]   = tlvmPUSH;
    context->m_InstructionSet[TLVM_PUSH_H]   = tlvmPUSH;
    context->m_InstructionSet[TLVM_PUSH_PSW] = tlvmPUSH;

    context->m_InstructionSet[TLVM_POP_B]    = tlvmPOP;
    context->m_InstructionSet[TLVM_POP_D]    = tlvmPOP;
    context->m_InstructionSet[TLVM_POP_H]    = tlvmPOP;
    context->m_InstructionSet[TLVM_POP_PSW]  = tlvmPOP;

    context->m_InstructionSet[TLVM_SPHL]     = tlvmSPHL;
    context->m_InstructionSet[TLVM_XTHL]     = tlvmXTHL;
    context->m_InstructionSet[TLVM_XCHG]     = tlvmXCHG;
    context->m_InstructionSet[TLVM_PCHL]     = tlvmPCHL;

    context->m_InstructionSet[TLVM_JNZ]      = tlvmJMP;
    context->m_InstructionSet[TLVM_JZ]       = tlvmJMP;
    context->m_InstructionSet[TLVM_JNC]      = tlvmJMP;
    context->m_InstructionSet[TLVM_JC]       = tlvmJMP;
    context->m_InstructionSet[TLVM_JPO]      = tlvmJMP;
    context->m_InstructionSet[TLVM_JPE]      = tlvmJMP;
    context->m_InstructionSet[TLVM_JP]       = tlvmJMP;
    context->m_InstructionSet[TLVM_JM]       = tlvmJMP;
    context->m_InstructionSet[TLVM_JMP]      = tlvmJMP;

    context->m_InstructionSet[TLVM_CNZ]      = tlvmCALL;
    context->m_InstructionSet[TLVM_CZ]       = tlvmCALL;
    context->m_InstructionSet[TLVM_CNC]      = tlvmCALL;
    context->m_InstructionSet[TLVM_CC]       = tlvmCALL;
    context->m_InstructionSet[TLVM_CPO]      = tlvmCALL;
    context->m_InstructionSet[TLVM_CPE]      = tlvmCALL;
    context->m_InstructionSet[TLVM_CP]       = tlvmCALL;
    context->m_InstructionSet[TLVM_CM]       = tlvmCALL;
    context->m_InstructionSet[TLVM_CALL]     = tlvmCALL;

    context->m_InstructionSet[TLVM_RNZ]      = tlvmRET;
    context->m_InstructionSet[TLVM_RZ]       = tlvmRET;
    context->m_InstructionSet[TLVM_RNC]      = tlvmRET;
    context->m_InstructionSet[TLVM_RC]       = tlvmRET;
    context->m_InstructionSet[TLVM_RPO]      = tlvmRET;
    context->m_InstructionSet[TLVM_RPE]      = tlvmRET;
    context->m_InstructionSet[TLVM_RP]       = tlvmRET;
    context->m_InstructionSet[TLVM_RM]       = tlvmRET;
    context->m_InstructionSet[TLVM_RET]      = tlvmRET;

    context->m_InstructionSet[TLVM_ADD_B]    = tlvmADD;
    context->m_InstructionSet[TLVM_ADD_C]    = tlvmADD;
    context->m_InstructionSet[TLVM_ADD_D]    = tlvmADD;
    context->m_InstructionSet[TLVM_ADD_E]    = tlvmADD;
    context->m_InstructionSet[TLVM_ADD_H]    = tlvmADD;
    context->m_InstructionSet[TLVM_ADD_L]    = tlvmADD;
    context->m_InstructionSet[TLVM_ADD_M]    = tlvmADD;
    context->m_InstructionSet[TLVM_ADD_A]    = tlvmADD;
   
    context->m_InstructionSet[TLVM_ADC_B]    = tlvmADD;
    context->m_InstructionSet[TLVM_ADC_C]    = tlvmADD;
    context->m_InstructionSet[TLVM_ADC_D]    = tlvmADD;
    context->m_InstructionSet[TLVM_ADC_E]    = tlvmADD;
    context->m_InstructionSet[TLVM_ADC_H]    = tlvmADD;
    context->m_InstructionSet[TLVM_ADC_L]    = tlvmADD;
    context->m_InstructionSet[TLVM_ADC_M]    = tlvmADD;
    context->m_InstructionSet[TLVM_ADC_A]    = tlvmADD;
   
    context->m_InstructionSet[TLVM_SUB_B]    = tlvmSUB;
    context->m_InstructionSet[TLVM_SUB_C]    = tlvmSUB;
    context->m_InstructionSet[TLVM_SUB_D]    = tlvmSUB;
    context->m_InstructionSet[TLVM_SUB_E]    = tlvmSUB;
    context->m_InstructionSet[TLVM_SUB_H]    = tlvmSUB;
    context->m_InstructionSet[TLVM_SUB_L]    = tlvmSUB;
    context->m_InstructionSet[TLVM_SUB_M]    = tlvmSUB;
    context->m_InstructionSet[TLVM_SUB_A]    = tlvmSUB;
   
    context->m_InstructionSet[TLVM_SBB_B]    = tlvmSUB;
    context->m_InstructionSet[TLVM_SBB_C]    = tlvmSUB;
    context->m_InstructionSet[TLVM_SBB_D]    = tlvmSUB;
    context->m_InstructionSet[TLVM_SBB_E]    = tlvmSUB;
    context->m_InstructionSet[TLVM_SBB_H]    = tlvmSUB;
    context->m_InstructionSet[TLVM_SBB_L]    = tlvmSUB;
    context->m_InstructionSet[TLVM_SBB_M]    = tlvmSUB;
    context->m_InstructionSet[TLVM_SBB_A]    = tlvmSUB;
   
    context->m_InstructionSet[TLVM_CMP_B]    = tlvmCMP;
    context->m_InstructionSet[TLVM_CMP_C]    = tlvmCMP;
    context->m_InstructionSet[TLVM_CMP_D]    = tlvmCMP;
    context->m_InstructionSet[TLVM_CMP_E]    = tlvmCMP;
    context->m_InstructionSet[TLVM_CMP_H]    = tlvmCMP;
    context->m_InstructionSet[TLVM_CMP_L]    = tlvmCMP;
    context->m_InstructionSet[TLVM_CMP_M]    = tlvmCMP;
    context->m_InstructionSet[TLVM_CMP_A]    = tlvmCMP;
   
    context->m_InstructionSet[TLVM_INR_B]    = tlvmINR;
    context->m_InstructionSet[TLVM_INR_C]    = tlvmINR;
    context->m_InstructionSet[TLVM_INR_D]    = tlvmINR;
    context->m_InstructionSet[TLVM_INR_E]    = tlvmINR;
    context->m_InstructionSet[TLVM_INR_H]    = tlvmINR;
    context->m_InstructionSet[TLVM_INR_L]    = tlvmINR;
    context->m_InstructionSet[TLVM_INR_M]    = tlvmINR;
    context->m_InstructionSet[TLVM_INR_A]    = tlvmINR;
   
    context->m_InstructionSet[TLVM_INX_B]    = tlvmINX;
    context->m_InstructionSet[TLVM_INX_D]    = tlvmINX;
    context->m_InstructionSet[TLVM_INX_H]    = tlvmINX;
    context->m_InstructionSet[TLVM_INX_SP]   = tlvmINX;
   
    context->m_InstructionSet[TLVM_DCR_B]    = tlvmDCR;
    context->m_InstructionSet[TLVM_DCR_C]    = tlvmDCR;
    context->m_InstructionSet[TLVM_DCR_D]    = tlvmDCR;
    context->m_InstructionSet[TLVM_DCR_E]    = tlvmDCR;
    context->m_InstructionSet[TLVM_DCR_H]    = tlvmDCR;
    context->m_InstructionSet[TLVM_DCR_L]    = tlvmDCR;
    context->m_InstructionSet[TLVM_DCR_M]    = tlvmDCR;
    context->m_InstructionSet[TLVM_DCR_A]    = tlvmDCR;
   
    context->m_InstructionSet[TLVM_DCX_B]    = tlvmDCX;
    context->m_InstructionSet[TLVM_DCX_D]    = tlvmDCX;
    context->m_InstructionSet[TLVM_DCX_H]    = tlvmDCX;
    context->m_InstructionSet[TLVM_DCX_SP]   = tlvmDCX;
   
    context->m_InstructionSet[TLVM_ADI]      = tlvmADI;
    context->m_InstructionSet[TLVM_ACI]      = tlvmADI;
    context->m_InstructionSet[TLVM_SUI]      = tlvmSUI;
    context->m_InstructionSet[TLVM_SBI]      = tlvmSUI;
    context->m_InstructionSet[TLVM_CPI]      = tlvmCPI;
   
    context->m_InstructionSet[TLVM_DAD_B]    = tlvmDAD;
    context->m_InstructionSet[TLVM_DAD_D]    = tlvmDAD;
    context->m_InstructionSet[TLVM_DAD_H]    = tlvmDAD;
    context->m_InstructionSet[TLVM_DAD_SP]   = tlvmDAD;
   
    context->m_InstructionSet[TLVM_STA]      = tlvmSTA;
   
    context->m_InstructionSet[TLVM_OUT]      = tlvmOUT;
    context->m_InstructionSet[TLVM_IN]       = tlvmIN;

    context->m_InstructionSet[TLVM_RST_0]    = tlvmRST;
    context->m_InstructionSet[TLVM_RST_1]    = tlvmRST;
    context->m_InstructionSet[TLVM_RST_2]    = tlvmRST;
    context->m_InstructionSet[TLVM_RST_3]    = tlvmRST;
    context->m_InstructionSet[TLVM_RST_4]    = tlvmRST;
    context->m_InstructionSet[TLVM_RST_5]    = tlvmRST;
    context->m_InstructionSet[TLVM_RST_6]    = tlvmRST;
    context->m_InstructionSet[TLVM_RST_7]    = tlvmRST;

    context->m_InstructionSet[TLVM_EI]       = tlvmEI;
    context->m_InstructionSet[TLVM_DI]       = tlvmDI;

    context->m_InstructionSet[TLVM_RLC]      = tlvmROT;
    context->m_InstructionSet[TLVM_RAL]      = tlvmROT;
    context->m_InstructionSet[TLVM_RRC]      = tlvmROT;
    context->m_InstructionSet[TLVM_RAR]      = tlvmROT;

    context->m_InstructionSet[TLVM_SHLD]     = tlvmSHLD;
    context->m_InstructionSet[TLVM_LHLD]     = tlvmLHLD;

    context->m_InstructionSet[TLVM_STC]      = tlvmSTC;
    context->m_InstructionSet[TLVM_CMC]      = tlvmCMC;

    context->m_InstructionSet[TLVM_CMA]      = tlvmCMA;

    context->m_InstructionSet[TLVM_DAA]      = tlvmDAA;

    // TEMPORARY CODE JUST TO CHECK HOW MANY INSTRUCTIONS
    // ARE IMPLEMENTED
    // TODO: REMOVE
    int t = 0;
    int i = 0;
    for(i = 0; i < 256; ++i)
        if(context->m_InstructionSet[i] != NULL)
        t++;

    TLVM_RETURN_CODE(SUCCESS);
}

tlvmReturn tlvm8080SetIOCallback(tlvmContext* context, tlvm8080IOCallback callback)
{
    if(context == NULL)
        TLVM_RETURN_CODE(NO_CONTEXT);

    ((tlvm8080data*)context->m_ProcessorData)->m_IOCallback = callback;

    TLVM_RETURN_CODE(SUCCESS);
}

tlvmReturn tlvm8080GetPort(tlvmContext* context, tlvmByte port, tlvmByte* outPort)
{
    if(context == NULL)
        TLVM_RETURN_CODE(NO_CONTEXT);
    if(outPort == NULL)
        TLVM_RETURN_CODE(INVALID_INPUT);
    *outPort = context->m_Ports[port];
    TLVM_RETURN_CODE(SUCCESS);
}

tlvmReturn tlvm8080SetPort(tlvmContext* context, tlvmByte port, tlvmByte portval)
{
    if(context == NULL)
        TLVM_RETURN_CODE(NO_CONTEXT);
    context->m_Ports[port] = portval;
    TLVM_RETURN_CODE(SUCCESS);
}

tlvmReturn tlvmSTC(tlvmContext* context, tlvmByte* cycles)
{
    if(context == NULL)
        TLVM_RETURN_CODE(NO_CONTEXT);

    TLVM_FLAG_SET(C);
    
    // size of instruction - 1

    context->m_ProgramCounter += 1;
    if(cycles)
    	*cycles = 4;
    
    TLVM_RETURN_CODE(SUCCESS);
}

tlvmReturn tlvmCMC(tlvmContext* context, tlvmByte* cycles)
{
    if(context == NULL)
        TLVM_RETURN_CODE(NO_CONTEXT);

    TLVM_FLAG_SET_IF(TLVM_FLAG_ISSET(C) == 0, C);
    
    // size of instruction - 1

    context->m_ProgramCounter += 1;
    if(cycles)
    	*cycles = 4;
    
    TLVM_RETURN_CODE(SUCCESS);
}

tlvmReturn tlvmNOP(tlvmContext* context, tlvmByte* cycles)
{
    if(context == NULL)
        TLVM_RETURN_CODE(NO_CONTEXT);
    
    context->m_ProgramCounter += 1;
    if(cycles)
    	*cycles =1;
    
    TLVM_RETURN_CODE(SUCCESS);
}

tlvmReturn tlvmHLT(tlvmContext* context, tlvmByte* cycles)
{
    if(context == NULL)
        TLVM_RETURN_CODE(NO_CONTEXT);
    
    context->m_ProgramCounter += 1;
    if(cycles)
    	*cycles =1;
    
    TLVM_RETURN_CODE(EXIT);
}


tlvmReturn tlvmCMA(tlvmContext* context, tlvmByte* cycles)
{
    if(context == NULL)
        TLVM_RETURN_CODE(NO_CONTEXT);
    
    TLVM_REGISTER_COMPLEMENT(TLVM_REG_A);

    context->m_ProgramCounter += 1;
    if(cycles)
    	*cycles = 4;
    
    TLVM_RETURN_CODE(SUCCESS);
}

tlvmReturn tlvmLXI(tlvmContext* context, tlvmByte* cycles)
{
    if(context == NULL)
        TLVM_RETURN_CODE(NO_CONTEXT);
    
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
    if(context == NULL)
        TLVM_RETURN_CODE(NO_CONTEXT);
    
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
    if(dst == NULL)
    	TLVM_RETURN_CODE(INVALID_INPUT);
    *dst = context->m_Registers[TLVM_REG_A];
    
    // size of instruction    = 1
    context->m_ProgramCounter += 1;
    if(cycles)
    	*cycles =1;
    
    TLVM_RETURN_CODE(SUCCESS);
}

tlvmReturn tlvmSHLD(tlvmContext* context, tlvmByte* cycles)
{
	if(context == NULL)
		TLVM_RETURN_CODE(NO_CONTEXT);


	TLVM_GET_OP(opLow, 1);
	TLVM_GET_OP(opHigh, 2);

    tlvmShort addr = (tlvmShort)opHigh << 8 | (tlvmShort)opLow;
    tlvmByte* dstLo = tlvmGetMemory(context, addr+0, TLVM_FLAG_WRITE);
    tlvmByte* dstHi = tlvmGetMemory(context, addr+1, TLVM_FLAG_WRITE);
    if(dstLo == NULL || dstHi == NULL)
    	TLVM_RETURN_CODE(INVALID_INPUT);
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
    if(context == NULL)
        TLVM_RETURN_CODE(NO_CONTEXT);
    
    
    TLVM_GET_OP(opLow, 1);
    TLVM_GET_OP(opHigh, 2);
    
    tlvmShort addr = (tlvmShort)opHigh << 8 | (tlvmShort)opLow;
    tlvmByte* dstLo = tlvmGetMemory(context, addr+0, TLVM_FLAG_WRITE);
    tlvmByte* dstHi = tlvmGetMemory(context, addr+1, TLVM_FLAG_WRITE);
    if(dstLo == NULL || dstHi == NULL)
    	TLVM_RETURN_CODE(INVALID_INPUT);
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
	if(context == NULL)
		TLVM_RETURN_CODE(NO_CONTEXT);

	TLVM_GET_OP(opLow, 1);
	TLVM_GET_OP(opHigh, 2);

    tlvmShort addr = (tlvmShort)opHigh << 8 | (tlvmShort)opLow;

    tlvmByte* src = tlvmGetMemory(context, addr, TLVM_FLAG_READ);
    if(src == NULL)
    	TLVM_RETURN_CODE(INVALID_INPUT);
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
	if(context == NULL)
		TLVM_RETURN_CODE(NO_CONTEXT);

	TLVM_GET_OP(opLow, 1);
	TLVM_GET_OP(opHigh, 2);

    tlvmShort addr = (tlvmShort)opHigh << 8 | (tlvmShort)opLow;

    tlvmByte* dst = tlvmGetMemory(context, addr, TLVM_FLAG_READ);
    if(dst == NULL)
    	TLVM_RETURN_CODE(INVALID_INPUT);
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
	if(context == NULL)
		TLVM_RETURN_CODE(NO_CONTEXT);

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
	if(src == NULL)
		TLVM_RETURN_CODE(INVALID_INPUT);

	context->m_Registers[TLVM_REG_A] = *src;

	// size of instruction    = 1
	context->m_ProgramCounter += 1;
    if(cycles)
    	*cycles =1;

	TLVM_RETURN_CODE(SUCCESS);
}

tlvmReturn tlvmANA(tlvmContext* context, tlvmByte* cycles)
{
	if(context == NULL)
		TLVM_RETURN_CODE(NO_CONTEXT);

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

	if(src == NULL)
		TLVM_RETURN_CODE(INVALID_INPUT);

	context->m_Registers[TLVM_REG_A] &= *src;

	// size of instruction    = 1
	context->m_ProgramCounter += 1;
    if(cycles)
    	*cycles =1;

	TLVM_RETURN_CODE(SUCCESS);
}

tlvmReturn tlvmANI(tlvmContext* context, tlvmByte* cycles)
{
	if(context == NULL)
		TLVM_RETURN_CODE(NO_CONTEXT);

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
	if(context == NULL)
		TLVM_RETURN_CODE(NO_CONTEXT);

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

	if(src == NULL)
		TLVM_RETURN_CODE(INVALID_INPUT);

	context->m_Registers[TLVM_REG_A] |= *src;

	// size of instruction    = 1
	context->m_ProgramCounter += 1;
    if(cycles)
    	*cycles =1;

	TLVM_RETURN_CODE(SUCCESS);
}

tlvmReturn tlvmORI(tlvmContext* context, tlvmByte* cycles)
{
	if(context == NULL)
		TLVM_RETURN_CODE(NO_CONTEXT);

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
	if(context == NULL)
		TLVM_RETURN_CODE(NO_CONTEXT);

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

	if(src == NULL)
		TLVM_RETURN_CODE(INVALID_INPUT);

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
	if(context == NULL)
		TLVM_RETURN_CODE(NO_CONTEXT);

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
    if(context == NULL)
        TLVM_RETURN_CODE(NO_CONTEXT);

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
    if(context == NULL)
        TLVM_RETURN_CODE(NO_CONTEXT);

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
    if(context == NULL)
        TLVM_RETURN_CODE(NO_CONTEXT);

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
    if(context == NULL)
        TLVM_RETURN_CODE(NO_CONTEXT);

    context->m_ProgramCounter = TLVM_GET_16BIT(TLVM_REG_H, TLVM_REG_L);

    // size of instruction    = 1
    //context->m_ProgramCounter += 1;
    if(cycles)
        *cycles =5;

    TLVM_RETURN_CODE(SUCCESS);

}

tlvmReturn tlvmDAA(tlvmContext* context, tlvmByte* cycles)
{
    if(context == NULL)
        TLVM_RETURN_CODE(NO_CONTEXT);

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
