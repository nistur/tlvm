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

tlvmReturn tlvm6800SUB(tlvmContext* context, tlvmByte* cycles)
{
    TLVM_NULL_CHECK(context, NO_CONTEXT);

    context->m_ProgramCounter += 1;

    TLVM_GET_OP(opcode, 0);

    tlvmShort val = 0;
    if(opcode == TLVM_6800_SBA)
    {
        val = (tlvmShort)TLVM_REGISTER(TLVM_6800_REG_A) - (tlvmShort)TLVM_REGISTER(TLVM_6800_REG_B);
        TLVM_REGISTER(TLVM_6800_REG_A) = (tlvmByte)val;
    }

    TLVM_FLAG_SET_IF(val&0x00FF, Z, 6800);
    TLVM_FLAG_SET_IF(val&0xFF00, C, 6800);
    TLVM_FLAG_SET_IF(val&0xFF00, V, 6800);
    TLVM_FLAG_SET_IF(val&0x0080, N, 6800);
    
    if(cycles)
        *cycles = 2;

    TLVM_RETURN_CODE(SUCCESS);
}

#endif/*TLVM_HAS_6800*/
