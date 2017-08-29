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

TEST(Instructions, MOV, 0.0f,
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
          ASSERT(m_data.context->m_InstructionSet[TLVM_MOV_BB] == tlvmMOV);
          ASSERT(m_data.context->m_InstructionSet[TLVM_MOV_BC] == tlvmMOV);
          ASSERT(m_data.context->m_InstructionSet[TLVM_MOV_BD] == tlvmMOV);
          ASSERT(m_data.context->m_InstructionSet[TLVM_MOV_BE] == tlvmMOV);
          ASSERT(m_data.context->m_InstructionSet[TLVM_MOV_BH] == tlvmMOV);
          ASSERT(m_data.context->m_InstructionSet[TLVM_MOV_BL] == tlvmMOV);
          ASSERT(m_data.context->m_InstructionSet[TLVM_MOV_BM] == tlvmMOV);
          ASSERT(m_data.context->m_InstructionSet[TLVM_MOV_BA] == tlvmMOV);

          ASSERT(m_data.context->m_InstructionSet[TLVM_MOV_CB] == tlvmMOV);
          ASSERT(m_data.context->m_InstructionSet[TLVM_MOV_CC] == tlvmMOV);
          ASSERT(m_data.context->m_InstructionSet[TLVM_MOV_CD] == tlvmMOV);
          ASSERT(m_data.context->m_InstructionSet[TLVM_MOV_CE] == tlvmMOV);
          ASSERT(m_data.context->m_InstructionSet[TLVM_MOV_CH] == tlvmMOV);
          ASSERT(m_data.context->m_InstructionSet[TLVM_MOV_CL] == tlvmMOV);
          ASSERT(m_data.context->m_InstructionSet[TLVM_MOV_CM] == tlvmMOV);
          ASSERT(m_data.context->m_InstructionSet[TLVM_MOV_CA] == tlvmMOV);

          ASSERT(m_data.context->m_InstructionSet[TLVM_MOV_DB] == tlvmMOV);
          ASSERT(m_data.context->m_InstructionSet[TLVM_MOV_DC] == tlvmMOV);
          ASSERT(m_data.context->m_InstructionSet[TLVM_MOV_DD] == tlvmMOV);
          ASSERT(m_data.context->m_InstructionSet[TLVM_MOV_DE] == tlvmMOV);
          ASSERT(m_data.context->m_InstructionSet[TLVM_MOV_DH] == tlvmMOV);
          ASSERT(m_data.context->m_InstructionSet[TLVM_MOV_DL] == tlvmMOV);
          ASSERT(m_data.context->m_InstructionSet[TLVM_MOV_DM] == tlvmMOV);
          ASSERT(m_data.context->m_InstructionSet[TLVM_MOV_DA] == tlvmMOV);

          ASSERT(m_data.context->m_InstructionSet[TLVM_MOV_EB] == tlvmMOV);
          ASSERT(m_data.context->m_InstructionSet[TLVM_MOV_EC] == tlvmMOV);
          ASSERT(m_data.context->m_InstructionSet[TLVM_MOV_ED] == tlvmMOV);
          ASSERT(m_data.context->m_InstructionSet[TLVM_MOV_EE] == tlvmMOV);
          ASSERT(m_data.context->m_InstructionSet[TLVM_MOV_EH] == tlvmMOV);
          ASSERT(m_data.context->m_InstructionSet[TLVM_MOV_EL] == tlvmMOV);
          ASSERT(m_data.context->m_InstructionSet[TLVM_MOV_EM] == tlvmMOV);
          ASSERT(m_data.context->m_InstructionSet[TLVM_MOV_EA] == tlvmMOV);

          ASSERT(m_data.context->m_InstructionSet[TLVM_MOV_HB] == tlvmMOV);
          ASSERT(m_data.context->m_InstructionSet[TLVM_MOV_HC] == tlvmMOV);
          ASSERT(m_data.context->m_InstructionSet[TLVM_MOV_HD] == tlvmMOV);
          ASSERT(m_data.context->m_InstructionSet[TLVM_MOV_HE] == tlvmMOV);
          ASSERT(m_data.context->m_InstructionSet[TLVM_MOV_HH] == tlvmMOV);
          ASSERT(m_data.context->m_InstructionSet[TLVM_MOV_HL] == tlvmMOV);
          ASSERT(m_data.context->m_InstructionSet[TLVM_MOV_HM] == tlvmMOV);
          ASSERT(m_data.context->m_InstructionSet[TLVM_MOV_HA] == tlvmMOV);

          ASSERT(m_data.context->m_InstructionSet[TLVM_MOV_MB] == tlvmMOV);
          ASSERT(m_data.context->m_InstructionSet[TLVM_MOV_MC] == tlvmMOV);
          ASSERT(m_data.context->m_InstructionSet[TLVM_MOV_MD] == tlvmMOV);
          ASSERT(m_data.context->m_InstructionSet[TLVM_MOV_ME] == tlvmMOV);
          ASSERT(m_data.context->m_InstructionSet[TLVM_MOV_MH] == tlvmMOV);
          ASSERT(m_data.context->m_InstructionSet[TLVM_MOV_ML] == tlvmMOV);
          //ASSERT(m_data.conteta->m_InstructionSet[TLVM_MOV_MM] == tlvmMOV); // doesn't exist
          ASSERT(m_data.context->m_InstructionSet[TLVM_MOV_MA] == tlvmMOV);

          ASSERT(m_data.context->m_InstructionSet[TLVM_MOV_AB] == tlvmMOV);
          ASSERT(m_data.context->m_InstructionSet[TLVM_MOV_AC] == tlvmMOV);
          ASSERT(m_data.context->m_InstructionSet[TLVM_MOV_AD] == tlvmMOV);
          ASSERT(m_data.context->m_InstructionSet[TLVM_MOV_AE] == tlvmMOV);
          ASSERT(m_data.context->m_InstructionSet[TLVM_MOV_AH] == tlvmMOV);
          ASSERT(m_data.context->m_InstructionSet[TLVM_MOV_AL] == tlvmMOV);
          ASSERT(m_data.context->m_InstructionSet[TLVM_MOV_AM] == tlvmMOV);
          ASSERT(m_data.context->m_InstructionSet[TLVM_MOV_AA] == tlvmMOV);
     },
     // data
     {
      tlvmContext* context;
     }
    );

