#include "../tlvm-tests.h"

TEST_8080(Instructions, JMP, 0.0f,
     // initialisation
     {
      tlvmInitContext(&m_data.context);
      tlvmInit8080(m_data.context);
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

TEST_8080(JMP, JMP, 0.0f,
     // initialisation
     {
      tlvmInitContext(&m_data.context);
      tlvmInit8080(m_data.context);
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
          // use local variable so we can use macros
          tlvmContext* context = m_data.context;

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

TEST_8080(JNZ, JMP, 0.0f,
     // initialisation
     {
      tlvmInitContext(&m_data.context);
      tlvmInit8080(m_data.context);
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
          TLVM_FLAG_UNSET(Z);
          ASSERT(tlvmStep(m_data.context, &cycles) == TLVM_SUCCESS);
          ASSERT(cycles == 10);
          ASSERT(m_data.context->m_ProgramCounter == 0x0000);

          cycles = 0;
          TLVM_FLAG_SET(Z);
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

TEST_8080(JZ, JMP, 0.0f,
     // initialisation
     {
      tlvmInitContext(&m_data.context);
      tlvmInit8080(m_data.context);
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
          TLVM_FLAG_SET(Z);
          ASSERT(tlvmStep(m_data.context, &cycles) == TLVM_SUCCESS);
          ASSERT(cycles == 10);
          ASSERT(m_data.context->m_ProgramCounter == 0x0000);

          cycles = 0;
          TLVM_FLAG_UNSET(Z);
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

TEST_8080(JNC, JMP, 0.0f,
     // initialisation
     {
      tlvmInitContext(&m_data.context);
      tlvmInit8080(m_data.context);
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
          TLVM_FLAG_UNSET(C);
          ASSERT(tlvmStep(m_data.context, &cycles) == TLVM_SUCCESS);
          ASSERT(cycles == 10);
          ASSERT(m_data.context->m_ProgramCounter == 0x0000);

          cycles = 0;
          TLVM_FLAG_SET(C);
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

TEST_8080(JC, JMP, 0.0f,
     // initialisation
     {
      tlvmInitContext(&m_data.context);
      tlvmInit8080(m_data.context);
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
          TLVM_FLAG_SET(C);
          ASSERT(tlvmStep(m_data.context, &cycles) == TLVM_SUCCESS);
          ASSERT(cycles == 10);
          ASSERT(m_data.context->m_ProgramCounter == 0x0000);

          cycles = 0;
          TLVM_FLAG_UNSET(C);
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

TEST_8080(JPO, JMP, 0.0f,
     // initialisation
     {
      tlvmInitContext(&m_data.context);
      tlvmInit8080(m_data.context);
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
          TLVM_FLAG_UNSET(P);
          ASSERT(tlvmStep(m_data.context, &cycles) == TLVM_SUCCESS);
          ASSERT(cycles == 10);
          ASSERT(m_data.context->m_ProgramCounter == 0x0000);

          cycles = 0;
          TLVM_FLAG_SET(P);
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

TEST_8080(JPE, JMP, 0.0f,
     // initialisation
     {
      tlvmInitContext(&m_data.context);
      tlvmInit8080(m_data.context);
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
          TLVM_FLAG_SET(P);
          ASSERT(tlvmStep(m_data.context, &cycles) == TLVM_SUCCESS);
          ASSERT(cycles == 10);
          ASSERT(m_data.context->m_ProgramCounter == 0x0000);

          cycles = 0;
          TLVM_FLAG_UNSET(P);
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

TEST_8080(JP, JMP, 0.0f,
     // initialisation
     {
      tlvmInitContext(&m_data.context);
      tlvmInit8080(m_data.context);
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
          TLVM_FLAG_UNSET(S);
          ASSERT(tlvmStep(m_data.context, &cycles) == TLVM_SUCCESS);
          ASSERT(cycles == 10);
          ASSERT(m_data.context->m_ProgramCounter == 0x0000);

          cycles = 0;
          TLVM_FLAG_SET(S);
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

TEST_8080(JM, JMP, 0.0f,
     // initialisation
     {
      tlvmInitContext(&m_data.context);
      tlvmInit8080(m_data.context);
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
          TLVM_FLAG_SET(S);
          ASSERT(tlvmStep(m_data.context, &cycles) == TLVM_SUCCESS);
          ASSERT(cycles == 10);
          ASSERT(m_data.context->m_ProgramCounter == 0x0000);

          cycles = 0;
          TLVM_FLAG_UNSET(S);
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