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

#define SET_FLAGS(_val)				\
TLVM_FLAG_SET_IF(_val &  0x0080, N, 6800);	\
TLVM_FLAG_SET_IF(_val == 0x0000, Z, 6800);	\
TLVM_FLAG_SET_IF(_val &  0xFF00, C, 6800);	\
TLVM_FLAG_SET(V, 6800); 

TLVM_6800_INSTRUCTION(NEG_A, 2, 1,
{
    tlvmShort val = -(tlvmShort)TLVM_REGISTER(TLVM_6800_REG_A);
    TLVM_REGISTER(TLVM_6800_REG_A) = (tlvmByte)val & 0xFF;

    SET_FLAGS(val);
})

TLVM_6800_INSTRUCTION(NEG_B, 2, 1,
{
    tlvmShort val = -(tlvmShort)TLVM_REGISTER(TLVM_6800_REG_B);
    TLVM_REGISTER(TLVM_6800_REG_B) = (tlvmByte)val & 0xFF;

    SET_FLAGS(val);
})

TLVM_6800_INSTRUCTION(NEG_X, 2, 2,
{
    tlvmShort val = 0;
    TLVM_6800_GET_MEM_EXTENDED(mem);
    val = -(tlvmShort)*mem;
    *mem = (tlvmByte)val & 0xFF;
    
    SET_FLAGS(val);
})

TLVM_6800_INSTRUCTION(NEG_E, 2, 3,
{
    tlvmShort val = 0;
    TLVM_6800_GET_MEM_EXTENDED(mem);
    val = -(tlvmShort)*mem;
    *mem = (tlvmByte)val & 0xFF;
    
    SET_FLAGS(val);
})

#endif/*TLVM_HAS_6800*/
