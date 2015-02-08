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

#include <string.h>

// TODO: replace Hello world with more condense version
TEST(HelloWorld, Smoke, 0.0f,
     // initialisation
     {
      tlvmInitContext(&m_data.context);
      tlvm8080Init(m_data.context);
      tlvmSetMemory(m_data.context, m_data.bootloader, 0x000, 255, TLVM_FLAG_READ);
      tlvmSetMemory(m_data.context, m_data.memory, 0x100, 255, TLVM_FLAG_READ | TLVM_FLAG_WRITE);
      tlvmSetClockspeed(m_data.context, TLVM_MHZ(2,0));
      m_data.bootloader[0x00] = TLVM_LXI_H;
      m_data.bootloader[0x01] = 0x0;
      m_data.bootloader[0x02] = 0x1;
      m_data.bootloader[0x03] = TLVM_MVI_M;
      m_data.bootloader[0x04] = 'H';
      m_data.bootloader[0x05] = TLVM_INX_H;
      m_data.bootloader[0x06] = TLVM_MVI_M;
      m_data.bootloader[0x07] = 'e';
      m_data.bootloader[0x08] = TLVM_INX_H;
      m_data.bootloader[0x09] = TLVM_MVI_M;
      m_data.bootloader[0x0A] = 'l';
      m_data.bootloader[0x0B] = TLVM_INX_H;
      m_data.bootloader[0x0C] = TLVM_MVI_M;
      m_data.bootloader[0x0D] = 'l';
      m_data.bootloader[0x0E] = TLVM_INX_H;
      m_data.bootloader[0x0F] = TLVM_MVI_M;
      m_data.bootloader[0x10] = 'o';
      m_data.bootloader[0x11] = TLVM_INX_H;
      m_data.bootloader[0x12] = TLVM_MVI_M;
      m_data.bootloader[0x13] = ',';
      m_data.bootloader[0x14] = TLVM_INX_H;
      m_data.bootloader[0x15] = TLVM_MVI_M;
      m_data.bootloader[0x16] = ' ';
      m_data.bootloader[0x17] = TLVM_INX_H;
      m_data.bootloader[0x18] = TLVM_MVI_M;
      m_data.bootloader[0x19] = 'W';
      m_data.bootloader[0x1A] = TLVM_INX_H;
      m_data.bootloader[0x1B] = TLVM_MVI_M;
      m_data.bootloader[0x1C] = 'o';
      m_data.bootloader[0x1D] = TLVM_INX_H;
      m_data.bootloader[0x1E] = TLVM_MVI_M;
      m_data.bootloader[0x1F] = 'r';
      m_data.bootloader[0x20] = TLVM_INX_H;
      m_data.bootloader[0x21] = TLVM_MVI_M;
      m_data.bootloader[0x22] = 'l';
      m_data.bootloader[0x23] = TLVM_INX_H;
      m_data.bootloader[0x24] = TLVM_MVI_M;
      m_data.bootloader[0x25] = 'd';
      m_data.bootloader[0x26] = TLVM_INX_H;
      m_data.bootloader[0x27] = TLVM_MVI_M;
      m_data.bootloader[0x28] = '!';
      m_data.bootloader[0x29] = TLVM_INX_H;
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

// This Hello World program is expected to run significantly slower than the above one
// as it uses a couple of "slow" JMPs however it demonstrates a more concise and sane
// program where all the data is together
TEST(HelloWorld2, Smoke, 0.0f,
     // initialisation
     {
      tlvmInitContext(&m_data.context);
      tlvm8080Init(m_data.context);
      tlvmSetMemory(m_data.context, m_data.bootloader, 0x000, 255, TLVM_FLAG_READ);
      tlvmSetMemory(m_data.context, m_data.memory, 0x100, 255, TLVM_FLAG_READ | TLVM_FLAG_WRITE);
      tlvmSetClockspeed(m_data.context, TLVM_MHZ(2,0));
      m_data.bootloader[0x00] = TLVM_LXI_B; // set the position that we're
      m_data.bootloader[0x01] = 0x00;       // going to write to
      m_data.bootloader[0x02] = 0x01;
      m_data.bootloader[0x03] = TLVM_LXI_D; // where we're reading data from
      m_data.bootloader[0x04] = 0x09;
      m_data.bootloader[0x05] = 0x00;
      m_data.bootloader[0x06] = TLVM_JMP; // jump forward, over the data
      m_data.bootloader[0x07] = 0x19;     // and over the INX's
      m_data.bootloader[0x08] = 0x00;
      m_data.bootloader[0x09] = 'H';      // Data
      m_data.bootloader[0x0A] = 'e';
      m_data.bootloader[0x0B] = 'l';
      m_data.bootloader[0x0C] = 'l';
      m_data.bootloader[0x0D] = 'o';
      m_data.bootloader[0x0E] = ',';
      m_data.bootloader[0x0F] = ' ';
      m_data.bootloader[0x10] = 'W';
      m_data.bootloader[0x11] = 'o';
      m_data.bootloader[0x12] = 'r';
      m_data.bootloader[0x13] = 'l';
      m_data.bootloader[0x14] = 'd';
      m_data.bootloader[0x15] = '!';
      m_data.bootloader[0x16] = 0;
      m_data.bootloader[0x17] = TLVM_INX_D;
      m_data.bootloader[0x18] = TLVM_INX_B;
      m_data.bootloader[0x19] = TLVM_LDAX_D;
      m_data.bootloader[0x1A] = TLVM_STAX_B;
      m_data.bootloader[0x1B] = TLVM_ADI; // Add 0 to A to set the zero flag if we're
      m_data.bootloader[0x1C] = 0;        // at the end
      m_data.bootloader[0x1D] = TLVM_JNZ; // if the flag wasn't set to zero
      m_data.bootloader[0x1E] = 0x17;     // jump back to the INX's
      m_data.bootloader[0x1F] = 0x00;
      m_data.bootloader[0x20] = TLVM_HLT;

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
