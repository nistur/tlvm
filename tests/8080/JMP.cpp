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

TEST(Instructions, JMP, 0.0f,
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
          // reload the program so each time we start from 0x0
          tlvmReset(m_data.context);

          ASSERT(m_data.context->m_InstructionSet[TLVM_JMP] == tlvmJMP);
          ASSERT(m_data.context->m_InstructionSet[TLVM_JNZ] == tlvmJMP);
          ASSERT(m_data.context->m_InstructionSet[TLVM_JZ]  == tlvmJMP);
          ASSERT(m_data.context->m_InstructionSet[TLVM_JNC] == tlvmJMP);
          ASSERT(m_data.context->m_InstructionSet[TLVM_JPO] == tlvmJMP);
          ASSERT(m_data.context->m_InstructionSet[TLVM_JPE] == tlvmJMP);
          ASSERT(m_data.context->m_InstructionSet[TLVM_JP]  == tlvmJMP);
          ASSERT(m_data.context->m_InstructionSet[TLVM_JM]  == tlvmJMP);
     },
     // data
     {
      tlvmContext* context;
     }
    );

TEST(JMP, JMP, 0.0f,
     // initialisation
     {
      tlvmInitContext(&m_data.context, TLVM_CPU_8080);
      tlvmSetMemory(m_data.context, m_data.bootloader, 0, 0xFF, TLVM_FLAG_READ);

      m_data.bootloader[0x00] = TLVM_JMP;
      m_data.bootloader[0x01] = 0x00;
      m_data.bootloader[0x02] = 0x00; // just jump to beginning
     },
     // cleanup
     {
      tlvmTerminateContext(&m_data.context);
     },
     // test
     {
          // reload the program so each time we start from 0x0
          tlvmReset(m_data.context);

          tlvmByte cycles = 0;
          ASSERT(tlvmStep(m_data.context, &cycles) == TLVM_SUCCESS);
          ASSERT(cycles == 10);
          ASSERT(m_data.context->m_ProgramCounter == 0x0000);
     },
     // data
     {
      tlvmContext* context;
      tlvmByte     bootloader[255];
     }
    );

TEST(JNZ, JMP, 0.0f,
     // initialisation
     {
      tlvmInitContext(&m_data.context, TLVM_CPU_8080);
      tlvmSetMemory(m_data.context, m_data.bootloader, 0, 0xFF, TLVM_FLAG_READ);

      m_data.bootloader[0x00] = TLVM_JNZ;
      m_data.bootloader[0x01] = 0x00;
      m_data.bootloader[0x02] = 0x00; // just jump to beginning
     },
     // cleanup
     {
      tlvmTerminateContext(&m_data.context);
     },
     // test
     {
          // use local variable so we can use macros
          tlvmContext* context = m_data.context;

          // reload the program so each time we start from 0x0
          tlvmReset(m_data.context);

          tlvmByte cycles = 0;
          TLVM_FLAG_UNSET(Z, 8080);
          ASSERT(tlvmStep(m_data.context, &cycles) == TLVM_SUCCESS);
          ASSERT(cycles == 10);
          ASSERT(m_data.context->m_ProgramCounter == 0x0000);

          cycles = 0;
          TLVM_FLAG_SET(Z, 8080);
          ASSERT(tlvmStep(m_data.context, &cycles) == TLVM_SUCCESS);
          ASSERT(cycles == 10);
          ASSERT(m_data.context->m_ProgramCounter == 0x0003);
     },
     // data
     {
      tlvmContext* context;
      tlvmByte     bootloader[255];
     }
    );

TEST(JZ, JMP, 0.0f,
     // initialisation
     {
      tlvmInitContext(&m_data.context, TLVM_CPU_8080);
      tlvmSetMemory(m_data.context, m_data.bootloader, 0, 0xFF, TLVM_FLAG_READ);

      m_data.bootloader[0x00] = TLVM_JZ;
      m_data.bootloader[0x01] = 0x00;
      m_data.bootloader[0x02] = 0x00; // just jump to beginning
     },
     // cleanup
     {
      tlvmTerminateContext(&m_data.context);
     },
     // test
     {
          // use local variable so we can use macros
          tlvmContext* context = m_data.context;

          // reload the program so each time we start from 0x0
          tlvmReset(m_data.context);

          tlvmByte cycles = 0;
          TLVM_FLAG_SET(Z, 8080);
          ASSERT(tlvmStep(m_data.context, &cycles) == TLVM_SUCCESS);
          ASSERT(cycles == 10);
          ASSERT(m_data.context->m_ProgramCounter == 0x0000);

          cycles = 0;
          TLVM_FLAG_UNSET(Z, 8080);
          ASSERT(tlvmStep(m_data.context, &cycles) == TLVM_SUCCESS);
          ASSERT(cycles == 10);
          ASSERT(m_data.context->m_ProgramCounter == 0x0003);
     },
     // data
     {
      tlvmContext* context;
      tlvmByte     bootloader[255];
     }
    );

