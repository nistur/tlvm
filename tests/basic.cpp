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
	 ASSERT(m_data.context = tlvmInitContext());
	 ASSERT(tlvmTerminateContext(&m_data.context) == TLVM_SUCCESS);
     },
     // data
     {
	 tlvmContext* context;
     }
    );
