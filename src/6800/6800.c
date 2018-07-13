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

tlvmReturn tlvm6800NOP(tlvmContext* ctx, tlvmByte* cycles);

#define _______ NULL
#define __(_m) tlvm6800##_m /* Standard instruction */
#define _A(_m) __(_m##_A)    /* Instruction on A accumulator */
#define _B(_m) __(_m##_B)    /* Instruction on B accumulator */
#define X_(_m) __(_m##_X)    /* Indexed address */
#define E_(_m) __(_m##_E)    /* Extended address */
#define IA(_m) _A(_m##_I)    /* Immediate address -> A */
#define DA(_m) _A(_m##_D)    /* Direct address -> A */
#define XA(_m) _A(_m##_X)    /* Indexed address -> A */
#define EA(_m) _A(_m##_E)    /* Extended address -> A */
#define IB(_m) _A(_m##_I)    /* Immediate address -> B */
#define DB(_m) _A(_m##_D)    /* Direct address -> B */
#define XB(_m) _A(_m##_X)    /* Indexed address -> B */
#define EB(_m) _A(_m##_E)    /* Extended address -> B */

tlvmInstruction g_6800InstructionSet[] =  {
/*          0       1       2       3       4       5       6       7       8       9       A       B       C       D       E       F */
/* 0 */ _______,__(NOP),_______,_______,_______,_______,__(TAP),__(TPA),__(INX),__(DEX),__(CLV),__(SEV),__(CLC),__(SEC),__(CLI),__(SEI),
/* 1 */ __(SBA),_______,_______,_______,_______,_______,__(TAB),__(TBA),_______,__(DAA),_______,__(ABA),_______,_______,_______,_______,
/* 2 */ __(BRA),_______,__(BHI),__(BLS),__(BCC),__(BCS),__(BNE),__(BEQ),__(BVC),__(BVS),__(BPL),__(BMI),__(BGE),__(BLT),__(BGT),__(BLE),
/* 3 */ __(TSX),__(INS),_A(PUL),_B(PUL),__(DES),__(TXS),_A(PSH),_B(PSH),_______,__(RTS),_______,__(RTI),_______,_______,__(WAI),__(SWI),
/* 4 */ _A(NEG),_______,_______,_A(COM),_A(LSR),_______,_______,_______,_______,_______,_A(DEC),_______,_A(INC),_______,_______,_______,
/* 5 */ _B(NEG),_______,_______,_B(COM),_B(LSR),_______,_______,_______,_______,_______,_B(DEC),_______,_B(INC),_______,_______,_______,
/* 6 */ X_(NEG),_______,_______,X_(COM),X_(LSR),_______,_______,_______,_______,_______,X_(DEC),_______,X_(INC),_______,_______,_______,
/* 7 */ E_(NEG),_______,_______,E_(COM),E_(LSR),_______,_______,_______,_______,_______,E_(DEC),_______,E_(INC),_______,_______,_______,
/* 8 */ _______,IA(CMP),_______,_______,_______,_______,IA(LDA),_______,_______,_______,_______,_______,_______,_______,_______,_______,
/* 9 */ _______,DA(CMP),_______,_______,_______,_______,DA(LDA),_______,_______,_______,_______,_______,_______,_______,_______,_______,
/* A */ _______,XA(CMP),_______,_______,_______,_______,XA(LDA),_______,_______,_______,_______,_______,_______,X_(JSR),_______,_______,
/* B */ _______,EA(CMP),_______,_______,_______,_______,EA(LDA),_______,_______,_______,_______,_______,_______,E_(JSR),_______,_______,
/* C */ _______,IB(CMP),_______,_______,_______,_______,IB(LDA),_______,_______,_______,_______,_______,_______,_______,_______,_______,
/* D */ _______,DB(CMP),_______,_______,_______,_______,DB(LDA),_______,_______,_______,_______,_______,_______,_______,_______,_______,
/* E */ _______,XB(CMP),_______,_______,_______,_______,XB(LDA),_______,_______,_______,_______,_______,_______,_______,_______,_______,
/* F */ _______,EB(CMP),_______,_______,_______,_______,EB(LDA),_______,_______,_______,_______,_______,_______,_______,_______,_______
};


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
    (*context)->m_WideRegisters = cpu->m_WideRegisters;
    (*context)->m_Ports = cpu->m_Ports;

    TLVM_RETURN_CODE(SUCCESS);
}

void tlvm6800SetupData()
{
    g_6800Data.m_Header.m_ProcessorID = TLVM_CPU_6800;
    g_6800Data.m_InstructionSet = g_6800InstructionSet;
    g_6800Data.m_Header.m_InstructionSet = g_6800Data.m_InstructionSet;

    g_6800Data.m_Header.m_Interrupt = tlvm6800Interrupt;

}

tlvmReturn tlvm6800Interrupt(tlvmContext* context, tlvmByte interrupt)
{
    TLVM_NULL_CHECK(context, NO_CONTEXT);

    // interrupts will un-stall a stallec CPU
    context->m_Flags &= ~TLVM_FLAG_STALL;

    tlvmBool  willInterrupt = TLVM_FALSE;
    tlvmShort addr = 0;
    
    if(interrupt == TLVM_INTERRUPT_RESET)
    {
        TLVM_GET_MEMORY16(vec, TLVM_6800_INT_RESET);
        addr = vec;
        willInterrupt = TLVM_TRUE;
    }
    else if(interrupt == TLVM_INTERRUPT_NMI)
    {
        TLVM_GET_MEMORY16(vec, TLVM_6800_INT_NMI);
        addr = vec;
        willInterrupt = TLVM_TRUE;
    }
    else if(interrupt == TLVM_INTERRUPT_IRQ)
    {
        if(context->m_Interrupts != TLVM_INTERRUPT_NMI &&
           TLVM_FLAG_ISSET(I, 6800))
        {
            TLVM_GET_MEMORY16(vec, TLVM_6800_INT_IRQ);
            addr = vec;
            willInterrupt = TLVM_TRUE;
        }
    }

    
    if(willInterrupt)
    {
        if(context->m_Interrupts == TLVM_INTERRUPT_NONE && interrupt != TLVM_INTERRUPT_RESET)
        {
            TLVM_STACK_PUSH16(context->m_ProgramCounter);
            TLVM_STACK_PUSH16(TLVM_REGISTER16(TLVM_6800_REG16_IX));
            TLVM_STACK_PUSH(TLVM_REGISTER(TLVM_6800_REG_A));
            TLVM_STACK_PUSH(TLVM_REGISTER(TLVM_6800_REG_B));
            TLVM_STACK_PUSH(TLVM_REGISTER(TLVM_6800_REG_F));
        }

        context->m_Interrupts = interrupt;

        context->m_ProgramCounter = addr;
    }
    
    TLVM_RETURN_CODE(SUCCESS);
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