TEST(JNC, JMP, 0.0f,
     // initialisation
     {
      tlvmInitContext(&m_data.context, TLVM_CPU_8080);
      tlvmSetMemory(m_data.context, m_data.bootloader, 0, 0xFF, TLVM_FLAG_READ);

      m_data.bootloader[0x00] = TLVM_JNC;
      m_data.bootloader[0x01] = 0x00;
      m_data.bootloader[0x02] = 0x00; // just jump to beginning
     },
     // cleanup
     {
      tlvmTerminateContext(&m_data.context);
     },
     // test
     {
          // use local variable so we can use macros
          tlvmContext* context = m_data.context;

          // reload the program so each time we start from 0x0
          tlvmReset(m_data.context);

          tlvmByte cycles = 0;
          TLVM_FLAG_UNSET(C, 8080);
          ASSERT(tlvmStep(m_data.context, &cycles) == TLVM_SUCCESS);
          ASSERT(cycles == 10);
          ASSERT(m_data.context->m_ProgramCounter == 0x0000);

          cycles = 0;
          TLVM_FLAG_SET(C, 8080);
          ASSERT(tlvmStep(m_data.context, &cycles) == TLVM_SUCCESS);
          ASSERT(cycles == 10);
          ASSERT(m_data.context->m_ProgramCounter == 0x0003);
     },
     // data
     {
      tlvmContext* context;
      tlvmByte     bootloader[255];
     }
    );

TEST(JC, JMP, 0.0f,
     // initialisation
     {
      tlvmInitContext(&m_data.context, TLVM_CPU_8080);
      tlvmSetMemory(m_data.context, m_data.bootloader, 0, 0xFF, TLVM_FLAG_READ);

      m_data.bootloader[0x00] = TLVM_JC;
      m_data.bootloader[0x01] = 0x00;
      m_data.bootloader[0x02] = 0x00; // just jump to beginning
     },
     // cleanup
     {
      tlvmTerminateContext(&m_data.context);
     },
     // test
     {
          // use local variable so we can use macros
          tlvmContext* context = m_data.context;

          // reload the program so each time we start from 0x0
          tlvmReset(m_data.context);

          tlvmByte cycles = 0;
          TLVM_FLAG_SET(C, 8080);
          ASSERT(tlvmStep(m_data.context, &cycles) == TLVM_SUCCESS);
          ASSERT(cycles == 10);
          ASSERT(m_data.context->m_ProgramCounter == 0x0000);

          cycles = 0;
          TLVM_FLAG_UNSET(C, 8080);
          ASSERT(tlvmStep(m_data.context, &cycles) == TLVM_SUCCESS);
          ASSERT(cycles == 10);
          ASSERT(m_data.context->m_ProgramCounter == 0x0003);
     },
     // data
     {
      tlvmContext* context;
      tlvmByte     bootloader[255];
     }
    );

TEST(JPO, JMP, 0.0f,
     // initialisation
     {
      tlvmInitContext(&m_data.context, TLVM_CPU_8080);
      tlvmSetMemory(m_data.context, m_data.bootloader, 0, 0xFF, TLVM_FLAG_READ);

      m_data.bootloader[0x00] = TLVM_JPO;
      m_data.bootloader[0x01] = 0x00;
      m_data.bootloader[0x02] = 0x00; // just jump to beginning
     },
     // cleanup
     {
      tlvmTerminateContext(&m_data.context);
     },
     // test
     {
          // use local variable so we can use macros
          tlvmContext* context = m_data.context;

          // reload the program so each time we start from 0x0
          tlvmReset(m_data.context);

          tlvmByte cycles = 0;
          TLVM_FLAG_UNSET(P, 8080);
          ASSERT(tlvmStep(m_data.context, &cycles) == TLVM_SUCCESS);
          ASSERT(cycles == 10);
          ASSERT(m_data.context->m_ProgramCounter == 0x0000);

          cycles = 0;
          TLVM_FLAG_SET(P, 8080);
          ASSERT(tlvmStep(m_data.context, &cycles) == TLVM_SUCCESS);
          ASSERT(cycles == 10);
          ASSERT(m_data.context->m_ProgramCounter == 0x0003);
     },
     // data
     {
      tlvmContext* context;
      tlvmByte     bootloader[255];
     }
    );

