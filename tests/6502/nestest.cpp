#ifdef TLVM_HAS_6502
#ifdef TEST_HAS_NESTEST
#include "../tlvm-tests.h"
#include <stdio.h>

TEST(NESTEST, CPU_6502_Smoke, 0.0f,
     // initialisation
     {
      tlvmInitContext(&m_data.context, TLVM_CPU_6502);

      FILE* fp = fopen("bin/6502/nestest.nes", "r");
      if(fp != NULL)
      {
          fseek(fp, 0, SEEK_END);
          long size = ftell(fp);

          m_data.ROM = new tlvmByte[size];
          fread(m_data.ROM, 1, size, fp);

          tlvmSetMemory(m_data.context, m_data.ROM, 0x8000, size, TLVM_FLAG_READ);
      }
     },
     // cleanup
     {
      tlvmTerminateContext(&m_data.context);
      if( m_data.ROM )
      {
          free(m_data.ROM);
          m_data.ROM = NULL;
      }
     },
     // test
     {
         ASSERT(m_data.ROM);
         tlvmReset(m_data.context);
         m_data.context->m_ProgramCounter = 0xC000;
         ASSERT(tlvmRun(m_data.context) == TLVM_SUCCESS);
     },
     // data
     {
      tlvmContext* context;
      tlvmByte*    ROM;
      
     }
    );

#endif/*TEST_HAS_NESTEST*/
#endif/*TLVM_HAS_6502*/
