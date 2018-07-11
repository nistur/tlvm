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

TLVM_6800_INSTRUCTION(CMP, 2, 2,
{
    TLVM_GET_OP(opcode, 0);
    TLVM_GET_OP(op1, 1);
    
    tlvmShort val = (tlvmShort)TLVM_REGISTER( (opcode & 0x40) == 0x00 ? TLVM_6800_REG_A : TLVM_6800_REG_B );
    tlvmByte imm = (opcode & 0x30) == 0x00;
    tlvmByte dir = (opcode & 0x30) == 0x10;
    tlvmByte idx = (opcode & 0x30) == 0x20;
    tlvmByte ext = (opcode & 0x30) == 0x30;

    if( !imm )
    {
	tlvmShort addr = 0;

	if(idx)
	{
	    TLVM_6800_GET_ADDR_INDEXED(val);
	    addr = val;
	}
	else if(dir)
	{
	    addr = op1;
	}
	else if(ext)
	{
	    context->m_ProgramCounter += 1;
	    
	    TLVM_GET_OP(msb, 2);
	    addr = (tlvmShort)(op1) | (tlvmShort)(msb << 8);
	}
	
	TLVM_GET_MEMORY(mem, addr);
	op1 = mem;

	
    }
    
    val = val - op1;

    TLVM_FLAG_SET_IF(val&0x00FF, Z, 6800);
    TLVM_FLAG_SET_IF(val&0xFF00, C, 6800);
    TLVM_FLAG_SET_IF(val&0xFF00, V, 6800);
    TLVM_FLAG_SET_IF(val&0x0080, N, 6800);
})

#endif/*TLVM_HAS_6800*/
