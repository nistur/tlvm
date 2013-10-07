#include "../tlvm-tests.h"
#include <stdio.h>

#define PRINT_STACK(msg) \
  printf("\n==STACK=%.02d=====\n", m_data.context->m_StackPointer); \
  printf("%s\n", #msg); \
  for(int i = TLVM_8231A_STACK_START; i <= TLVM_8231A_STACK_END; ++i) \
  { \
    printf("%d%s", m_data.context->m_Registers[i], (i+1) % 4  ? "\t" : "\n"); \
  }\
  printf("===============\n");

TEST_8231(TEST, Smoke, 0.0f,
{
  tlvmInitContext(&m_data.context);
  tlvmInit8231A(m_data.context);
},
{
  tlvmTerminateContext(&m_data.context);
},
{
  tlvmByte* cmd = NULL;
  tlvmByte* db  = NULL;
  tlvmGetPort(m_data.context, TLVM_8231A_PORT_CMD, &cmd);
  tlvmGetPort(m_data.context, TLVM_8231A_PORT_DB, &db);

  printf("\n\n==========TEST\n");
  // first of all, we want 2 16 bit numbers
  tlvmShort A = 550;
  tlvmShort B = 25;
  tlvmShort R = 0;
  // Then we push them onto the 8231's stack
  // 1 byte at a time
  PRINT_STACK(init);
  WRITE_DATA_8231A(((tlvmByte*)&A)[1]);
  PRINT_STACK(push AU);
  WRITE_DATA_8231A(((tlvmByte*)&A)[0]);
  PRINT_STACK(push AL);
  WRITE_DATA_8231A(((tlvmByte*)&B)[1]);
  PRINT_STACK(push BU);
  WRITE_DATA_8231A(((tlvmByte*)&B)[0]);
  PRINT_STACK(push BL);

  WRITE_COMMAND_8231A(TLVM_8231A_SADD);
  PRINT_STACK(SADD);
  
  READ_DATA_8231A(((tlvmByte*)&R)[0]);
  PRINT_STACK(pop RL);
  READ_DATA_8231A(((tlvmByte*)&R)[1]);
  PRINT_STACK(pop RU);
  
  ASSERT(R == 575);
},
{
  tlvmContext* context;
})

TEST_8231(SADD, Smoke, 0.0f,
{
  tlvmInitContext(&m_data.context);
  tlvmInit8231A(m_data.context);
},
{
  tlvmTerminateContext(&m_data.context);
},
{
  tlvmByte* cmd = NULL;
  tlvmByte* db  = NULL;
  tlvmGetPort(m_data.context, TLVM_8231A_PORT_CMD, &cmd);
  tlvmGetPort(m_data.context, TLVM_8231A_PORT_DB, &db);

  // first of all, we want 2 16 bit numbers
  tlvmShort A = 550;
  tlvmShort B = 25;
  tlvmShort R = 0;
  // Then we push them onto the 8231's stack
  // 1 byte at a time
  WRITE_DATA_8231A(((tlvmByte*)&A)[1]);
  WRITE_DATA_8231A(((tlvmByte*)&A)[0]);
  WRITE_DATA_8231A(((tlvmByte*)&B)[1]);
  WRITE_DATA_8231A(((tlvmByte*)&B)[0]);

  WRITE_COMMAND_8231A(TLVM_8231A_SADD);
  
  READ_DATA_8231A(((tlvmByte*)&R)[0]);
  READ_DATA_8231A(((tlvmByte*)&R)[1]);
  ASSERT(R == A + B);
},
{
  tlvmContext* context;
})

TEST_8231(SSUB, Smoke, 0.0f,
{
  tlvmInitContext(&m_data.context);
  tlvmInit8231A(m_data.context);
},
{
  tlvmTerminateContext(&m_data.context);
},
{
  tlvmByte* cmd = NULL;
  tlvmByte* db  = NULL;
  tlvmGetPort(m_data.context, TLVM_8231A_PORT_CMD, &cmd);
  tlvmGetPort(m_data.context, TLVM_8231A_PORT_DB, &db);

  // first of all, we want 2 16 bit numbers
  tlvmShort A = 550;
  tlvmShort B = 25;
  tlvmShort R = 0;
  // Then we push them onto the 8231's stack
  // 1 byte at a time
  WRITE_DATA_8231A(((tlvmByte*)&A)[1]);
  WRITE_DATA_8231A(((tlvmByte*)&A)[0]);
  WRITE_DATA_8231A(((tlvmByte*)&B)[1]);
  WRITE_DATA_8231A(((tlvmByte*)&B)[0]);

  WRITE_COMMAND_8231A(TLVM_8231A_SSUB);
  
  READ_DATA_8231A(((tlvmByte*)&R)[1]);
  READ_DATA_8231A(((tlvmByte*)&R)[0]);
  ASSERT(R == A - B);
},
{
  tlvmContext* context;
})

TEST_8231(POPS, Smoke, 0.0f,
{
  tlvmInitContext(&m_data.context);
  tlvmInit8231A(m_data.context);
},
{
  tlvmTerminateContext(&m_data.context);
},
{
  tlvmByte* cmd = NULL;
  tlvmByte* db  = NULL;
  tlvmGetPort(m_data.context, TLVM_8231A_PORT_CMD, &cmd);
  tlvmGetPort(m_data.context, TLVM_8231A_PORT_DB, &db);

  // first of all, we want 2 16 bit numbers
  tlvmShort A = 550;
  tlvmShort B = 25;
  tlvmShort R = 0;
  // Then we push them onto the 8231's stack
  // 1 byte at a time
  WRITE_DATA_8231A(((tlvmByte*)&A)[1]);
  WRITE_DATA_8231A(((tlvmByte*)&A)[0]);
  WRITE_DATA_8231A(((tlvmByte*)&B)[1]);
  WRITE_DATA_8231A(((tlvmByte*)&B)[0]);

  WRITE_COMMAND_8231A(TLVM_8231A_POPS);
  
  READ_DATA_8231A(((tlvmByte*)&R)[0]);
  READ_DATA_8231A(((tlvmByte*)&R)[1]);
  
  ASSERT(R == A);
},
{
  tlvmContext* context;
})