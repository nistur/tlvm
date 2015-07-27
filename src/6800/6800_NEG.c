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

tlvmReturn tlvm6800NEG(tlvmContext* context, tlvmByte* cycles)
{
    TLVM_NULL_CHECK(context, NO_CONTEXT);

    TLVM_GET_OP(opcode, 0);

    tlvmShort val = 0;
    tlvmByte length = 1;
    tlvmByte count = 2;
    if(opcode == TLVM_6800_NEGA)
    {
        val = -(tlvmShort)TLVM_REGISTER(TLVM_6800_REG_A);
        TLVM_REGISTER(TLVM_6800_REG_A) = (tlvmByte)val & 0xFF;
    }
    else if(opcode == TLVM_6800_NEGB)
    {
        val = -(tlvmShort)TLVM_REGISTER(TLVM_6800_REG_B);
        TLVM_REGISTER(TLVM_6800_REG_B) = (tlvmByte)val & 0xFF;
    }
    else if(opcode == TLVM_6800_NEGX)
    {
        TLVM_6800_GET_ADDR_EXTENDED(addr);
        tlvmByte* mem = tlvmGetMemory(context, addr, TLVM_FLAG_READ);
        if(mem != 0)
        {
            val = -(tlvmShort)*mem;
            *mem = (tlvmByte)val & 0xFF;
        }
        length = 3;
        count = 6;
    }
    else if(opcode == TLVM_6800_NEGE)
    {
        TLVM_6800_GET_ADDR_INDEXED(addr);
        tlvmByte* mem = tlvmGetMemory(context, addr, TLVM_FLAG_READ);
        if(mem != 0)
        {
            val = -(tlvmShort)*mem;
            *mem = (tlvmByte)val & 0xFF;
        }
        length = 1;
        count = 7;
    }

    TLVM_FLAG_SET_IF(val &  0x0080, N, 6800);
    TLVM_FLAG_SET_IF(val == 0x0000, Z, 6800);
    TLVM_FLAG_SET_IF(val &  0xFF00, C, 6800);
    TLVM_FLAG_SET(V, 6800); // I'm not sure about this... but I think this should always be true here?

    context->m_ProgramCounter += length;

    if(cycles)
        *cycles = count;

    TLVM_RETURN_CODE(SUCCESS);
}

#endif/*TLVM_HAS_6800*/
