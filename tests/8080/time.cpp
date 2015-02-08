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

TEST(SetClockspeed, Time, 0.0f,
     // initialisation
     {
      tlvmInitContext(&m_data.context);
     },
     // cleanup
     {
      tlvmTerminateContext(&m_data.context);
     },
     // test
     {
          ASSERT(tlvmSetClockspeed(m_data.context, TLVM_MHZ(2,0)) == TLVM_SUCCESS);
          ASSERT(m_data.context->m_Clockspeed == TLVM_MHZ(2, 0));
     },
     // data
     {
      tlvmContext* context;
     }
    );

TEST(Time, Time, 0.0f,
     // initialisation
     {
      m_data.memory[0] = TLVM_NOP;
      m_data.memory[1] = TLVM_HLT;

      tlvmInitContext(&m_data.context);
      tlvm8080Init(m_data.context);
      tlvmSetClockspeed(m_data.context, TLVM_MHZ(2,0));
      tlvmSetMemory(m_data.context, m_data.memory, 0, 256, TLVM_FLAG_READ);
     },
     // cleanup
     {
      tlvmTerminateContext(&m_data.context);
     },
     // test
     {
      // Um. This should really test how long it takes to run some random program with known execution time
      tlvmRun(m_data.context);
     },
     // data
     {
      tlvmContext* context;
      tlvmByte     memory[256];
     }
    );