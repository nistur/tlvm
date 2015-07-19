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

#ifdef  TLVM_HAS_6800
#include "tlvm_internal.h"

TLVM_INSTRUCTION_DEFINE(6800, NOP,   0x01);
TLVM_INSTRUCTION_DEFINE(6800, TAP,   0x06);
TLVM_INSTRUCTION_DEFINE(6800, TPA,   0x07);
TLVM_INSTRUCTION_DEFINE(6800, INX,   0x08);
TLVM_INSTRUCTION_DEFINE(6800, DEX,   0x09);
TLVM_INSTRUCTION_DEFINE(6800, CLV,   0x0A);
TLVM_INSTRUCTION_DEFINE(6800, SEV,   0x0B);
TLVM_INSTRUCTION_DEFINE(6800, CLC,   0x0C);
TLVM_INSTRUCTION_DEFINE(6800, SEC,   0x0D);
TLVM_INSTRUCTION_DEFINE(6800, CLI,   0x0E);
TLVM_INSTRUCTION_DEFINE(6800, SEI,   0x0F);

TLVM_INSTRUCTION_DEFINE(6800, SBA,   0x10);
TLVM_INSTRUCTION_DEFINE(6800, CBA,   0x11);
TLVM_INSTRUCTION_DEFINE(6800, TAB,   0x16);
TLVM_INSTRUCTION_DEFINE(6800, TBA,   0x17);
TLVM_INSTRUCTION_DEFINE(6800, DAA,   0x19);
TLVM_INSTRUCTION_DEFINE(6800, ABA,   0x1B);

TLVM_INSTRUCTION_DEFINE(6800, BRA,   0x20);
TLVM_INSTRUCTION_DEFINE(6800, BHI,   0x22);
TLVM_INSTRUCTION_DEFINE(6800, BLS,   0x23);
TLVM_INSTRUCTION_DEFINE(6800, BCC,   0x24);
TLVM_INSTRUCTION_DEFINE(6800, BCS,   0x25);
TLVM_INSTRUCTION_DEFINE(6800, BNE,   0x26);
TLVM_INSTRUCTION_DEFINE(6800, BEQ,   0x27);
TLVM_INSTRUCTION_DEFINE(6800, BVC,   0x28);
TLVM_INSTRUCTION_DEFINE(6800, BVS,   0x29);
TLVM_INSTRUCTION_DEFINE(6800, BPL,   0x2A);
TLVM_INSTRUCTION_DEFINE(6800, BMI,   0x2B);
TLVM_INSTRUCTION_DEFINE(6800, BGE,   0x2C);
TLVM_INSTRUCTION_DEFINE(6800, BLT,   0x2D);
TLVM_INSTRUCTION_DEFINE(6800, BGT,   0x2E);
TLVM_INSTRUCTION_DEFINE(6800, BLE,   0x2F);

TLVM_INSTRUCTION_DEFINE(6800, TSX,   0x30);
TLVM_INSTRUCTION_DEFINE(6800, PULA,  0x32);
TLVM_INSTRUCTION_DEFINE(6800, PULB,  0x33);
TLVM_INSTRUCTION_DEFINE(6800, INS,   0x31);
TLVM_INSTRUCTION_DEFINE(6800, DES,   0x34);
TLVM_INSTRUCTION_DEFINE(6800, TXS,   0x35);
TLVM_INSTRUCTION_DEFINE(6800, PSHA,  0x36);
TLVM_INSTRUCTION_DEFINE(6800, PSHB,  0x37);
TLVM_INSTRUCTION_DEFINE(6800, RTS,   0x39);
TLVM_INSTRUCTION_DEFINE(6800, RTI,   0x3B);

TLVM_INSTRUCTION_DEFINE(6800, LSRA,  0x44);
TLVM_INSTRUCTION_DEFINE(6800, LSRB,  0x54);
TLVM_INSTRUCTION_DEFINE(6800, LSRdX, 0x64);
TLVM_INSTRUCTION_DEFINE(6800, LSRmm, 0x74);

tlvmProcessorData_6800 g_6800Data;

tlvmReturn tlvm6800Init(tlvmContext** context)
{
    TLVM_NULL_CHECK(context, NO_CONTEXT);

    tlvmContext_6800* cpu = tlvmMalloc(tlvmContext_6800);
    *context = &cpu->m_Header;

    if(g_6800Data.m_Header.m_ProcessorID == 0)
        tlvm6800SetupData();

    (*context)->m_ProcessorData = &g_6800Data.m_Header;

    (*context)->m_Registers = cpu->m_Registers;
    (*context)->m_Ports = cpu->m_Ports;

    TLVM_RETURN_CODE(SUCCESS);
}

