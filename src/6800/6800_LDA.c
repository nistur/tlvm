/*
Copyright (c) 2018 Philipp Geyer

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

TLVM_6800_INSTRUCTION(LDA_I_A, 2, 2,
{
    TLVM_GET_OP(op1, 1);
    TLVM_REGISTER(TLVM_6800_REG_A) = (tlvmShort)op1;
})

TLVM_6800_INSTRUCTION(LDA_D_A, 2, 2,
{
    TLVM_GET_OP(op1, 1);
    TLVM_GET_MEMORY(mem, op1);
    TLVM_REGISTER(TLVM_6800_REG_A) = (tlvmShort)mem;
})

TLVM_6800_INSTRUCTION(LDA_X_A, 2, 2,
{
    TLVM_6800_GET_MEM_INDEXED(mem);
    TLVM_REGISTER(TLVM_6800_REG_A) = (tlvmShort)*mem;
})

TLVM_6800_INSTRUCTION(LDA_E_A, 2, 2,
{
    TLVM_6800_GET_MEM_EXTENDED(mem);
    TLVM_REGISTER(TLVM_6800_REG_A) = (tlvmShort)*mem;
})

TLVM_6800_INSTRUCTION(LDA_I_B, 2, 2,
{
    TLVM_GET_OP(op1, 1);
    TLVM_REGISTER(TLVM_6800_REG_B) = (tlvmShort)op1;
})

TLVM_6800_INSTRUCTION(LDA_D_B, 2, 2,
{
    TLVM_GET_OP(op1, 1);
    TLVM_GET_MEMORY(mem, op1);
    TLVM_REGISTER(TLVM_6800_REG_B) = (tlvmShort)mem;
})

TLVM_6800_INSTRUCTION(LDA_X_B, 2, 2,
{
    TLVM_6800_GET_MEM_INDEXED(mem);
    TLVM_REGISTER(TLVM_6800_REG_B) = (tlvmShort)*mem;
})

TLVM_6800_INSTRUCTION(LDA_E_B, 2, 2,
{
    TLVM_6800_GET_MEM_EXTENDED(mem);
    TLVM_REGISTER(TLVM_6800_REG_B) = (tlvmShort)*mem;
})


#endif/*TLVM_HAS_6800*/
