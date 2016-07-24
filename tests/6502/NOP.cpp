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

TEST(InstNOP, CPU_6502, 0.0f,
     // initialisation
     {
      tlvmInitContext(&m_data.context, TLVM_CPU_6502);
      tlvmSetMemory(m_data.context, m_data.bootloader, 0, 1, TLVM_FLAG_READ);
      m_data.bootloader[0] = TLVM_6502_NOP;
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
          ASSERT(cycle == 2);
          ASSERT(m_data.context->m_Registers[TLVM_6502_REG_F] == 0);     // check that no flags have 
                                                                    // been affected
     },
     // data
     {
      tlvmContext* context;
      tlvmByte     bootloader[1];
     }
    );


TEST(InstBRK, CPU_6502, 0.0f,
     // initialisation
     {
      tlvmInitContext(&m_data.context, TLVM_CPU_6502);
      tlvmSetMemory(m_data.context, m_data.bootloader, 0, 2, TLVM_FLAG_READ);
      tlvmSetMemory(m_data.context, m_data.interrupts, 0xFFF0, 0x0010, TLVM_FLAG_READ);
      m_data.bootloader[0x0] = TLVM_6502_BRK;
      m_data.interrupts[0xE] = 0x34;
      m_data.interrupts[0xF] = 0x12;
     },
     // cleanup
     {
      tlvmTerminateContext(&m_data.context);
     },
     // test
     {
          tlvmContext* context = m_data.context;

          // reload the program so each time we start from 0x0
          tlvmReset(m_data.context);
          tlvmByte cycle = 0;
          ASSERT(tlvmStep(m_data.context, &cycle) == TLVM_SUCCESS); // run the first instruction
          ASSERT(cycle == 7);
          ASSERT(TLVM_FLAG_ISSET(B, 6502));     // check that the B flag is set
          ASSERT(m_data.context->m_ProgramCounter == 0x1234);
     },
     // data
     {
      tlvmContext* context;
      tlvmByte     bootloader[2];
      tlvmByte     interrupts[0x10];
     }
    );


TEST(InstRTI, CPU_6502, 0.0f,
     // initialisation
     {
      tlvmInitContext(&m_data.context, TLVM_CPU_6502);
      tlvmSetMemory(m_data.context, m_data.bootloader, 0x0000, 0x0002, TLVM_FLAG_READ);
      tlvmSetMemory(m_data.context, m_data.interrupts, 0xFFF0, 0x0010, TLVM_FLAG_READ);
      tlvmSetMemory(m_data.context, m_data.interrupt,  0x1234, 0x0001, TLVM_FLAG_READ);
      m_data.bootloader[0x0] = TLVM_6502_BRK;
      m_data.interrupts[0xE] = 0x34;
      m_data.interrupts[0xF] = 0x12;
      m_data.interrupt[0x0] = TLVM_6502_RTI;
     },
     // cleanup
     {
      tlvmTerminateContext(&m_data.context);
     },
     // test
     {
          tlvmContext* context = m_data.context;

          // reload the program so each time we start from 0x0
          tlvmReset(m_data.context);
          tlvmByte cycle = 0;
          TLVM_REGISTER(TLVM_6502_REG_F) = 0x87; 
          tlvmStep(m_data.context, &cycle);

          TLVM_REGISTER(TLVM_6502_REG_F) = 0x00;
          cycle = 0;

          ASSERT(tlvmStep(m_data.context, &cycle) == TLVM_SUCCESS);
          ASSERT(cycle == 6);
          ASSERT(TLVM_REGISTER(TLVM_6502_REG_F) == 0x87);
          ASSERT(m_data.context->m_ProgramCounter == 0x0002);
     },
     // data
     {
      tlvmContext* context;
      tlvmByte     bootloader[2];
      tlvmByte     interrupts[0x10];
      tlvmByte     interrupt[1];
     }
    );
