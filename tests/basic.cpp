#include "tlvm-tests.h"
#include "tlvm.h"

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
      ASSERT(tlvmInitContext(&m_data.context) == TLVM_SUCCESS);
      ASSERT(m_data.context != NULL);
      ASSERT(tlvmTerminateContext(&m_data.context) == TLVM_SUCCESS);
     },
     // data
     {
      tlvmContext* context;
     }
    );

TEST(SetRegisters, Basic, 0.0f,
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
          // no context
          ASSERT(tlvmSetMemoryBuffer(NULL, m_data.memory, 255) == TLVM_NO_CONTEXT);

          // no buffer
          ASSERT(tlvmSetMemoryBuffer(m_data.context, NULL, 255) == TLVM_NO_MEMORY);

          // zero size
          ASSERT(tlvmSetMemoryBuffer(m_data.context, m_data.memory, NULL) == TLVM_INVALID_INPUT);

          // valid input
          ASSERT(tlvmSetMemoryBuffer(m_data.context, m_data.memory, 255) == TLVM_SUCCESS);
      
     },
     // data
     {
      tlvmContext* context;
      tlvmByte     memory[255];
     }
    );

TEST(LoadProgram, Basic, 0.0f,
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
          // no context
          ASSERT(tlvmLoadProgram(NULL, m_data.program, 255) == TLVM_NO_CONTEXT);

          // no buffer
          ASSERT(tlvmLoadProgram(m_data.context, NULL, 255) == TLVM_INVALID_INPUT);

          // zero size
          ASSERT(tlvmLoadProgram(m_data.context, m_data.program, NULL) == TLVM_INVALID_INPUT);

          // valid input
          ASSERT(tlvmLoadProgram(m_data.context, m_data.program, 255) == TLVM_SUCCESS);
      
     },
     // data
     {
      tlvmContext* context;
      tlvmByte     program[255];
     }
    );

TEST(NOOP, Basic, 0.0f,
     // initialisation
     {
      tlvmInitContext(&m_data.context);
      m_data.program[0] = 0x0; // NOOP
      m_data.program[1] = 0xFF; // nothing, unknown instruction
     },
     // cleanup
     {
      tlvmTerminateContext(&m_data.context);
     },
     // test
     {
          // reload the program so each time we start from 0x0
          tlvmLoadProgram(m_data.context, m_data.program, 255);

          ASSERT(tlvmStep(m_data.context) == TLVM_SUCCESS);
          ASSERT(tlvmStep(m_data.context) == TLVM_UNKNOWN_INSTRUCTION);
          ASSERT(tlvmRun(m_data.context) == TLVM_UNKNOWN_INSTRUCTION);
     },
     // data
     {
      tlvmContext* context;
      tlvmByte     program[255];
     }
    );
