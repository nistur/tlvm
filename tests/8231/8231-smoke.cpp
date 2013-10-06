#include "../tlvm-tests.h"
#include <stdio.h>

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
  
  READ_DATA_8231A(((tlvmByte*)&R)[1]);
  READ_DATA_8231A(((tlvmByte*)&R)[1]);
  READ_DATA_8231A(((tlvmByte*)&R)[0]);
  ASSERT(R == A + B);
},
{
  tlvmContext* context;
})