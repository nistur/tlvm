#include "../tlvm-tests.h"

TEST_8231(InstructionSet, Basic, 0.0f,
     // initialisation
     {
      tlvmInitContext(&m_data.context);
      tlvmInit8231A(m_data.context);
      memset(m_data.validInstructions, 0, 256);
      // floating point instructions
      m_data.validInstructions[0x06] = 1;
      m_data.validInstructions[0x05] = 1;
      m_data.validInstructions[0x07] = 1;
      m_data.validInstructions[0x15] = 1;
      m_data.validInstructions[0x03] = 1;
      m_data.validInstructions[0x0A] = 1;
      m_data.validInstructions[0x10] = 1;
      m_data.validInstructions[0x13] = 1;
      m_data.validInstructions[0x1C] = 1;
      m_data.validInstructions[0x1D] = 1;
      m_data.validInstructions[0x12] = 1;
      m_data.validInstructions[0x11] = 1;
      m_data.validInstructions[0x08] = 1;
      m_data.validInstructions[0x09] = 1;
      m_data.validInstructions[0x18] = 1;
      m_data.validInstructions[0x17] = 1;
      m_data.validInstructions[0x1A] = 1;
      m_data.validInstructions[0x0B] = 1;
      m_data.validInstructions[0x02] = 1;
      m_data.validInstructions[0x01] = 1;
      m_data.validInstructions[0x04] = 1;
      m_data.validInstructions[0x19] = 1;
      // double precision fixed point instructions
      m_data.validInstructions[0x34] = 1;
      m_data.validInstructions[0x2C] = 1;
      m_data.validInstructions[0x2F] = 1;
      m_data.validInstructions[0x2E] = 1;
      m_data.validInstructions[0x36] = 1;
      m_data.validInstructions[0x2D] = 1;
      m_data.validInstructions[0x1E] = 1;
      m_data.validInstructions[0x38] = 1;
      m_data.validInstructions[0x37] = 1;
      m_data.validInstructions[0x39] = 1;
      // single precision fixed point instructions
      m_data.validInstructions[0x74] = 1;
      m_data.validInstructions[0x1F] = 1;
      m_data.validInstructions[0x78] = 1;
      m_data.validInstructions[0x77] = 1;
      m_data.validInstructions[0x6C] = 1;
      m_data.validInstructions[0x6F] = 1;
      m_data.validInstructions[0x6E] = 1;
      m_data.validInstructions[0x76] = 1;
      m_data.validInstructions[0x6D] = 1;
      m_data.validInstructions[0x79] = 1;
      m_data.validInstructions[0x00] = 1;
     },
     // cleanup
     {
      tlvmTerminateContext(&m_data.context);
     },
     // test
     {
        for(unsigned int i = 0; i < 256; ++i)
          if(m_data.validInstructions[i] != 0)
            ASSERT(((_tlvmContext*)m_data.context)->m_InstructionSet[i] != NULL);
     },
     // data
     {
      tlvmContext* context;
      tlvmByte validInstructions[256];
     }
    );

TEST_8231(GetDB, Basic, 0.0f,
{
  tlvmInitContext(&m_data.context);
  tlvmInit8231A(m_data.context);
},
{
  tlvmTerminateContext(&m_data.context);
},
{
  tlvmByte* databuffer = NULL;
  ASSERT(tlvmGetPort(m_data.context, 1, &databuffer) == TLVM_SUCCESS);
  ASSERT(databuffer != NULL);
  ASSERT(databuffer == &m_data.context->m_Ports[TLVM_8231A_PORT_DB]);
},
{
  tlvmContext* context;
})
#include <stdio.h>
TEST_8231(WriteCommand, Basic, 0.0f,
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
  tlvmByte* svr  = NULL;
  tlvmGetPort(m_data.context, TLVM_8231A_PORT_CMD, &cmd);
  tlvmGetPort(m_data.context, TLVM_8231A_PORT_DB, &db);
  tlvmGetPort(m_data.context, TLVM_8231A_PORT_SVR, &svr);

  STEP(SET_LOW_8231A(CS));
  STEP(SET_HIGH_8231A(A0));
  STEP(SET_LOW_8231A(WR));

  while((*cmd & TLVM_8231A_CMD_READY))
    STEP({});

  STEP(*db = 0x6C); // Random command

  STEP(SET_HIGH_8231A(WR));
  ASSERT(m_data.context->m_Registers[TLVM_8231A_COMMAND] == *db); // finally written it to the command buffer
  STEP(SET_LOW_8231A(A0));
  STEP(SET_HIGH_8231A(CS));
  while((*cmd & TLVM_8231A_CMD_END))
    STEP({});
  STEP(SET_LOW_8231A_SVR(EACK));
  while(!(*cmd & TLVM_8231A_CMD_END))
    STEP({});
  STEP(SET_HIGH_8231A_SVR(EACK));
},
{
  tlvmContext* context;
})

