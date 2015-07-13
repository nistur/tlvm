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

tlvmProcessorData_8080 g_8080Data;

tlvmReturn tlvm8080Init(tlvmContext** context)
{
    TLVM_NULL_CHECK(context, NO_CONTEXT);

    tlvmContext_8080* cpu = tlvmMalloc(tlvmContext_8080);
    *context = &cpu->m_Header;

    if(g_8080Data.m_Header.m_ProcessorID == 0)
        tlvm8080SetupData();

    (*context)->m_ProcessorData = &g_8080Data.m_Header;

    (*context)->m_Registers = cpu->m_Registers;
    (*context)->m_Ports = cpu->m_Ports;

    TLVM_RETURN_CODE(SUCCESS);
}

tlvmReturn tlvmAdd8080Instructions(tlvmInstruction* instructionSet)
{

    instructionSet[TLVM_NOP]      = tlvmNOP;
    instructionSet[TLVM_HLT]      = tlvmHLT;
      
    instructionSet[TLVM_LXI_B]    = tlvmLXI;
    instructionSet[TLVM_LXI_D]    = tlvmLXI;
    instructionSet[TLVM_LXI_H]    = tlvmLXI;
    instructionSet[TLVM_LXI_SP]   = tlvmLXI;
      
    instructionSet[TLVM_LDAX_B]   = tlvmLDAX;
    instructionSet[TLVM_LDAX_D]   = tlvmLDAX;
  
    instructionSet[TLVM_STAX_B]   = tlvmSTAX;
    instructionSet[TLVM_STAX_D]   = tlvmSTAX;
      
    instructionSet[TLVM_MVI_B]    = tlvmMVI;
    instructionSet[TLVM_MVI_C]    = tlvmMVI;
    instructionSet[TLVM_MVI_D]    = tlvmMVI;
    instructionSet[TLVM_MVI_E]    = tlvmMVI;
    instructionSet[TLVM_MVI_H]    = tlvmMVI;
    instructionSet[TLVM_MVI_L]    = tlvmMVI;
    instructionSet[TLVM_MVI_M]    = tlvmMVI;
    instructionSet[TLVM_MVI_A]    = tlvmMVI;
  
    instructionSet[TLVM_LDA]      = tlvmLDA;
    
    instructionSet[TLVM_MOV_BB]   = tlvmMOV;
    instructionSet[TLVM_MOV_BC]   = tlvmMOV;
    instructionSet[TLVM_MOV_BD]   = tlvmMOV;
    instructionSet[TLVM_MOV_BE]   = tlvmMOV;
    instructionSet[TLVM_MOV_BH]   = tlvmMOV;
    instructionSet[TLVM_MOV_BL]   = tlvmMOV;
    instructionSet[TLVM_MOV_BM]   = tlvmMOV;
    instructionSet[TLVM_MOV_BA]   = tlvmMOV;
    
    instructionSet[TLVM_MOV_CB]   = tlvmMOV;
    instructionSet[TLVM_MOV_CC]   = tlvmMOV;
    instructionSet[TLVM_MOV_CD]   = tlvmMOV;
    instructionSet[TLVM_MOV_CE]   = tlvmMOV;
    instructionSet[TLVM_MOV_CH]   = tlvmMOV;
    instructionSet[TLVM_MOV_CL]   = tlvmMOV;
    instructionSet[TLVM_MOV_CM]   = tlvmMOV;
    instructionSet[TLVM_MOV_CA]   = tlvmMOV;
    
    instructionSet[TLVM_MOV_DB]   = tlvmMOV;
    instructionSet[TLVM_MOV_DC]   = tlvmMOV;
    instructionSet[TLVM_MOV_DD]   = tlvmMOV;
    instructionSet[TLVM_MOV_DE]   = tlvmMOV;
    instructionSet[TLVM_MOV_DH]   = tlvmMOV;
    instructionSet[TLVM_MOV_DL]   = tlvmMOV;
    instructionSet[TLVM_MOV_DM]   = tlvmMOV;
    instructionSet[TLVM_MOV_DA]   = tlvmMOV;
    
    instructionSet[TLVM_MOV_EB]   = tlvmMOV;
    instructionSet[TLVM_MOV_EC]   = tlvmMOV;
    instructionSet[TLVM_MOV_ED]   = tlvmMOV;
    instructionSet[TLVM_MOV_EE]   = tlvmMOV;
    instructionSet[TLVM_MOV_EH]   = tlvmMOV;
    instructionSet[TLVM_MOV_EL]   = tlvmMOV;
    instructionSet[TLVM_MOV_EM]   = tlvmMOV;
    instructionSet[TLVM_MOV_EA]   = tlvmMOV;
    
    instructionSet[TLVM_MOV_HB]   = tlvmMOV;
    instructionSet[TLVM_MOV_HC]   = tlvmMOV;
    instructionSet[TLVM_MOV_HD]   = tlvmMOV;
    instructionSet[TLVM_MOV_HE]   = tlvmMOV;
    instructionSet[TLVM_MOV_HH]   = tlvmMOV;
    instructionSet[TLVM_MOV_HL]   = tlvmMOV;
    instructionSet[TLVM_MOV_HM]   = tlvmMOV;
    instructionSet[TLVM_MOV_HA]   = tlvmMOV;
    
    instructionSet[TLVM_MOV_LB]   = tlvmMOV;
    instructionSet[TLVM_MOV_LC]   = tlvmMOV;
    instructionSet[TLVM_MOV_LD]   = tlvmMOV;
    instructionSet[TLVM_MOV_LE]   = tlvmMOV;
    instructionSet[TLVM_MOV_LH]   = tlvmMOV;
    instructionSet[TLVM_MOV_LL]   = tlvmMOV;
    instructionSet[TLVM_MOV_LM]   = tlvmMOV;
    instructionSet[TLVM_MOV_LA]   = tlvmMOV;
    
    instructionSet[TLVM_MOV_MB]   = tlvmMOV;
    instructionSet[TLVM_MOV_MC]   = tlvmMOV;
    instructionSet[TLVM_MOV_MD]   = tlvmMOV;
    instructionSet[TLVM_MOV_ME]   = tlvmMOV;
    instructionSet[TLVM_MOV_MH]   = tlvmMOV;
    instructionSet[TLVM_MOV_ML]   = tlvmMOV;
    instructionSet[TLVM_MOV_MA]   = tlvmMOV;
    
    instructionSet[TLVM_MOV_AB]   = tlvmMOV;
    instructionSet[TLVM_MOV_AC]   = tlvmMOV;
    instructionSet[TLVM_MOV_AD]   = tlvmMOV;
    instructionSet[TLVM_MOV_AE]   = tlvmMOV;
    instructionSet[TLVM_MOV_AH]   = tlvmMOV;
    instructionSet[TLVM_MOV_AL]   = tlvmMOV;
    instructionSet[TLVM_MOV_AM]   = tlvmMOV;
    instructionSet[TLVM_MOV_AA]   = tlvmMOV;
    
    instructionSet[TLVM_ANA_B]    = tlvmANA;
    instructionSet[TLVM_ANA_C]    = tlvmANA;
    instructionSet[TLVM_ANA_D]    = tlvmANA;
    instructionSet[TLVM_ANA_E]    = tlvmANA;
    instructionSet[TLVM_ANA_H]    = tlvmANA;
    instructionSet[TLVM_ANA_L]    = tlvmANA;
    instructionSet[TLVM_ANA_M]    = tlvmANA;
    instructionSet[TLVM_ANA_A]    = tlvmANA;
    
    instructionSet[TLVM_ANI]      = tlvmANI;
    
    instructionSet[TLVM_ORA_B]    = tlvmORA;
    instructionSet[TLVM_ORA_C]    = tlvmORA;
    instructionSet[TLVM_ORA_D]    = tlvmORA;
    instructionSet[TLVM_ORA_E]    = tlvmORA;
    instructionSet[TLVM_ORA_H]    = tlvmORA;
    instructionSet[TLVM_ORA_L]    = tlvmORA;
    instructionSet[TLVM_ORA_M]    = tlvmORA;
    instructionSet[TLVM_ORA_A]    = tlvmORA;
    
    instructionSet[TLVM_ORI]      = tlvmORI;
    
    instructionSet[TLVM_XRA_B]    = tlvmXRA;
    instructionSet[TLVM_XRA_C]    = tlvmXRA;
    instructionSet[TLVM_XRA_D]    = tlvmXRA;
    instructionSet[TLVM_XRA_E]    = tlvmXRA;
    instructionSet[TLVM_XRA_H]    = tlvmXRA;
    instructionSet[TLVM_XRA_L]    = tlvmXRA;
    instructionSet[TLVM_XRA_M]    = tlvmXRA;
    instructionSet[TLVM_XRA_A]    = tlvmXRA;
   
    instructionSet[TLVM_XRI]      = tlvmXRI;

    instructionSet[TLVM_PUSH_B]   = tlvmPUSH;
    instructionSet[TLVM_PUSH_D]   = tlvmPUSH;
    instructionSet[TLVM_PUSH_H]   = tlvmPUSH;
    instructionSet[TLVM_PUSH_PSW] = tlvmPUSH;

    instructionSet[TLVM_POP_B]    = tlvmPOP;
    instructionSet[TLVM_POP_D]    = tlvmPOP;
    instructionSet[TLVM_POP_H]    = tlvmPOP;
    instructionSet[TLVM_POP_PSW]  = tlvmPOP;

    instructionSet[TLVM_SPHL]     = tlvmSPHL;
    instructionSet[TLVM_XTHL]     = tlvmXTHL;
    instructionSet[TLVM_XCHG]     = tlvmXCHG;
    instructionSet[TLVM_PCHL]     = tlvmPCHL;

    instructionSet[TLVM_JNZ]      = tlvmJMP;
    instructionSet[TLVM_JZ]       = tlvmJMP;
    instructionSet[TLVM_JNC]      = tlvmJMP;
    instructionSet[TLVM_JC]       = tlvmJMP;
    instructionSet[TLVM_JPO]      = tlvmJMP;
    instructionSet[TLVM_JPE]      = tlvmJMP;
    instructionSet[TLVM_JP]       = tlvmJMP;
    instructionSet[TLVM_JM]       = tlvmJMP;
    instructionSet[TLVM_JMP]      = tlvmJMP;

    instructionSet[TLVM_CNZ]      = tlvmCALL;
    instructionSet[TLVM_CZ]       = tlvmCALL;
    instructionSet[TLVM_CNC]      = tlvmCALL;
    instructionSet[TLVM_CC]       = tlvmCALL;
    instructionSet[TLVM_CPO]      = tlvmCALL;
    instructionSet[TLVM_CPE]      = tlvmCALL;
    instructionSet[TLVM_CP]       = tlvmCALL;
    instructionSet[TLVM_CM]       = tlvmCALL;
    instructionSet[TLVM_CALL]     = tlvmCALL;

    instructionSet[TLVM_RNZ]      = tlvmRET;
    instructionSet[TLVM_RZ]       = tlvmRET;
    instructionSet[TLVM_RNC]      = tlvmRET;
    instructionSet[TLVM_RC]       = tlvmRET;
    instructionSet[TLVM_RPO]      = tlvmRET;
    instructionSet[TLVM_RPE]      = tlvmRET;
    instructionSet[TLVM_RP]       = tlvmRET;
    instructionSet[TLVM_RM]       = tlvmRET;
    instructionSet[TLVM_RET]      = tlvmRET;

    instructionSet[TLVM_ADD_B]    = tlvmADD;
    instructionSet[TLVM_ADD_C]    = tlvmADD;
    instructionSet[TLVM_ADD_D]    = tlvmADD;
    instructionSet[TLVM_ADD_E]    = tlvmADD;
    instructionSet[TLVM_ADD_H]    = tlvmADD;
    instructionSet[TLVM_ADD_L]    = tlvmADD;
    instructionSet[TLVM_ADD_M]    = tlvmADD;
    instructionSet[TLVM_ADD_A]    = tlvmADD;
   
    instructionSet[TLVM_ADC_B]    = tlvmADD;
    instructionSet[TLVM_ADC_C]    = tlvmADD;
    instructionSet[TLVM_ADC_D]    = tlvmADD;
    instructionSet[TLVM_ADC_E]    = tlvmADD;
    instructionSet[TLVM_ADC_H]    = tlvmADD;
    instructionSet[TLVM_ADC_L]    = tlvmADD;
    instructionSet[TLVM_ADC_M]    = tlvmADD;
    instructionSet[TLVM_ADC_A]    = tlvmADD;
   
    instructionSet[TLVM_SUB_B]    = tlvmSUB;
    instructionSet[TLVM_SUB_C]    = tlvmSUB;
    instructionSet[TLVM_SUB_D]    = tlvmSUB;
    instructionSet[TLVM_SUB_E]    = tlvmSUB;
    instructionSet[TLVM_SUB_H]    = tlvmSUB;
    instructionSet[TLVM_SUB_L]    = tlvmSUB;
    instructionSet[TLVM_SUB_M]    = tlvmSUB;
    instructionSet[TLVM_SUB_A]    = tlvmSUB;
   
    instructionSet[TLVM_SBB_B]    = tlvmSUB;
    instructionSet[TLVM_SBB_C]    = tlvmSUB;
    instructionSet[TLVM_SBB_D]    = tlvmSUB;
    instructionSet[TLVM_SBB_E]    = tlvmSUB;
    instructionSet[TLVM_SBB_H]    = tlvmSUB;
    instructionSet[TLVM_SBB_L]    = tlvmSUB;
    instructionSet[TLVM_SBB_M]    = tlvmSUB;
    instructionSet[TLVM_SBB_A]    = tlvmSUB;
   
    instructionSet[TLVM_CMP_B]    = tlvmCMP;
    instructionSet[TLVM_CMP_C]    = tlvmCMP;
    instructionSet[TLVM_CMP_D]    = tlvmCMP;
    instructionSet[TLVM_CMP_E]    = tlvmCMP;
    instructionSet[TLVM_CMP_H]    = tlvmCMP;
    instructionSet[TLVM_CMP_L]    = tlvmCMP;
    instructionSet[TLVM_CMP_M]    = tlvmCMP;
    instructionSet[TLVM_CMP_A]    = tlvmCMP;
   
    instructionSet[TLVM_INR_B]    = tlvmINR;
    instructionSet[TLVM_INR_C]    = tlvmINR;
    instructionSet[TLVM_INR_D]    = tlvmINR;
    instructionSet[TLVM_INR_E]    = tlvmINR;
    instructionSet[TLVM_INR_H]    = tlvmINR;
    instructionSet[TLVM_INR_L]    = tlvmINR;
    instructionSet[TLVM_INR_M]    = tlvmINR;
    instructionSet[TLVM_INR_A]    = tlvmINR;
   
    instructionSet[TLVM_INX_B]    = tlvmINX;
    instructionSet[TLVM_INX_D]    = tlvmINX;
    instructionSet[TLVM_INX_H]    = tlvmINX;
    instructionSet[TLVM_INX_SP]   = tlvmINX;
   
    instructionSet[TLVM_DCR_B]    = tlvmDCR;
    instructionSet[TLVM_DCR_C]    = tlvmDCR;
    instructionSet[TLVM_DCR_D]    = tlvmDCR;
    instructionSet[TLVM_DCR_E]    = tlvmDCR;
    instructionSet[TLVM_DCR_H]    = tlvmDCR;
    instructionSet[TLVM_DCR_L]    = tlvmDCR;
    instructionSet[TLVM_DCR_M]    = tlvmDCR;
    instructionSet[TLVM_DCR_A]    = tlvmDCR;
   
    instructionSet[TLVM_DCX_B]    = tlvmDCX;
    instructionSet[TLVM_DCX_D]    = tlvmDCX;
    instructionSet[TLVM_DCX_H]    = tlvmDCX;
    instructionSet[TLVM_DCX_SP]   = tlvmDCX;
   
    instructionSet[TLVM_ADI]      = tlvmADI;
    instructionSet[TLVM_ACI]      = tlvmADI;
    instructionSet[TLVM_SUI]      = tlvmSUI;
    instructionSet[TLVM_SBI]      = tlvmSUI;
    instructionSet[TLVM_CPI]      = tlvmCPI;
   
    instructionSet[TLVM_DAD_B]    = tlvmDAD;
    instructionSet[TLVM_DAD_D]    = tlvmDAD;
    instructionSet[TLVM_DAD_H]    = tlvmDAD;
    instructionSet[TLVM_DAD_SP]   = tlvmDAD;
   
    instructionSet[TLVM_STA]      = tlvmSTA;
   
    instructionSet[TLVM_OUT]      = tlvmOUT;
    instructionSet[TLVM_IN]       = tlvmIN;

    instructionSet[TLVM_RST_0]    = tlvmRST;
    instructionSet[TLVM_RST_1]    = tlvmRST;
    instructionSet[TLVM_RST_2]    = tlvmRST;
    instructionSet[TLVM_RST_3]    = tlvmRST;
    instructionSet[TLVM_RST_4]    = tlvmRST;
    instructionSet[TLVM_RST_5]    = tlvmRST;
    instructionSet[TLVM_RST_6]    = tlvmRST;
    instructionSet[TLVM_RST_7]    = tlvmRST;

    instructionSet[TLVM_EI]       = tlvmEI;
    instructionSet[TLVM_DI]       = tlvmDI;

    instructionSet[TLVM_RLC]      = tlvmROT;
    instructionSet[TLVM_RAL]      = tlvmROT;
    instructionSet[TLVM_RRC]      = tlvmROT;
    instructionSet[TLVM_RAR]      = tlvmROT;

    instructionSet[TLVM_SHLD]     = tlvmSHLD;
    instructionSet[TLVM_LHLD]     = tlvmLHLD;

    instructionSet[TLVM_STC]      = tlvmSTC;
    instructionSet[TLVM_CMC]      = tlvmCMC;

    instructionSet[TLVM_CMA]      = tlvmCMA;

    instructionSet[TLVM_DAA]      = tlvmDAA;

    TLVM_RETURN_CODE(SUCCESS);
}

