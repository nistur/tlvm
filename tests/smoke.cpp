#include "tlvm-tests.h"
#include "tlvm.h"
#include "tlvm_instructions.h"

#include <stdio.h>
#include <string.h>

// TODO: replace Hello world with more condense version
TEST(HelloWorld, Smoke, 0.0f,
     // initialisation
     {
      tlvmInitContext(&m_data.context);
      tlvmAddALU(m_data.context);
      tlvmSetMemory(m_data.context, m_data.bootloader, 0x000, 255, TLVM_FLAG_READ | TLVM_FLAG_WRITE);
      tlvmSetMemory(m_data.context, m_data.memory, 0x100, 255, TLVM_FLAG_READ | TLVM_FLAG_WRITE);
      m_data.bootloader[0x00] = TLVM_LXI_H;
      m_data.bootloader[0x01] = 0x0;
      m_data.bootloader[0x02] = 0x1;
      m_data.bootloader[0x03] = TLVM_MVI_M;
      m_data.bootloader[0x04] = 'H';
      m_data.bootloader[0x05] = TLVM_INR_L;
      m_data.bootloader[0x06] = TLVM_MVI_M;
      m_data.bootloader[0x07] = 'e';
      m_data.bootloader[0x08] = TLVM_INR_L;
      m_data.bootloader[0x09] = TLVM_MVI_M;
      m_data.bootloader[0x0A] = 'l';
      m_data.bootloader[0x0B] = TLVM_INR_L;
      m_data.bootloader[0x0C] = TLVM_MVI_M;
      m_data.bootloader[0x0D] = 'l';
      m_data.bootloader[0x0E] = TLVM_INR_L;
      m_data.bootloader[0x0F] = TLVM_MVI_M;
      m_data.bootloader[0x10] = 'o';
      m_data.bootloader[0x11] = TLVM_INR_L;
      m_data.bootloader[0x12] = TLVM_MVI_M;
      m_data.bootloader[0x13] = ',';
      m_data.bootloader[0x14] = TLVM_INR_L;
      m_data.bootloader[0x15] = TLVM_MVI_M;
      m_data.bootloader[0x16] = ' ';
      m_data.bootloader[0x17] = TLVM_INR_L;
      m_data.bootloader[0x18] = TLVM_MVI_M;
      m_data.bootloader[0x19] = 'W';
      m_data.bootloader[0x1A] = TLVM_INR_L;
      m_data.bootloader[0x1B] = TLVM_MVI_M;
      m_data.bootloader[0x1C] = 'o';
      m_data.bootloader[0x1D] = TLVM_INR_L;
      m_data.bootloader[0x1E] = TLVM_MVI_M;
      m_data.bootloader[0x1F] = 'r';
      m_data.bootloader[0x20] = TLVM_INR_L;
      m_data.bootloader[0x21] = TLVM_MVI_M;
      m_data.bootloader[0x22] = 'l';
      m_data.bootloader[0x23] = TLVM_INR_L;
      m_data.bootloader[0x24] = TLVM_MVI_M;
      m_data.bootloader[0x25] = 'd';
      m_data.bootloader[0x26] = TLVM_INR_L;
      m_data.bootloader[0x27] = TLVM_MVI_M;
      m_data.bootloader[0x28] = '!';
      m_data.bootloader[0x29] = TLVM_INR_L;
      m_data.bootloader[0x2A] = TLVM_MVI_M;
      m_data.bootloader[0x2B] = 0;
      m_data.bootloader[0x2C] = TLVM_HLT;

     },
     // cleanup
     {
      tlvmTerminateContext(&m_data.context);
     },
     // test
     {
          memset(m_data.memory, 0, 255);
          tlvmReset(m_data.context);

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
