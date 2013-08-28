#include "tlvm-tests.h"
#include "tlvm.h"

TEST(InitTerminate, FPU, 0.0f,
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
          ASSERT(tlvmAddFPU(m_data.context) == TLVM_SUCCESS);
      
     },
     // data
     {
      tlvmContext* context;
     }
    );