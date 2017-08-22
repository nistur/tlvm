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

tlvmReturn tlvm6800TRA(tlvmContext* context, tlvmByte* cycles)
{
    TLVM_NULL_CHECK(context, NO_CONTEXT);

    TLVM_GET_OP(opcode, 0);

    if(opcode == TLVM_6800_TAP)
        TLVM_REGISTER(TLVM_6800_REG_F) = TLVM_REGISTER(TLVM_6800_REG_A);
    else if(opcode == TLVM_6800_TPA)
        TLVM_REGISTER(TLVM_6800_REG_A) = TLVM_REGISTER(TLVM_6800_REG_F);
    else if(opcode == TLVM_6800_TSX)
        TLVM_REGISTER16(TLVM_6800_REG16_IX) = context->m_StackPointer;
    else if(opcode == TLVM_6800_TXS)
        context->m_StackPointer = TLVM_REGISTER16(TLVM_6800_REG16_IX);

    context->m_ProgramCounter += 1;

    if(cycles)
        *cycles = 2;

    TLVM_RETURN_CODE(SUCCESS);
}

#endif/*TLVM_HAS_6800*/