void tlvm8080SetupData()
{
    g_8080Data.m_Header.m_ProcessorID = TLVM_CPU_8080;
    g_8080Data.m_Header.m_InstructionSet = g_8080Data.m_InstructionSet;

    g_8080Data.m_Header.m_Interrupt = tlvmInterrupt;

    tlvmAdd8080Instructions(g_8080Data.m_InstructionSet);
}

tlvmReturn tlvm8080Interrupt(tlvmContext* context, tlvmByte interrupt)
{
    TLVM_NULL_CHECK(context, NO_CONTEXT);

    if(TLVM_FLAG_ISSET(I, 8080))
        tlvm8080HandleInterrupt(context, interrupt);
    else
        context->m_Registers[TLVM_8080_REG_I] = interrupt;

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

    TLVM_FLAG_SET(C, 8080);
    
    // size of instruction - 1

    context->m_ProgramCounter += 1;
    if(cycles)
    	*cycles = 4;
    
    TLVM_RETURN_CODE(SUCCESS);
}

tlvmReturn tlvmCMC(tlvmContext* context, tlvmByte* cycles)
{
    TLVM_NULL_CHECK(context, NO_CONTEXT);

    TLVM_FLAG_SET_IF(TLVM_FLAG_ISSET(C, 8080) == 0, C, 8080);
    
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
    
    TLVM_REGISTER_COMPLEMENT(TLVM_8080_REG_A);

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
        context->m_Registers[TLVM_8080_REG_B] = opHigh;
        context->m_Registers[TLVM_8080_REG_C] = opLow;
	break;
    case TLVM_LXI_D:
        context->m_Registers[TLVM_8080_REG_D] = opHigh;
        context->m_Registers[TLVM_8080_REG_E] = opLow;
	break;
    case TLVM_LXI_H:
        context->m_Registers[TLVM_8080_REG_H] = opHigh;
        context->m_Registers[TLVM_8080_REG_L] = opLow;
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
    	addr = TLVM_GET_16BIT(TLVM_8080_REG_B, TLVM_8080_REG_C);
	break;
    case TLVM_STAX_D:
    	addr = TLVM_GET_16BIT(TLVM_8080_REG_D, TLVM_8080_REG_E);
	break;
    }
    tlvmByte* dst = tlvmGetMemory(context, addr, TLVM_FLAG_WRITE);
    TLVM_NULL_CHECK(dst, INVALID_INPUT);
    *dst = context->m_Registers[TLVM_8080_REG_A];
    
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
    *dstLo = context->m_Registers[TLVM_8080_REG_L];
    *dstHi = context->m_Registers[TLVM_8080_REG_H];

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
    context->m_Registers[TLVM_8080_REG_L] = *dstLo;
    context->m_Registers[TLVM_8080_REG_H] = *dstHi;
    
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
    context->m_Registers[TLVM_8080_REG_A] = *src;

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
    *dst = context->m_Registers[TLVM_8080_REG_A];

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
		addr = TLVM_GET_16BIT(TLVM_8080_REG_B, TLVM_8080_REG_C);
	break;
	case TLVM_LDAX_D:
		addr = TLVM_GET_16BIT(TLVM_8080_REG_D, TLVM_8080_REG_E);
	break;
	default:
		TLVM_RETURN_CODE(INVALID_INPUT);
	}

	tlvmByte* src = tlvmGetMemory(context, addr, TLVM_FLAG_READ);
    TLVM_NULL_CHECK(src, INVALID_INPUT);

	context->m_Registers[TLVM_8080_REG_A] = *src;

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
		src = &context->m_Registers[TLVM_8080_REG_B];
	break;
	case TLVM_ANA_C:
		src = &context->m_Registers[TLVM_8080_REG_C];
	break;
	case TLVM_ANA_D:
		src = &context->m_Registers[TLVM_8080_REG_D];
	break;
	case TLVM_ANA_E:
		src = &context->m_Registers[TLVM_8080_REG_E];
	break;
	case TLVM_ANA_H:
		src = &context->m_Registers[TLVM_8080_REG_H];
	break;
	case TLVM_ANA_L:
		src = &context->m_Registers[TLVM_8080_REG_L];
	break;
	case TLVM_ANA_M:
		{
			tlvmShort addr = TLVM_GET_16BIT(TLVM_8080_REG_H, TLVM_8080_REG_L);
			src = tlvmGetMemory(context, addr, TLVM_FLAG_READ);
		}
	break;
	case TLVM_ANA_A:
		src = &context->m_Registers[TLVM_8080_REG_A];
	break;
	}

    TLVM_NULL_CHECK(src, INVALID_INPUT);

	context->m_Registers[TLVM_8080_REG_A] &= *src;

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

	context->m_Registers[TLVM_8080_REG_A] &= operand;
    TLVM_SET_FLAGS(context->m_Registers[TLVM_8080_REG_A], 8080);

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
		src = &context->m_Registers[TLVM_8080_REG_B];
	break;
	case TLVM_ORA_C:
		src = &context->m_Registers[TLVM_8080_REG_C];
	break;
	case TLVM_ORA_D:
		src = &context->m_Registers[TLVM_8080_REG_D];
	break;
	case TLVM_ORA_E:
		src = &context->m_Registers[TLVM_8080_REG_E];
	break;
	case TLVM_ORA_H:
		src = &context->m_Registers[TLVM_8080_REG_H];
	break;
	case TLVM_ORA_L:
		src = &context->m_Registers[TLVM_8080_REG_L];
	break;
	case TLVM_ORA_M:
		{
			tlvmShort addr = TLVM_GET_16BIT(TLVM_8080_REG_H, TLVM_8080_REG_L);
			src = tlvmGetMemory(context, addr, TLVM_FLAG_READ);
		}
	break;
	case TLVM_ORA_A:
		src = &context->m_Registers[TLVM_8080_REG_A];
	break;
	}

    TLVM_NULL_CHECK(src, INVALID_INPUT);

	context->m_Registers[TLVM_8080_REG_A] |= *src;

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

	context->m_Registers[TLVM_8080_REG_A] |= operand;

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
		src = &context->m_Registers[TLVM_8080_REG_B];
	break;
	case TLVM_XRA_C:
		src = &context->m_Registers[TLVM_8080_REG_C];
	break;
	case TLVM_XRA_D:
		src = &context->m_Registers[TLVM_8080_REG_D];
	break;
	case TLVM_XRA_E:
		src = &context->m_Registers[TLVM_8080_REG_E];
	break;
	case TLVM_XRA_H:
		src = &context->m_Registers[TLVM_8080_REG_H];
	break;
	case TLVM_XRA_L:
		src = &context->m_Registers[TLVM_8080_REG_L];
	break;
	case TLVM_XRA_M:
		{
			tlvmShort addr = TLVM_GET_16BIT(TLVM_8080_REG_H, TLVM_8080_REG_L);
			src = tlvmGetMemory(context, addr, TLVM_FLAG_READ);
		}
	break;
	case TLVM_XRA_A:
		src = &context->m_Registers[TLVM_8080_REG_A];
	break;
	}

    TLVM_NULL_CHECK(src, INVALID_INPUT);

	context->m_Registers[TLVM_8080_REG_A] ^= *src;
    TLVM_FLAG_UNSET(H, 8080);
    TLVM_FLAG_UNSET(C, 8080);

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

	context->m_Registers[TLVM_8080_REG_A] ^= operand;
    TLVM_FLAG_UNSET(H, 8080);
    TLVM_FLAG_UNSET(C, 8080);

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
        context->m_Registers[TLVM_8080_REG_B]++;
    break;
    case TLVM_INR_C:
        context->m_Registers[TLVM_8080_REG_C]++;
    break;
    case TLVM_INR_D:
        context->m_Registers[TLVM_8080_REG_D]++;
    break;
    case TLVM_INR_E:
        context->m_Registers[TLVM_8080_REG_E]++;
    break;
    case TLVM_INR_H:
        context->m_Registers[TLVM_8080_REG_H]++;
    break;
    case TLVM_INR_L:
        context->m_Registers[TLVM_8080_REG_L]++;
    break;
    case TLVM_INR_M:
        {
            tlvmShort addr = TLVM_GET_16BIT(TLVM_8080_REG_H, TLVM_8080_REG_L);
            tlvmByte* val = tlvmGetMemory(context, addr, TLVM_FLAG_WRITE);
            if(val != NULL)
                (*val)++;
        }
    break;
    case TLVM_INR_A:
        context->m_Registers[TLVM_8080_REG_A]++;
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
        val = &context->m_Registers[TLVM_8080_REG_B];
    break;
    case TLVM_DCR_C:
        val = &context->m_Registers[TLVM_8080_REG_C];
    break;
    case TLVM_DCR_D:
        val = &context->m_Registers[TLVM_8080_REG_D];
    break;
    case TLVM_DCR_E:
        val = &context->m_Registers[TLVM_8080_REG_E];
    break;
    case TLVM_DCR_H:
        val = &context->m_Registers[TLVM_8080_REG_H];
    break;
    case TLVM_DCR_L:
        val = &context->m_Registers[TLVM_8080_REG_L];
    break;
    case TLVM_DCR_M:
        val = tlvmGetMemory(context, TLVM_GET_16BIT(TLVM_8080_REG_H, TLVM_8080_REG_L), TLVM_FLAG_WRITE);
    break;
    case TLVM_DCR_A:
        val = &context->m_Registers[TLVM_8080_REG_A];
    break;
    }

    if(val != NULL)
    {
        (*val)--;
        TLVM_FLAG_SET_IF((*val == 0), Z, 8080);
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

    tlvmShort tmp = TLVM_GET_16BIT(TLVM_8080_REG_H, TLVM_8080_REG_L);
    TLVM_SET_16BIT(TLVM_8080_REG_H, TLVM_8080_REG_L, TLVM_GET_16BIT(TLVM_8080_REG_D, TLVM_8080_REG_E));
    TLVM_SET_16BIT(TLVM_8080_REG_D, TLVM_8080_REG_E, tmp);
    // size of instruction    = 1
    context->m_ProgramCounter += 1;
    if(cycles)
        *cycles =5;

    TLVM_RETURN_CODE(SUCCESS);

}

