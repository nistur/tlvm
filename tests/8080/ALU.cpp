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

#include "../tlvm-tests.h"
#ifdef TLVM_HAS_8080

TEST(ADI, ALU, 0.0f,
     // initialisation
     {
      tlvmInitContext(&m_data.context, TLVM_CPU_8080);
      tlvmSetMemory(m_data.context, m_data.bootloader, 0, 255, TLVM_FLAG_READ);
      m_data.bootloader[0] = TLVM_ADI;
      m_data.bootloader[1] = 99;
     },
     // cleanup
     {
      tlvmTerminateContext(&m_data.context);
     },
     // test
     {
          // reload the program so each time we start from 0x0
          tlvmReset(m_data.context);
          tlvmByte cycle = 0;
          ASSERT(tlvmStep(m_data.context, &cycle) == TLVM_SUCCESS); // run the first instruction
          ASSERT(cycle == 7);
     },
     // data
     {
      tlvmContext* context;
      tlvmByte     bootloader[255];
     }
    );
#endif/*TLVM_HAS_8080*/
