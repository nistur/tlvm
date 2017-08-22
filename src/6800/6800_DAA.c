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

tlvmReturn tlvm6800DAA(tlvmContext* context, tlvmByte* cycles)
{
    TLVM_NULL_CHECK(context, NO_CONTEXT);

    context->m_ProgramCounter += 1;

    tlvmShort val = (tlvmShort)TLVM_REGISTER(TLVM_6800_REG_A);;

    tlvmByte nibbleLo = val & 0x0F;
    tlvmByte nibbleHi = (val & 0xF0)>>4;

    if(nibbleLo>0x09 || TLVM_FLAG_ISSET(H, 6800))
    {
        nibbleLo += 0x06;
        TLVM_FLAG_SET_IF(nibbleLo & 0xF0, H, 6800);
        if(TLVM_FLAG_ISSET(H, 6800))
            nibbleHi += 0x01;
    }
    if(nibbleHi>0x09 || TLVM_FLAG_ISSET(C, 6800))
    {
        nibbleHi += 0x06;
    }
    val = ((nibbleHi & 0x0F)<<4) | (nibbleLo & 0x0F);

    TLVM_FLAG_SET_IF(val&0x00FF, Z, 6800);
    TLVM_FLAG_SET_IF(val&0xFF00, V, 6800);
    TLVM_FLAG_SET_IF(val&0x0080, N, 6800);
    TLVM_FLAG_SET_IF(nibbleHi & 0xF0, C, 6800);

    
    TLVM_REGISTER(TLVM_6800_REG_A) = (tlvmByte)(val & 0xFF);
    
    if(cycles)
        *cycles = 2;

    TLVM_RETURN_CODE(SUCCESS);
}

#endif/*TLVM_HAS_6800*/
