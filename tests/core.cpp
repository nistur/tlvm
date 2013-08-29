#include "tlvm-tests.h"
#include "tlvm.h"
#include "tlvm_instructions.h"

TEST(NOOP, Core, 0.0f,
     // initialisation
     {
      tlvmInitContext(&m_data.context);
      m_data.bootloader[0] = TLVM_NOOP;
      m_data.bootloader[1] = 0xFF; // nothing, unknown instruction
     },
     // cleanup
     {
      tlvmTerminateContext(&m_data.context);
     },
     // test
     {
          // reload the program so each time we start from 0x0
          tlvmLoadBootloader(m_data.context, m_data.bootloader);

          ASSERT(tlvmStep(m_data.context) == TLVM_SUCCESS);
          ASSERT(tlvmStep(m_data.context) == TLVM_UNKNOWN_INSTRUCTION);
          ASSERT(tlvmRun(m_data.context) == TLVM_UNKNOWN_INSTRUCTION);
     },
     // data
     {
      tlvmContext* context;
      tlvmByte     bootloader[255];
     }
    );

TEST(MOV, Core, 0.0f,
     // initialisation
     {
      tlvmInitContext(&m_data.context);
      tlvmSetMemoryBuffer(m_data.context, m_data.memory, 255);
      tlvmAddALU(m_data.context);
      m_data.bootloader[0] = TLVM_ADI;
      m_data.bootloader[1] = 99;
      m_data.bootloader[2] = TLVM_MOV_A;
      m_data.bootloader[3] = TLVM_ANI;
      m_data.bootloader[4] = 0;
     },
     // cleanup
     {
      tlvmTerminateContext(&m_data.context);
     },
     // test
     {
          // reload the program so each time we start from 0x0
          tlvmLoadBootloader(m_data.context, m_data.bootloader);
          tlvmStep(m_data.context); // we're going to assume that the ADI works, as it's tested in ALU

          ASSERT(tlvmStep(m_data.context) == TLVM_SUCCESS); // check that the MOV command was successful
          ASSERT(m_data.memory[0] == 99); // HL should be set to 0x0000 so it should write the value into the beginning

          tlvmStep(m_data.context); // we're going to assume that the ANI works
     },
     // data
     {
      tlvmContext* context;
      tlvmByte     bootloader[255];
      tlvmByte     memory[255];
     }
    );