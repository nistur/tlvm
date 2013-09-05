#include "tlvm-tests.h"
#include "tlvm.h"
#include "tlvm_instructions.h"

TEST(InitTerminate, ALU, 0.0f,
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
          ASSERT(tlvmAddALU(m_data.context) == TLVM_SUCCESS);
     },
     // data
     {
      tlvmContext* context;
     }
    );

TEST(ADI, ALU, 0.0f,
     // initialisation
     {
      tlvmInitContext(&m_data.context);
      tlvmAddALU(m_data.context);
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
          ASSERT(cycle == 2);
     },
     // data
     {
      tlvmContext* context;
      tlvmByte     bootloader[255];
     }
    );