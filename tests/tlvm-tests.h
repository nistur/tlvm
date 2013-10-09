#ifndef __TLVM_TESTS_H__
#define __TLVM_TESTS_H__

extern "C" {
#include "tlvm_internal.h"
}

#include "testsuite/tests.h"

#define TEST_8080(x, grp, t, init, cleanup, test, data) \
  TEST(x, grp##_8080, t, init, cleanup, test, data)

#define TEST_8231(x, grp, t, init, cleanup, test, data) \
  TEST(x, grp##_8231, t, init, cleanup, test, data)

#define TEST_MOV_REG_REG(to, from) \
TEST_8080(to##from, MOV, 0.0f, \
     { \
      tlvmInitContext(&m_data.context); \
      tlvmInit8080(m_data.context); \
      tlvmSetMemory(m_data.context, m_data.bootloader, 0, 0xFF, TLVM_FLAG_READ); \
      m_data.bootloader[0x00] = TLVM_MOV_##to##from; \
     }, \
     { \
      tlvmTerminateContext(&m_data.context); \
     }, \
     { \
          tlvmReset(m_data.context); \
          tlvmByte cycles = 0; \
          m_data.context->m_Registers[TLVM_REG_##from] = 99; \
          ASSERT(tlvmStep(m_data.context, &cycles) == TLVM_SUCCESS); \
          ASSERT(m_data.context->m_Registers[TLVM_REG_##to] == 99); \
          ASSERT(cycles == 5); \
     }, \
     { \
      tlvmContext* context; \
      tlvmByte     bootloader[255]; \
     } \
    );

#define TEST_MOV_REG_MEM(to) \
TEST_8080(to##M, MOV, 0.0f, \
     { \
      tlvmInitContext(&m_data.context); \
      tlvmInit8080(m_data.context); \
      tlvmSetMemory(m_data.context, m_data.bootloader, 0, 0xFF, TLVM_FLAG_READ); \
      tlvmSetMemory(m_data.context, m_data.memory, 0x100, 0xFF, TLVM_FLAG_READ|TLVM_FLAG_WRITE); \
      m_data.bootloader[0x00] = TLVM_MOV_##to##M; \
     }, \
     { \
      tlvmTerminateContext(&m_data.context); \
     }, \
     { \
          tlvmReset(m_data.context); \
          tlvmByte cycles = 0; \
          m_data.context->m_Registers[TLVM_REG_H] = 0x01; \
          m_data.memory[0x00] = 99; \
          ASSERT(tlvmStep(m_data.context, &cycles) == TLVM_SUCCESS); \
          ASSERT(m_data.context->m_Registers[TLVM_REG_##to] == 99); \
          ASSERT(cycles == 7); \
     }, \
     { \
      tlvmContext* context; \
      tlvmByte     bootloader[255]; \
      tlvmByte     memory[255]; \
     } \
    );

#define TEST_MOV_MEM_REG(from) \
TEST_8080(M##from, MOV, 0.0f, \
     { \
      tlvmInitContext(&m_data.context); \
      tlvmInit8080(m_data.context); \
      tlvmSetMemory(m_data.context, m_data.bootloader, 0, 0xFF, TLVM_FLAG_READ); \
      tlvmSetMemory(m_data.context, m_data.memory, 0x100, 0xFF, TLVM_FLAG_READ|TLVM_FLAG_WRITE); \
      m_data.bootloader[0x00] = TLVM_MOV_M##from; \
     }, \
     { \
      tlvmTerminateContext(&m_data.context); \
     }, \
     { \
          tlvmReset(m_data.context); \
          tlvmByte cycles = 0; \
          m_data.context->m_Registers[TLVM_REG_##from] = 0x01; \
          m_data.context->m_Registers[TLVM_REG_H] = 0x01; \
          ASSERT(tlvmStep(m_data.context, &cycles) == TLVM_SUCCESS); \
          ASSERT(m_data.memory[0x00] == 0x01); \
          ASSERT(cycles == 7); \
     }, \
     { \
      tlvmContext* context; \
      tlvmByte     bootloader[255]; \
      tlvmByte     memory[255]; \
     } \
    );

#define STEP(x) \
{ \
  { x; } \
  ASSERT(tlvmStep(m_data.context, NULL) == TLVM_SUCCESS); \
}
#define SET_HIGH_8231A_SVR(x) *svr |=  TLVM_8231A_SVR_##x
#define SET_LOW_8231A_SVR(x)  *svr &= ~TLVM_8231A_SVR_##x
#define SET_HIGH_8231A(x) *cmd |=  TLVM_8231A_CMD_##x
#define SET_LOW_8231A(x)  *cmd &= ~TLVM_8231A_CMD_##x

#define WRITE_COMMAND_8231A(x)					\
  {								\
  STEP(SET_LOW_8231A(CS));					\
  STEP(SET_HIGH_8231A(A0));					\
  STEP(SET_LOW_8231A(WR));					\
  while((*cmd & TLVM_8231A_CMD_READY))				\
    STEP({});							\
  STEP(*db = x);						\
  STEP(SET_HIGH_8231A(WR));					\
  ASSERT(m_data.context->m_Registers[TLVM_8231A_COMMAND] == x); \
  STEP(SET_LOW_8231A(A0));					\
  STEP(SET_HIGH_8231A(CS));					\
  while((*cmd & TLVM_8231A_CMD_END))				\
    STEP({});							\
  STEP(SET_LOW_8231A_SVR(EACK));				\
  while(!(*cmd & TLVM_8231A_CMD_END)) \
    STEP({}); \
  STEP(SET_HIGH_8231A_SVR(EACK)); \
 }

#define WRITE_DATA_8231A(x) \
{ \
  STEP(SET_LOW_8231A(CS)); \
  STEP(SET_LOW_8231A(A0)); \
  STEP(SET_LOW_8231A(WR)); \
  while((*cmd & TLVM_8231A_CMD_READY)) \
    STEP({}); \
  STEP(*db = x); \
  STEP(SET_HIGH_8231A(WR)); \
  STEP(SET_HIGH_8231A(A0)); \
  STEP(SET_HIGH_8231A(CS)); \
}

#define READ_DATA_8231A(x) \
{ \
  STEP(SET_LOW_8231A(CS)); \
  STEP(SET_LOW_8231A(A0)); \
  STEP(SET_LOW_8231A(RD)); \
  while((*cmd & TLVM_8231A_CMD_READY)) \
    STEP({}); \
  STEP(SET_HIGH_8231A(RD)); \
  x = *db; \
  STEP(SET_HIGH_8231A(A0)); \
  STEP(SET_HIGH_8231A(CS)); \
}


#endif/*__TLVM_TESTS_H__*/