TEST_8231(WriteData, Basic, 0.0f,
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
  tlvmByte* svr  = NULL;
  tlvmGetPort(m_data.context, TLVM_8231A_PORT_CMD, &cmd);
  tlvmGetPort(m_data.context, TLVM_8231A_PORT_DB, &db);
  tlvmGetPort(m_data.context, TLVM_8231A_PORT_SVR, &svr);

  STEP(SET_LOW_8231A(CS));
  STEP(SET_LOW_8231A(A0));
  STEP(SET_LOW_8231A(WR));

  while((*cmd & TLVM_8231A_CMD_READY))
    STEP({});

  STEP(*db = 0x6E); // Random value

  STEP(SET_HIGH_8231A(WR));
  ASSERT(m_data.context->m_Registers[m_data.context->m_StackPointer] == *db); // finally written it to the command buffer
  STEP(SET_HIGH_8231A(A0));
  STEP(SET_HIGH_8231A(CS));
},
{
  tlvmContext* context;
})

TEST_8231(ReadData, Basic, 0.0f,
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
  tlvmByte* svr  = NULL;
  tlvmGetPort(m_data.context, TLVM_8231A_PORT_CMD, &cmd);
  tlvmGetPort(m_data.context, TLVM_8231A_PORT_DB, &db);
  tlvmGetPort(m_data.context, TLVM_8231A_PORT_SVR, &svr);

  m_data.context->m_Registers[m_data.context->m_StackPointer] = 0x6E; // stick random value in the stack
  STEP(SET_LOW_8231A(CS));
  STEP(SET_LOW_8231A(A0));
  STEP(SET_LOW_8231A(RD));

  while((*cmd & TLVM_8231A_CMD_READY))
    STEP({});

  STEP(SET_HIGH_8231A(RD));
  ASSERT(*db == 0x6E); // Random value
  STEP(SET_HIGH_8231A(A0));
  STEP(SET_HIGH_8231A(CS));
},
{
  tlvmContext* context;
})

TEST_8231(Stack, Basic, 0.0f,
{
  tlvmInitContext(&m_data.context);
  tlvmInit8231A(m_data.context);
},
{
  tlvmTerminateContext(&m_data.context);
},
{
  tlvmByte val = 55;
  tlvm8231AStackPush(m_data.context, val);
  ASSERT(m_data.context->m_Registers[m_data.context->m_StackPointer] == val);
  tlvmByte res = tlvm8231AStackPop(m_data.context);
  ASSERT(val == res);

  // also, try pushing 2 16 bit numbers on and popping them off
  tlvmShort A = 550;
  tlvmShort B = 25;
  // push A1 A0, B1, B0
  tlvm8231AStackPush(m_data.context, ((tlvmByte*)&A)[1]);
  tlvm8231AStackPush(m_data.context, ((tlvmByte*)&A)[0]);
  tlvm8231AStackPush(m_data.context, ((tlvmByte*)&B)[1]);
  tlvm8231AStackPush(m_data.context, ((tlvmByte*)&B)[0]);

  tlvmShort resA = 0;
  tlvmShort resB = 0;

  // pop in reverse order, B0 B1, A0 A1
  ((tlvmByte*)&resB)[0] = tlvm8231AStackPop(m_data.context);
  ((tlvmByte*)&resB)[1] = tlvm8231AStackPop(m_data.context);
  ((tlvmByte*)&resA)[0] = tlvm8231AStackPop(m_data.context);
  ((tlvmByte*)&resA)[1] = tlvm8231AStackPop(m_data.context);

  ASSERT(A == resA && B == resB);
},
{
  tlvmContext* context;
})