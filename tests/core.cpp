#include "tlvm-tests.h"
#include "tlvm.h"
#include "tlvm_instructions.h"

TEST(NOP, Core, 0.0f,
     // initialisation
     {
      tlvmInitContext(&m_data.context);
      m_data.bootloader[0] = TLVM_NOP;
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

          tlvmByte cycle = 0;
          ASSERT(tlvmStep(m_data.context, &cycle) == TLVM_SUCCESS);
          ASSERT(cycle == 1);
          
          ASSERT(tlvmStep(m_data.context, &cycle) == TLVM_UNKNOWN_INSTRUCTION);
          ASSERT(tlvmRun(m_data.context) == TLVM_UNKNOWN_INSTRUCTION);
     },
     // data
     {
      tlvmContext* context;
      tlvmByte     bootloader[255];
     }
    );

TEST(LXI, Core, 0.0f,
     // initialisation
     {
      tlvmInitContext(&m_data.context);
      tlvmSetMemoryBuffer(m_data.context, m_data.memory, 255);
      tlvmAddALU(m_data.context);
      tlvmShort addr = 10;
      tlvmByte* pAddr = (tlvmByte*)&addr;
      m_data.bootloader[0] = TLVM_ADI; // add 99 to A
      m_data.bootloader[1] = 99;
      m_data.bootloader[2] = TLVM_LXI_H; // set HL to 10
      m_data.bootloader[3] = pAddr[0];
      m_data.bootloader[4] = pAddr[1];
      m_data.bootloader[5] = TLVM_MOV_MA; // write A to (HL)
      m_data.bootloader[6] = TLVM_ANI; // AND A with 0 (clearing it)
      m_data.bootloader[7] = 0;
     },
     // cleanup
     {
      tlvmTerminateContext(&m_data.context);
     },
     // test
     {
          // reload the program so each time we start from 0x0
          tlvmLoadBootloader(m_data.context, m_data.bootloader);
          tlvmStep(m_data.context, NULL); // we're going to assume that the ADI works, as it's tested in ALU

          tlvmByte cycle = 0;
          ASSERT(tlvmStep(m_data.context, &cycle) == TLVM_SUCCESS);
          ASSERT(cycle == 3);

          tlvmStep(m_data.context, NULL); // Assume MOV works
          ASSERT(m_data.memory[10] == 99); // HL should be set to 0x0000 so it should write the value into the beginning

          tlvmStep(m_data.context, NULL); // we're going to assume that the ANI works
     },
     // data
     {
      tlvmContext* context;
      tlvmByte     bootloader[255];
      tlvmByte     memory[255];
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
      m_data.bootloader[2] = TLVM_MOV_MA;
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
          tlvmStep(m_data.context, NULL); // we're going to assume that the ADI works, as it's tested in ALU

          tlvmByte cycle = 0;
          ASSERT(tlvmStep(m_data.context, &cycle) == TLVM_SUCCESS); // check that the MOV command was successful
          ASSERT(cycle == 1);
          ASSERT(m_data.memory[0] == 99); // HL should be set to 0x0000 so it should write the value into the beginning

          tlvmStep(m_data.context, NULL); // we're going to assume that the ANI works
     },
     // data
     {
      tlvmContext* context;
      tlvmByte     bootloader[255];
      tlvmByte     memory[255];
     }
    );