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

TEST(InitTerminate, Basic, 0.0f,
     // initialisation
     {
      m_data.context = 0;
     },
     // cleanup
     {
      tlvmTerminateContext(&m_data.context);
     },
     // test
     {
      ASSERT(tlvmInitContext(&m_data.context, TLVM_CPU_8080) == TLVM_SUCCESS);
      ASSERT(m_data.context != NULL);
      ASSERT(tlvmTerminateContext(&m_data.context) == TLVM_SUCCESS);
     },
     // data
     {
      tlvmContext* context;
     }
    );

TEST(SetMemory, Basic, 0.0f,
     // initialisation
     {
      tlvmInitContext(&m_data.context, TLVM_CPU_8080);
     },
     // cleanup
     {
      tlvmTerminateContext(&m_data.context);
     },
     // test
     {
          // no context
          ASSERT(tlvmSetMemory(NULL, m_data.memory, 0, 255, TLVM_FLAG_READ | TLVM_FLAG_WRITE) == TLVM_NO_CONTEXT);

          // no buffer
          ASSERT(tlvmSetMemory(m_data.context, NULL, 0, 255, TLVM_FLAG_READ | TLVM_FLAG_WRITE) == TLVM_NO_MEMORY);

          // zero size
          ASSERT(tlvmSetMemory(m_data.context, m_data.memory, 0, 0, TLVM_FLAG_READ | TLVM_FLAG_WRITE) == TLVM_INVALID_INPUT);

          // valid input
          ASSERT(tlvmSetMemory(m_data.context, m_data.memory, 0, 255, TLVM_FLAG_READ | TLVM_FLAG_WRITE) == TLVM_SUCCESS);

          // unset
          ASSERT(tlvmUnsetMemory(m_data.context, m_data.memory) == TLVM_SUCCESS);
      
     },
     // data
     {
      tlvmContext* context;
      tlvmByte     memory[255];
     }
    );

TEST(InstructionSet, Basic, 0.0f,
     // initialisation
     {
      tlvmInitContext(&m_data.context, TLVM_CPU_8080);
      memset(m_data.nullInstructions, 0, 256);

      m_data.nullInstructions[0x08] = 1;
      m_data.nullInstructions[0x10] = 1;
      m_data.nullInstructions[0x18] = 1;
      m_data.nullInstructions[0x20] = 1;
      m_data.nullInstructions[0x28] = 1;
      m_data.nullInstructions[0x30] = 1;
      m_data.nullInstructions[0x38] = 1;
      m_data.nullInstructions[0xCB] = 1;
      m_data.nullInstructions[0xD9] = 1;
      m_data.nullInstructions[0xDD] = 1;
      m_data.nullInstructions[0xED] = 1;
      m_data.nullInstructions[0xFD] = 1;
     },
     // cleanup
     {
      tlvmTerminateContext(&m_data.context);
     },
     // test
     {
        for(unsigned int i = 0; i < 256; ++i)
          if(m_data.nullInstructions[i] == 0)
            ASSERT(((_tlvmContext*)m_data.context)->m_InstructionSet[i] != NULL);
     },
     // data
     {
      tlvmContext* context;
      tlvmByte nullInstructions[256];
     }
    );

TEST(SetClockspeed, Basic, 0.0f,
     // initialisation
     {
      tlvmInitContext(&m_data.context, TLVM_CPU_8080);
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