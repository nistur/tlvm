#include "tlvm-tests.h"
#include "tlvm.h"
#include "tlvm_instructions.h"

#include <string.h>

TEST(HelloWorld, Smoke, 0.0f,
     // initialisation
     {
      tlvmInitContext(&m_data.context);
      tlvmAddALU(m_data.context);
      tlvmSetMemoryBuffer(m_data.context, m_data.memory, 255);
      m_data.bootloader[0x00] = TLVM_MVI_M;
      m_data.bootloader[0x01] = 'H';
      m_data.bootloader[0x02] = TLVM_INR_L;
      m_data.bootloader[0x03] = TLVM_MVI_M;
      m_data.bootloader[0x04] = 'e';
      m_data.bootloader[0x05] = TLVM_INR_L;
      m_data.bootloader[0x06] = TLVM_MVI_M;
      m_data.bootloader[0x07] = 'l';
      m_data.bootloader[0x08] = TLVM_INR_L;
      m_data.bootloader[0x09] = TLVM_MVI_M;
      m_data.bootloader[0x0A] = 'l';
      m_data.bootloader[0x0B] = TLVM_INR_L;
      m_data.bootloader[0x0C] = TLVM_MVI_M;
      m_data.bootloader[0x0D] = 'o';
      m_data.bootloader[0x0E] = TLVM_INR_L;
      m_data.bootloader[0x0F] = TLVM_MVI_M;
      m_data.bootloader[0x10] = ',';
      m_data.bootloader[0x11] = TLVM_INR_L;
      m_data.bootloader[0x12] = TLVM_MVI_M;
      m_data.bootloader[0x13] = ' ';
      m_data.bootloader[0x14] = TLVM_INR_L;
      m_data.bootloader[0x15] = TLVM_MVI_M;
      m_data.bootloader[0x16] = 'W';
      m_data.bootloader[0x17] = TLVM_INR_L;
      m_data.bootloader[0x18] = TLVM_MVI_M;
      m_data.bootloader[0x19] = 'o';
      m_data.bootloader[0x1A] = TLVM_INR_L;
      m_data.bootloader[0x1B] = TLVM_MVI_M;
      m_data.bootloader[0x1C] = 'r';
      m_data.bootloader[0x1D] = TLVM_INR_L;
      m_data.bootloader[0x1E] = TLVM_MVI_M;
      m_data.bootloader[0x1F] = 'l';
      m_data.bootloader[0x20] = TLVM_INR_L;
      m_data.bootloader[0x21] = TLVM_MVI_M;
      m_data.bootloader[0x22] = 'd';
      m_data.bootloader[0x23] = TLVM_INR_L;
      m_data.bootloader[0x24] = TLVM_MVI_M;
      m_data.bootloader[0x25] = '!';
      m_data.bootloader[0x26] = TLVM_INR_L;
      m_data.bootloader[0x27] = TLVM_MVI_M;
      m_data.bootloader[0x28] = 0;
      m_data.bootloader[0x29] = TLVM_MVI_L;
      m_data.bootloader[0x2A] = 0;
      m_data.bootloader[0x2B] = TLVM_HLT;

     },
     // cleanup
     {
      tlvmTerminateContext(&m_data.context);
     },
     // test
     {
          // reload the program so each time we start from 0x0
          tlvmLoadBootloader(m_data.context, m_data.bootloader);

          ASSERT(tlvmRun(m_data.context) == TLVM_SUCCESS);
          ASSERT(strcmp((const char*)m_data.memory, "Hello, World!") == 0);

     },
     // data
     {
      tlvmContext* context;
      tlvmByte     bootloader[255];
      tlvmByte     memory[255];
     }
    );
