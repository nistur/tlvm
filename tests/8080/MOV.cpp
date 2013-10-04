#include "../tlvm-tests.h"

TEST(Instructions, MOV, 0.0f,
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
          //ASSERT(m_data.context->m_InstructionSet[TLVM_MOV_MM] == tlvmMOV); // doesn't exist
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

TEST_MOV_REG_REG(B,B);
TEST_MOV_REG_REG(B,C);
TEST_MOV_REG_REG(B,D);
TEST_MOV_REG_REG(B,E);
TEST_MOV_REG_REG(B,H);
TEST_MOV_REG_REG(B,L);
TEST_MOV_REG_REG(B,A);
TEST_MOV_REG_MEM(B);

TEST_MOV_REG_REG(C,B);
TEST_MOV_REG_REG(C,C);
TEST_MOV_REG_REG(C,D);
TEST_MOV_REG_REG(C,E);
TEST_MOV_REG_REG(C,H);
TEST_MOV_REG_REG(C,L);
TEST_MOV_REG_REG(C,A);
TEST_MOV_REG_MEM(C);

TEST_MOV_REG_REG(D,B);
TEST_MOV_REG_REG(D,C);
TEST_MOV_REG_REG(D,D);
TEST_MOV_REG_REG(D,E);
TEST_MOV_REG_REG(D,H);
TEST_MOV_REG_REG(D,L);
TEST_MOV_REG_REG(D,A);
TEST_MOV_REG_MEM(D);

TEST_MOV_REG_REG(H,B);
TEST_MOV_REG_REG(H,C);
TEST_MOV_REG_REG(H,D);
TEST_MOV_REG_REG(H,E);
TEST_MOV_REG_REG(H,H);
TEST_MOV_REG_REG(H,L);
TEST_MOV_REG_REG(H,A);
TEST_MOV_REG_MEM(H);

TEST_MOV_REG_REG(L,B);
TEST_MOV_REG_REG(L,C);
TEST_MOV_REG_REG(L,D);
TEST_MOV_REG_REG(L,E);
TEST_MOV_REG_REG(L,H);
TEST_MOV_REG_REG(L,L);
TEST_MOV_REG_REG(L,A);
TEST_MOV_REG_MEM(L);

TEST_MOV_REG_REG(A,B);
TEST_MOV_REG_REG(A,C);
TEST_MOV_REG_REG(A,D);
TEST_MOV_REG_REG(A,E);
TEST_MOV_REG_REG(A,H);
TEST_MOV_REG_REG(A,L);
TEST_MOV_REG_REG(A,A);
TEST_MOV_REG_MEM(A);

TEST_MOV_MEM_REG(B);
TEST_MOV_MEM_REG(C);
TEST_MOV_MEM_REG(D);
TEST_MOV_MEM_REG(E);
TEST_MOV_MEM_REG(H);
TEST(ML, MOV, 0.0f,
     {
      tlvmInitContext(&m_data.context);
      tlvmInit8080(m_data.context);
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
          m_data.context->m_Registers[TLVM_REG_L] = 99;
          m_data.context->m_Registers[TLVM_REG_H] = 0x01;
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
TEST_MOV_MEM_REG(A);
