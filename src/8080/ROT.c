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

tlvmReturn tlvmROT(tlvmContext* context, tlvmByte* cycles)
{
    TLVM_NULL_CHECK(context, NO_CONTEXT);
    TLVM_GET_OP(operand,0);
    
    tlvmShort acc = (tlvmShort)context->m_Registers[TLVM_REG_A];

    if(operand == TLVM_RLC)
    {
        acc <<= 1;
        if(acc & (1<<8))
        {
            acc |= 1;
            TLVM_FLAG_SET(C, 8080);
        }
        else
        {
            TLVM_FLAG_UNSET(C, 8080);
        }
    }
    else if(operand == TLVM_RRC)
    {
        if(acc & 1)
        {
            acc |= 1<<8;
            TLVM_FLAG_SET(C, 8080);
        }
        else
        {
            TLVM_FLAG_UNSET(C, 8080);
        }
        acc >>= 1;
    }
    else if(operand == TLVM_RAL)
    {
        acc <<= 1;
        if(TLVM_FLAG_ISSET(C, 8080))
            acc |= 1;
        TLVM_FLAG_SET_IF(acc > 0xFF, C, 8080);
    }
    else if(operand == TLVM_RAR)
    {
        if(TLVM_FLAG_ISSET(C, 8080))
            acc |= 1<<8;
        TLVM_FLAG_SET_IF(acc & 1, C, 8080);
        acc >>= 1;
    }

    context->m_Registers[TLVM_REG_A] = (tlvmByte)(acc & 0xFF);

    // size of instruction = 1
    context->m_ProgramCounter += 1;
    if(cycles)
        *cycles = 4;
    TLVM_RETURN_CODE(SUCCESS);
}

#endif/*TLVM_HAS_8080*/
