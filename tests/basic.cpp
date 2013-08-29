#include "tlvm-tests.h"
#include "tlvm.h"

TEST(InitTerminate, Basic, 0.0f,
     // initialisation
     {
      m_data.context = 0;
     },
     // cleanup
     {
      tlvmTerminateContext(&m_data.context);
     },
     // test
     {
      ASSERT(tlvmInitContext(&m_data.context) == TLVM_SUCCESS);
      ASSERT(m_data.context != NULL);
      ASSERT(tlvmTerminateContext(&m_data.context) == TLVM_SUCCESS);
     },
     // data
     {
      tlvmContext* context;
     }
    );

TEST(SetMemory, Basic, 0.0f,
     // initialisation
     {
      tlvmInitContext(&m_data.context);
     },
     // cleanup
     {
      tlvmTerminateContext(&m_data.context);
     },
     // test
     {
          // no context
          ASSERT(tlvmSetMemoryBuffer(NULL, m_data.memory, 255) == TLVM_NO_CONTEXT);

          // no buffer
          ASSERT(tlvmSetMemoryBuffer(m_data.context, NULL, 255) == TLVM_NO_MEMORY);

          // zero size
          ASSERT(tlvmSetMemoryBuffer(m_data.context, m_data.memory, 0) == TLVM_INVALID_INPUT);

          // valid input
          ASSERT(tlvmSetMemoryBuffer(m_data.context, m_data.memory, 255) == TLVM_SUCCESS);
      
     },
     // data
     {
      tlvmContext* context;
      tlvmByte     memory[255];
     }
    );

TEST(LoadBootloader, Basic, 0.0f,
     // initialisation
     {
      tlvmInitContext(&m_data.context);
     },
     // cleanup
     {
      tlvmTerminateContext(&m_data.context);
     },
     // test
     {
          // no context
          ASSERT(tlvmLoadBootloader(NULL, m_data.bootloader) == TLVM_NO_CONTEXT);

          // no buffer
          ASSERT(tlvmLoadBootloader(m_data.context, NULL) == TLVM_INVALID_INPUT);

          // valid input
          ASSERT(tlvmLoadBootloader(m_data.context, m_data.bootloader) == TLVM_SUCCESS);
      
     },
     // data
     {
      tlvmContext* context;
      tlvmByte     bootloader[256];
     }
    );