void tlvm6800SetupData()
{
    g_6800Data.m_Header.m_ProcessorID = TLVM_CPU_6800;
    g_6800Data.m_Header.m_InstructionSet = g_6800Data.m_InstructionSet;

    TLVM_INSTRUCTION_ADD          (g_6800Data.m_InstructionSet, 6800, NOP);
    TLVM_INSTRUCTION_ADD_VARIATION(g_6800Data.m_InstructionSet, 6800, TAP, TRA);
    TLVM_INSTRUCTION_ADD_VARIATION(g_6800Data.m_InstructionSet, 6800, TPA, TRA);
    TLVM_INSTRUCTION_ADD_VARIATION(g_6800Data.m_InstructionSet, 6800, INX, INC);
    TLVM_INSTRUCTION_ADD_VARIATION(g_6800Data.m_InstructionSet, 6800, DEX, DEC);
    TLVM_INSTRUCTION_ADD_VARIATION(g_6800Data.m_InstructionSet, 6800, CLV, CLR);
    TLVM_INSTRUCTION_ADD_VARIATION(g_6800Data.m_InstructionSet, 6800, SEV, SET);
    TLVM_INSTRUCTION_ADD_VARIATION(g_6800Data.m_InstructionSet, 6800, CLC, CLR);
    TLVM_INSTRUCTION_ADD_VARIATION(g_6800Data.m_InstructionSet, 6800, SEC, SET);
    TLVM_INSTRUCTION_ADD_VARIATION(g_6800Data.m_InstructionSet, 6800, CLI, CLR);
    TLVM_INSTRUCTION_ADD_VARIATION(g_6800Data.m_InstructionSet, 6800, SEI, SET);

    TLVM_INSTRUCTION_ADD_VARIATION(g_6800Data.m_InstructionSet, 6800, SBA, SUB);
    TLVM_INSTRUCTION_ADD_VARIATION(g_6800Data.m_InstructionSet, 6800, CBA, CMP);
    TLVM_INSTRUCTION_ADD_VARIATION(g_6800Data.m_InstructionSet, 6800, TAB, TRA);
    TLVM_INSTRUCTION_ADD_VARIATION(g_6800Data.m_InstructionSet, 6800, TBA, TRA);
    TLVM_INSTRUCTION_ADD          (g_6800Data.m_InstructionSet, 6800, DAA);
    TLVM_INSTRUCTION_ADD_VARIATION(g_6800Data.m_InstructionSet, 6800, ABA, ADD);
    
    TLVM_INSTRUCTION_ADD_VARIATION(g_6800Data.m_InstructionSet, 6800, BRA, BRA);
    TLVM_INSTRUCTION_ADD_VARIATION(g_6800Data.m_InstructionSet, 6800, BHI, BRA);
    TLVM_INSTRUCTION_ADD_VARIATION(g_6800Data.m_InstructionSet, 6800, BLS, BRA);
    TLVM_INSTRUCTION_ADD_VARIATION(g_6800Data.m_InstructionSet, 6800, BCC, BRA);
    TLVM_INSTRUCTION_ADD_VARIATION(g_6800Data.m_InstructionSet, 6800, BCS, BRA);
    TLVM_INSTRUCTION_ADD_VARIATION(g_6800Data.m_InstructionSet, 6800, BNE, BRA);
    TLVM_INSTRUCTION_ADD_VARIATION(g_6800Data.m_InstructionSet, 6800, BEQ, BRA);
    TLVM_INSTRUCTION_ADD_VARIATION(g_6800Data.m_InstructionSet, 6800, BVC, BRA);
    TLVM_INSTRUCTION_ADD_VARIATION(g_6800Data.m_InstructionSet, 6800, BVS, BRA);
    TLVM_INSTRUCTION_ADD_VARIATION(g_6800Data.m_InstructionSet, 6800, BPL, BRA);
    TLVM_INSTRUCTION_ADD_VARIATION(g_6800Data.m_InstructionSet, 6800, BMI, BRA);
    TLVM_INSTRUCTION_ADD_VARIATION(g_6800Data.m_InstructionSet, 6800, BGE, BRA);
    TLVM_INSTRUCTION_ADD_VARIATION(g_6800Data.m_InstructionSet, 6800, BLT, BRA);
    TLVM_INSTRUCTION_ADD_VARIATION(g_6800Data.m_InstructionSet, 6800, BGT, BRA);
    TLVM_INSTRUCTION_ADD_VARIATION(g_6800Data.m_InstructionSet, 6800, BLE, BRA);

    TLVM_INSTRUCTION_ADD_VARIATION(g_6800Data.m_InstructionSet, 6800, TSX, TRA);
    TLVM_INSTRUCTION_ADD_VARIATION(g_6800Data.m_InstructionSet, 6800, PULA, PUL);
    TLVM_INSTRUCTION_ADD_VARIATION(g_6800Data.m_InstructionSet, 6800, PULB, PUL);
    TLVM_INSTRUCTION_ADD_VARIATION(g_6800Data.m_InstructionSet, 6800, INS, INC);
    TLVM_INSTRUCTION_ADD_VARIATION(g_6800Data.m_InstructionSet, 6800, DES, DEC);
    TLVM_INSTRUCTION_ADD_VARIATION(g_6800Data.m_InstructionSet, 6800, TXS, TRA);
    TLVM_INSTRUCTION_ADD_VARIATION(g_6800Data.m_InstructionSet, 6800, PSHA, PSH);
    TLVM_INSTRUCTION_ADD_VARIATION(g_6800Data.m_InstructionSet, 6800, PSHB, PSH);
    TLVM_INSTRUCTION_ADD          (g_6800Data.m_InstructionSet, 6800, RTS);
    TLVM_INSTRUCTION_ADD          (g_6800Data.m_InstructionSet, 6800, RTI);

    TLVM_INSTRUCTION_ADD_VARIATION(g_6800Data.m_InstructionSet, 6800, LSRA,  LSR);
    TLVM_INSTRUCTION_ADD_VARIATION(g_6800Data.m_InstructionSet, 6800, LSRB,  LSR);
    TLVM_INSTRUCTION_ADD_VARIATION(g_6800Data.m_InstructionSet, 6800, LSRdX, LSR);
    TLVM_INSTRUCTION_ADD_VARIATION(g_6800Data.m_InstructionSet, 6800, LSRmm, LSR);
}

tlvmReturn tlvm6800NOP(tlvmContext* context, tlvmByte* cycles)
{
    TLVM_NULL_CHECK(context, NO_CONTEXT);

    context->m_ProgramCounter += 1;
    if(cycles)
        *cycles = 1;

    TLVM_RETURN_CODE(SUCCESS);
}

#endif/*TLVM_HAS_6800*/
