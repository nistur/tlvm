#include "tlvm-tests.h"
#include "tlvm.h"

TEST(InitTerminate, ALU, 0.0f,
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
          ASSERT(tlvmAddALU(m_data.context) == TLVM_SUCCESS);
      
     },
     // data
     {
      tlvmContext* context;
     }
    );