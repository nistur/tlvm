/*
Copyright (c) 2015 Philipp Geyer

This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not
   claim that you wrote the original software. If you use this software
   in a product, an acknowledgement in the product documentation would be
   appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be
   misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.

Philipp Geyer
nistur@gmail.com
*/

#include "../tlvm-tests.h"
#ifdef TLVM_HAS_6303

TEST(InitTerminate, CPU_6303, 0.0f,
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
      ASSERT(tlvmInitContext(&m_data.context, TLVM_CPU_6303) == TLVM_SUCCESS);
      ASSERT(m_data.context != NULL);
      ASSERT(tlvmTerminateContext(&m_data.context) == TLVM_SUCCESS);
     },
     // data
     {
      tlvmContext* context;
     }
    );
#endif/*TLVM_HAS_6303*/
