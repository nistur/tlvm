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

#define ______ NULL
#define _(_X) tlvm6800##_X /* Standard instruction */
#define A(_X) _(_X##_A)    /* Instruction on A accumulator */
#define B(_X) _(_X##_B)    /* Instruction on B accumulator */
#define I(_X) _(_X##_I)    /* Indexed address */
#define E(_X) _(_X##_E)    /* Extended address */

tlvmInstruction g_6800InstructionSet[] =  {
/*             0      1      2      3      4      5      6      7      8      9      A      B      C      D      E      F */
    /* 0 */ ______,_(NOP),______,______,______,______,_(TAP),_(TPA),_(INX),_(DEX),_(CLV),_(SEV),_(CLC),_(SEC),_(CLI),_(SEI),
    /* 1 */ _(SBA),______,______,______,______,______,_(TAB),_(TBA),______,_(DAA),______,_(ABA),______,______,______,______,
    /* 2 */ _(BRA),______,_(BHI),_(BLS),_(BCC),_(BCS),_(BNE),_(BEQ),_(BVC),_(BVS),_(BPL),_(BMI),_(BGE),_(BLT),_(BGT),_(BLE),
    /* 3 */ _(TSX),_(INS),A(PUL),B(PUL),_(DES),_(TXS),A(PSH),B(PSH),______,_(RTS),______,_(RTI),______,______,_(WAI),_(SWI),
    /* 4 */ A(NEG),______,______,A(COM),A(LSR),______,______,______,______,______,A(DEC),______,A(INC),______,______,______,
    /* 5 */ B(NEG),______,______,B(COM),B(LSR),______,______,______,______,______,B(DEC),______,B(INC),______,______,______,
    /* 6 */ I(NEG),______,______,I(COM),I(LSR),______,______,______,______,______,I(DEC),______,I(INC),______,______,______,
    /* 7 */ E(NEG),______,______,E(COM),E(LSR),______,______,______,______,______,E(DEC),______,E(INC),______,______,______,
    /* 8 */ ______,_(CMP),______,______,______,______,______,______,______,______,______,______,______,______,______,______,
    /* 9 */ ______,_(CMP),______,______,______,______,______,______,______,______,______,______,______,______,______,______,
    /* A */ ______,_(CMP),______,______,______,______,______,______,______,______,______,______,______,______,______,______,
    /* B */ ______,_(CMP),______,______,______,______,______,______,______,______,______,______,______,______,______,______,
    /* C */ ______,_(CMP),______,______,______,______,______,______,______,______,______,______,______,______,______,______,
    /* D */ ______,_(CMP),______,______,______,______,______,______,______,______,______,______,______,______,______,______,
    /* E */ ______,_(CMP),______,______,______,______,______,______,______,______,______,______,______,______,______,______,
    /* F */ ______,_(CMP),______,______,______,______,______,______,______,______,______,______,______,______,______,______
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
        TLVM_GET_MEMORY16(interrupt, TLVM_6800_INT_RESET);
        addr = interrupt;
        willInterrupt = TLVM_TRUE;
    }
    else if(interrupt == TLVM_INTERRUPT_NMI)
    {
        TLVM_GET_MEMORY16(interrupt, TLVM_6800_INT_NMI);
        addr = interrupt;
        willInterrupt = TLVM_TRUE;
    }
    else if(interrupt == TLVM_INTERRUPT_IRQ)
    {
        if(context->m_Interrupts != TLVM_INTERRUPT_NMI &&
           TLVM_FLAG_ISSET(I, 6800))
        {
            TLVM_GET_MEMORY16(interrupt, TLVM_6800_INT_IRQ);
            addr = interrupt;
            willInterrupt = TLVM_TRUE;
        }
    }

    
    if(willInterrupt)
    {
        if(context->m_Interrupts == TLVM_INTERRUPT_NONE)
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
