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

#define XOR(a,b) ((a && !b) || (!a && b))
#define OR(a,b)  (a || b)
#define AND(a,b) (a && b)

tlvmReturn tlvm6800BRA(tlvmContext* context, tlvmByte* cycles)
{
    TLVM_NULL_CHECK(context, NO_CONTEXT);

    TLVM_GET_OP(opcode, 0);
    TLVM_GET_OP(address, 1);
    
    context->m_ProgramCounter += 2;

    tlvmBool z = TLVM_FLAG_ISSET(Z, 6800) ? TLVM_TRUE : TLVM_FALSE;
    tlvmBool n = TLVM_FLAG_ISSET(N, 6800) ? TLVM_TRUE : TLVM_FALSE;
    tlvmBool v = TLVM_FLAG_ISSET(V, 6800) ? TLVM_TRUE : TLVM_FALSE;
    tlvmBool c = TLVM_FLAG_ISSET(C, 6800) ? TLVM_TRUE : TLVM_FALSE;

    if(opcode == TLVM_6800_BRA)
    {
        context->m_ProgramCounter += (tlvmSByte)address;
    }
    else if(opcode == TLVM_6800_BHI)
    {
        if(OR(c, !v))
            context->m_ProgramCounter += (tlvmSByte)address;
    }
    else if(opcode == TLVM_6800_BLS)
    {
        if(OR(c,v))
            context->m_ProgramCounter += (tlvmSByte)address;
    }
    else if(opcode == TLVM_6800_BCC)
    {
        if(!c)
            context->m_ProgramCounter += (tlvmSByte)address;
    }
    else if(opcode == TLVM_6800_BNE)
    {
        if(!z)
            context->m_ProgramCounter += (tlvmSByte)address;
    }
    else if(opcode == TLVM_6800_BEQ)
    {
        if(z)
            context->m_ProgramCounter += (tlvmSByte)address;
    }
    else if(opcode == TLVM_6800_BVC)
    {
        if(!v)
            context->m_ProgramCounter += (tlvmSByte)address;
    }
    else if(opcode == TLVM_6800_BVS)
    {
        if(v)
            context->m_ProgramCounter += (tlvmSByte)address;
    }
    else if(opcode == TLVM_6800_BPL)
    {
        if(!n)
            context->m_ProgramCounter += (tlvmSByte)address;
    }
    else if(opcode == TLVM_6800_BMI)
    {
        if(n)
            context->m_ProgramCounter += (tlvmSByte)address;
    }
    else if(opcode == TLVM_6800_BGE)
    {
        if(!XOR(n,v))
            context->m_ProgramCounter += (tlvmSByte)address;
    }
    else if(opcode == TLVM_6800_BLT)
    {
        if(XOR(n,v))
            context->m_ProgramCounter += (tlvmSByte)address;
    }
    else if(opcode == TLVM_6800_BGT)
    {
        if(OR(z, XOR(n,v)))
            context->m_ProgramCounter += (tlvmSByte)address;
    }
    else if(opcode == TLVM_6800_BLE)
    {
        if(!OR(z, XOR(n,v)))
            context->m_ProgramCounter += (tlvmSByte)address;
    }


    if(cycles)
        *cycles = 4;

    TLVM_RETURN_CODE(SUCCESS);
}

#endif/*TLVM_HAS_6800*/
