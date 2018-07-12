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

TLVM_6800_INSTRUCTION(JSR_I, 8, 0,
{
    context->m_ProgramCounter += 2;

    TLVM_6800_GET_ADDR_INDEXED(addr);
    TLVM_PUSH_PC(addr);
})

TLVM_6800_INSTRUCTION(JSR_E, 8, 0,
{
    context->m_ProgramCounter += 3;

    TLVM_6800_GET_ADDR_EXTENDED(addr);    
    TLVM_PUSH_PC(addr);
})

#endif/*TLVM_HAS_6800*/
