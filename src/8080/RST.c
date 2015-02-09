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

tlvmReturn tlvmRST(tlvmContext* context, tlvmByte* cycles)
{
    if(context == NULL)
        TLVM_RETURN_CODE(NO_CONTEXT);

    TLVM_GET_OP(opcode, 0);

    // increment the program counter first so if/when we return,
    // we don't hit the interrupt again
    // size of instruction    = 1
    context->m_ProgramCounter += 1;

    // push the program counter
    tlvmByte pcLo = (tlvmByte)(context->m_ProgramCounter & 0xFF);
    tlvmByte pcHi = (tlvmByte)(context->m_ProgramCounter >> 8);

    TLVM_STACK_PUSH(pcHi);
    TLVM_STACK_PUSH(pcLo);

    // which interrupt are we hitting?
    tlvmShort addr = 0x08;
    switch(opcode)
    {
    case TLVM_RST_0:
        addr *= 0;
    break;
    case TLVM_RST_1:
        addr *= 1;
    break;
    case TLVM_RST_2:
        addr *= 2;
    break;
    case TLVM_RST_3:
        addr *= 3;
    break;
    case TLVM_RST_4:
        addr *= 4;
    break;
    case TLVM_RST_5:
        addr *= 5;
    break;
    case TLVM_RST_6:
        addr *= 6;
    break;
    case TLVM_RST_7:
        addr *= 7;
    break;
    }

    context->m_ProgramCounter = addr;
    if(cycles)
        *cycles =11;

    TLVM_RETURN_CODE(SUCCESS);
}

tlvmReturn tlvmEI(tlvmContext* context, tlvmByte* cycles)
{
    if(context == NULL)
        TLVM_RETURN_CODE(NO_CONTEXT);

    TLVM_FLAG_SET(I);
    if(context->m_Registers[TLVM_REG_I])
        tlvm8080HandleInterrupt(context, context->m_Registers[TLVM_REG_I]);
    context->m_Registers[TLVM_REG_I] = 0x00;
    // size of instruction    = 1
    context->m_ProgramCounter += 1;
    if(cycles)
        *cycles =4;

    TLVM_RETURN_CODE(SUCCESS);
}

tlvmReturn tlvmDI(tlvmContext* context, tlvmByte* cycles)
{
    if(context == NULL)
        TLVM_RETURN_CODE(NO_CONTEXT);

    TLVM_FLAG_UNSET(I);
    // size of instruction    = 1
    context->m_ProgramCounter += 1;
    if(cycles)
        *cycles =4;

    TLVM_RETURN_CODE(SUCCESS);
}
#endif/*TLVM_HAS_8080*/