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

#define FLAG(x) ( TLVM_FLAG_ISSET(x, 6800) ? TLVM_TRUE : TLVM_FALSE )

#define BRANCH_BASE()			\
    TLVM_GET_OP(opcode, 0);		\
    TLVM_GET_OP(address, 1);		\
    context->m_ProgramCounter += 2;


TLVM_6800_INSTRUCTION(BRA, 4, 0,
{
    BRANCH_BASE();
    
    context->m_ProgramCounter += (tlvmSByte)address;
})

TLVM_6800_INSTRUCTION(BHI, 4, 0,
{
    BRANCH_BASE();
    
    if( OR( FLAG(C), !FLAG(V) ) )
    {
	context->m_ProgramCounter += (tlvmSByte)address;
    }
})

TLVM_6800_INSTRUCTION(BLS, 4, 0,
{
    BRANCH_BASE();
    
    if( OR( FLAG(C), FLAG(V) ) )
    {
	context->m_ProgramCounter += (tlvmSByte)address;
    }
})

TLVM_6800_INSTRUCTION(BCS, 4, 0,
{
    BRANCH_BASE();
    
    if( FLAG(C) )
    {
	context->m_ProgramCounter += (tlvmSByte)address;
    }
})

TLVM_6800_INSTRUCTION(BCC, 4, 0,
{
    BRANCH_BASE();
    
    if( !FLAG(C) )
    {
	context->m_ProgramCounter += (tlvmSByte)address;
    }
})

TLVM_6800_INSTRUCTION(BNE, 4, 0,
{
    BRANCH_BASE();
    
    if( !FLAG(Z) )
    {
	context->m_ProgramCounter += (tlvmSByte)address;
    }
})

TLVM_6800_INSTRUCTION(BEQ, 4, 0,
{
    BRANCH_BASE();
    
    if( FLAG(Z) )
    {
	context->m_ProgramCounter += (tlvmSByte)address;
    }
})

TLVM_6800_INSTRUCTION(BVC, 4, 0,
{
    BRANCH_BASE();
    
    if( !FLAG(V) )
    {
	context->m_ProgramCounter += (tlvmSByte)address;
    }
})

TLVM_6800_INSTRUCTION(BVS, 4, 0,
{
    BRANCH_BASE();
    
    if( FLAG(Z) )
    {
	context->m_ProgramCounter += (tlvmSByte)address;
    }
})

TLVM_6800_INSTRUCTION(BPL, 4, 0,
{
    BRANCH_BASE();
    
    if( !FLAG(N) )
    {
	context->m_ProgramCounter += (tlvmSByte)address;
    }
})

TLVM_6800_INSTRUCTION(BMI, 4, 0,
{
    BRANCH_BASE();
    
    if( FLAG(N) )
    {
	context->m_ProgramCounter += (tlvmSByte)address;
    }
})

TLVM_6800_INSTRUCTION(BGE,4, 0,
{
    BRANCH_BASE();
    
    if( !XOR( FLAG(N), FLAG(V) ) )
    {
	context->m_ProgramCounter += (tlvmSByte)address;
    }
})

TLVM_6800_INSTRUCTION(BLT, 4, 0,
{
    BRANCH_BASE();
    
    if( XOR( FLAG(N), FLAG(V) ) )
    {
	context->m_ProgramCounter += (tlvmSByte)address;
    }
})

TLVM_6800_INSTRUCTION(BGT, 4, 0,
{
    BRANCH_BASE();
    
    if( OR(FLAG(Z), XOR( FLAG(N), FLAG(V) ) ) )
    {
	context->m_ProgramCounter += (tlvmSByte)address;
    }
})

TLVM_6800_INSTRUCTION(BLE, 4, 0,
{
    BRANCH_BASE();
    
    if( !OR( FLAG(Z), XOR( FLAG(N), FLAG(V) ) ) )
    {
	context->m_ProgramCounter += (tlvmSByte)address;
    }
})

#endif/*TLVM_HAS_6800*/
