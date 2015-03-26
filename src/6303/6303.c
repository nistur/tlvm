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

#ifdef  TLVM_HAS_6303
#include "tlvm_internal.h"

TLVM_INSTRUCTION_DEFINE(6303, TRAP,  0x00);
TLVM_INSTRUCTION_DEFINE(6303, NOP,   0x01);
TLVM_INSTRUCTION_DEFINE(6303, LSRD,  0x04);
TLVM_INSTRUCTION_DEFINE(6303, LSRA,  0x44);
TLVM_INSTRUCTION_DEFINE(6303, LSRB,  0x54);
TLVM_INSTRUCTION_DEFINE(6303, LSRdX, 0x64);
TLVM_INSTRUCTION_DEFINE(6303, LSRmm, 0x74);

tlvmProcessorData_6303 g_6303Data;

tlvmReturn tlvm6303Init(tlvmContext** context)
{
    TLVM_NULL_CHECK(context, NO_CONTEXT);

    tlvmContext_6303* cpu = tlvmMalloc(tlvmContext_6303);
    *context = &cpu->m_Header;

    if(g_6303Data.m_Header.m_ProcessorID == 0)
        tlvm6303SetupData();

    (*context)->m_ProcessorData = &g_6303Data.m_Header;
    (*context)->m_InstructionSet = g_6303Data.m_InstructionSet;

    (*context)->m_Registers = cpu->m_Registers;
    (*context)->m_Ports = cpu->m_Ports;

    TLVM_RETURN_CODE(SUCCESS);
}

void tlvm6303SetupData()
{
    g_6303Data.m_Header.m_ProcessorID = TLVM_CPU_6303;

    TLVM_INSTRUCTION_ADD          (g_6303Data.m_InstructionSet, 6303, TRAP);
    TLVM_INSTRUCTION_ADD          (g_6303Data.m_InstructionSet, 6303, NOP);
    TLVM_INSTRUCTION_ADD_VARIATION(g_6303Data.m_InstructionSet, 6303, LSRD,  LSR);
    TLVM_INSTRUCTION_ADD_VARIATION(g_6303Data.m_InstructionSet, 6303, LSRA,  LSR);
    TLVM_INSTRUCTION_ADD_VARIATION(g_6303Data.m_InstructionSet, 6303, LSRB,  LSR);
    TLVM_INSTRUCTION_ADD_VARIATION(g_6303Data.m_InstructionSet, 6303, LSRdX, LSR);
    TLVM_INSTRUCTION_ADD_VARIATION(g_6303Data.m_InstructionSet, 6303, LSRmm, LSR);
}

tlvmReturn tlvm6303TRAP(tlvmContext* context, tlvmByte* cycles)
{
    TLVM_NULL_CHECK(context, NO_CONTEXT);


    context->m_ProgramCounter += 1;
    TLVM_RETURN_CODE(EXIT); // TRAP should bail. Don't exit successfully
}

tlvmReturn tlvm6303NOP(tlvmContext* context, tlvmByte* cycles)
{
    TLVM_NULL_CHECK(context, NO_CONTEXT);

    context->m_ProgramCounter += 1;
    if(cycles)
        *cycles = 1;

    TLVM_RETURN_CODE(SUCCESS);
}

tlvmReturn tlvm6303LSR(tlvmContext* context, tlvmByte* cycles)
{
    TLVM_NULL_CHECK(context, NO_CONTEXT);

    TLVM_GET_OP(opcode, 0);

    tlvmByte cycleCount = 1;
    tlvmByte length = 1;
    if(opcode == TLVM_6303_LSRD)
    {
        tlvmShort val = TLVM_GET_16BIT(TLVM_REG_D, TLVM_REG_E);
        TLVM_FLAG_SET_IF(val & 1<<15,C, 6303);
        val <<= 1;
        TLVM_FLAG_SET_IF(val == 0, Z, 6303);
        TLVM_SET_16BIT(TLVM_REG_D, TLVM_REG_E, val);
    }
    else if(opcode == TLVM_6303_LSRA)
    {
        TLVM_REGISTER(TLVM_REG_A) <<= 1;
    }
    else if(opcode == TLVM_6303_LSRB)
    {
        TLVM_REGISTER(TLVM_REG_B) <<= 1;
    }
    else if(opcode == TLVM_6303_LSRdX)
    {
        length = 2;
        cycleCount = 6;
    }
    else if(opcode == TLVM_6303_LSRmm)
    {
        length = 3;
        cycleCount = 6;
    }

    context->m_ProgramCounter += length;
    if(cycles)
        *cycles = cycleCount;

    TLVM_RETURN_CODE(SUCCESS);
}

#endif/*TLVM_HAS_6303*/