TEST_MOV_REG_REG(B,B,8080);
TEST_MOV_REG_REG(B,C,8080);
TEST_MOV_REG_REG(B,D,8080);
TEST_MOV_REG_REG(B,E,8080);
TEST_MOV_REG_REG(B,H,8080);
TEST_MOV_REG_REG(B,L,8080);
TEST_MOV_REG_REG(B,A,8080);
TEST_MOV_REG_MEM(B,8080);

TEST_MOV_REG_REG(C,B,8080);
TEST_MOV_REG_REG(C,C,8080);
TEST_MOV_REG_REG(C,D,8080);
TEST_MOV_REG_REG(C,E,8080);
TEST_MOV_REG_REG(C,H,8080);
TEST_MOV_REG_REG(C,L,8080);
TEST_MOV_REG_REG(C,A,8080);
TEST_MOV_REG_MEM(C,8080);

TEST_MOV_REG_REG(D,B,8080);
TEST_MOV_REG_REG(D,C,8080);
TEST_MOV_REG_REG(D,D,8080);
TEST_MOV_REG_REG(D,E,8080);
TEST_MOV_REG_REG(D,H,8080);
TEST_MOV_REG_REG(D,L,8080);
TEST_MOV_REG_REG(D,A,8080);
TEST_MOV_REG_MEM(D,8080);

TEST_MOV_REG_REG(H,B,8080);
TEST_MOV_REG_REG(H,C,8080);
TEST_MOV_REG_REG(H,D,8080);
TEST_MOV_REG_REG(H,E,8080);
TEST_MOV_REG_REG(H,H,8080);
TEST_MOV_REG_REG(H,L,8080);
TEST_MOV_REG_REG(H,A,8080);
TEST_MOV_REG_MEM(H,8080);

TEST_MOV_REG_REG(L,B,8080);
TEST_MOV_REG_REG(L,C,8080);
TEST_MOV_REG_REG(L,D,8080);
TEST_MOV_REG_REG(L,E,8080);
TEST_MOV_REG_REG(L,H,8080);
TEST_MOV_REG_REG(L,L,8080);
TEST_MOV_REG_REG(L,A,8080);
TEST_MOV_REG_MEM(L,8080);

TEST_MOV_REG_REG(A,B,8080);
TEST_MOV_REG_REG(A,C,8080);
TEST_MOV_REG_REG(A,D,8080);
TEST_MOV_REG_REG(A,E,8080);
TEST_MOV_REG_REG(A,H,8080);
TEST_MOV_REG_REG(A,L,8080);
TEST_MOV_REG_REG(A,A,8080);
TEST_MOV_REG_MEM(A,8080);

TEST_MOV_MEM_REG(B,8080);
TEST_MOV_MEM_REG(C,8080);
TEST_MOV_MEM_REG(D,8080);
TEST_MOV_MEM_REG(E,8080);
TEST_MOV_MEM_REG(H,8080);
TEST(ML, MOV, 0.0f,
     {
      tlvmInitContext(&m_data.context, TLVM_CPU_8080);
      tlvmSetMemory(m_data.context, m_data.bootloader, 0, 0xFF, TLVM_FLAG_READ);
      tlvmSetMemory(m_data.context, m_data.memory, 0x100, 0xFF, TLVM_FLAG_READ|TLVM_FLAG_WRITE);
      m_data.bootloader[0x00] = TLVM_MOV_ML;
     },
     {
      tlvmTerminateContext(&m_data.context);
     },
     {
          tlvmReset(m_data.context);
          tlvmByte cycles = 0;
          m_data.context->m_Registers[TLVM_8080_REG_L] = 99;
          m_data.context->m_Registers[TLVM_8080_REG_H] = 0x01;
          ASSERT(tlvmStep(m_data.context, &cycles) == TLVM_SUCCESS);
          ASSERT(m_data.memory[99] == 99);
          ASSERT(cycles == 7);
     },
     {
      tlvmContext* context;
      tlvmByte     bootloader[255];
      tlvmByte     memory[255];
     }
    );
TEST_MOV_MEM_REG(A,8080);
