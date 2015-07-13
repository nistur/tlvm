#pragma once
#ifndef __Z80_H__
#define __Z80_H__

#ifdef  TLVM_HAS_Z80

tlvmReturn tlvmZ80Init(tlvmContext** context);

/*********************************************
 * tlvmZ80SetupData
 *     Add instruction set to CPU
 *********************************************/
void       tlvmZ80SetupData();

typedef struct _tlvmContext_Z80
{
    tlvmContext m_Header;

    tlvmByte    m_Registers[9];
    tlvmByte    m_Ports[256];
} tlvmContext_Z80;

typedef struct _tlvmProcessorData_Z80
{
    tlvmProcessorData m_Header;

    // instrution set
    tlvmInstruction     m_InstructionSet[512];
} tlvmProcessorData_Z80;


#endif/*TLVM_HAS_Z80*/
#endif/*__Z80_H__*/