tlvmReturn tlvmPCHL(tlvmContext* context, tlvmByte* cycles)
{
    TLVM_NULL_CHECK(context, NO_CONTEXT);

    context->m_ProgramCounter = TLVM_GET_16BIT(TLVM_8080_REG_H, TLVM_8080_REG_L);

    // size of instruction    = 1
    //context->m_ProgramCounter += 1;
    if(cycles)
        *cycles =5;

    TLVM_RETURN_CODE(SUCCESS);

}

tlvmReturn tlvmDAA(tlvmContext* context, tlvmByte* cycles)
{
    TLVM_NULL_CHECK(context, NO_CONTEXT);

    tlvmByte nibbleLo = context->m_Registers[TLVM_8080_REG_A] & 0x0F;
    tlvmByte nibbleHi = (context->m_Registers[TLVM_8080_REG_A] & 0xF0)>>4;

    if(nibbleLo>0x09 || TLVM_FLAG_ISSET(H, 8080))
    {
        nibbleLo += 0x06;
        TLVM_FLAG_SET_IF(nibbleLo & 0xF0, H, 8080);
        if(TLVM_FLAG_ISSET(H, 8080))
            nibbleHi += 0x01;
    }
    if(nibbleHi>0x09 || TLVM_FLAG_ISSET(C, 8080))
    {
        nibbleHi += 0x06;
    }
    context->m_Registers[TLVM_8080_REG_A] = ((nibbleHi & 0x0F)<<4) | (nibbleLo & 0x0F);
    TLVM_SET_FLAGS(context->m_Registers[TLVM_8080_REG_A], 8080);
    TLVM_FLAG_SET_IF(nibbleHi & 0xF0, C, 8080);

    // size of instruction    = 1
    context->m_ProgramCounter += 1;
    if(cycles)
        *cycles = 4;

    TLVM_RETURN_CODE(SUCCESS);

}
#endif/*TLVM_HAS_8080*/