TEST(JPE, JMP, 0.0f,
     // initialisation
     {
      tlvmInitContext(&m_data.context, TLVM_CPU_8080);
      tlvmSetMemory(m_data.context, m_data.bootloader, 0, 0xFF, TLVM_FLAG_READ);

      m_data.bootloader[0x00] = TLVM_JPE;
      m_data.bootloader[0x01] = 0x00;
      m_data.bootloader[0x02] = 0x00; // just jump to beginning
     },
     // cleanup
     {
      tlvmTerminateContext(&m_data.context);
     },
     // test
     {
          // use local variable so we can use macros
          tlvmContext* context = m_data.context;

          // reload the program so each time we start from 0x0
          tlvmReset(m_data.context);

          tlvmByte cycles = 0;
          TLVM_FLAG_SET(P, 8080);
          ASSERT(tlvmStep(m_data.context, &cycles) == TLVM_SUCCESS);
          ASSERT(cycles == 10);
          ASSERT(m_data.context->m_ProgramCounter == 0x0000);

          cycles = 0;
          TLVM_FLAG_UNSET(P, 8080);
          ASSERT(tlvmStep(m_data.context, &cycles) == TLVM_SUCCESS);
          ASSERT(cycles == 10);
          ASSERT(m_data.context->m_ProgramCounter == 0x0003);
     },
     // data
     {
      tlvmContext* context;
      tlvmByte     bootloader[255];
     }
    );

TEST(JP, JMP, 0.0f,
     // initialisation
     {
      tlvmInitContext(&m_data.context, TLVM_CPU_8080);
      tlvmSetMemory(m_data.context, m_data.bootloader, 0, 0xFF, TLVM_FLAG_READ);

      m_data.bootloader[0x00] = TLVM_JP;
      m_data.bootloader[0x01] = 0x00;
      m_data.bootloader[0x02] = 0x00; // just jump to beginning
     },
     // cleanup
     {
      tlvmTerminateContext(&m_data.context);
     },
     // test
     {
          // use local variable so we can use macros
          tlvmContext* context = m_data.context;

          // reload the program so each time we start from 0x0
          tlvmReset(m_data.context);

          tlvmByte cycles = 0;
          TLVM_FLAG_UNSET(S, 8080);
          ASSERT(tlvmStep(m_data.context, &cycles) == TLVM_SUCCESS);
          ASSERT(cycles == 10);
          ASSERT(m_data.context->m_ProgramCounter == 0x0000);

          cycles = 0;
          TLVM_FLAG_SET(S, 8080);
          ASSERT(tlvmStep(m_data.context, &cycles) == TLVM_SUCCESS);
          ASSERT(cycles == 10);
          ASSERT(m_data.context->m_ProgramCounter == 0x0003);
     },
     // data
     {
      tlvmContext* context;
      tlvmByte     bootloader[255];
     }
    );

TEST(JM, JMP, 0.0f,
     // initialisation
     {
      tlvmInitContext(&m_data.context, TLVM_CPU_8080);
      tlvmSetMemory(m_data.context, m_data.bootloader, 0, 0xFF, TLVM_FLAG_READ);

      m_data.bootloader[0x00] = TLVM_JM;
      m_data.bootloader[0x01] = 0x00;
      m_data.bootloader[0x02] = 0x00; // just jump to beginning
     },
     // cleanup
     {
      tlvmTerminateContext(&m_data.context);
     },
     // test
     {
          // use local variable so we can use macros
          tlvmContext* context = m_data.context;

          // reload the program so each time we start from 0x0
          tlvmReset(m_data.context);

          tlvmByte cycles = 0;
          TLVM_FLAG_SET(S, 8080);
          ASSERT(tlvmStep(m_data.context, &cycles) == TLVM_SUCCESS);
          ASSERT(cycles == 10);
          ASSERT(m_data.context->m_ProgramCounter == 0x0000);

          cycles = 0;
          TLVM_FLAG_UNSET(S, 8080);
          ASSERT(tlvmStep(m_data.context, &cycles) == TLVM_SUCCESS);
          ASSERT(cycles == 10);
          ASSERT(m_data.context->m_ProgramCounter == 0x0003);
     },
     // data
     {
      tlvmContext* context;
      tlvmByte     bootloader[255];
     }
    );
