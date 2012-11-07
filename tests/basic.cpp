#include "tmpl-tests.h"
#include "template.h"

TEST(InitTerminate, Basic, 0.0f,
     // initialisation
     {
	 m_data.context = 0;
     },
     // cleanup
     {
	 tmplTerminateContext(&m_data.context);
     },
     // test
     {
	 ASSERT(m_data.context = tmplInitContext());
	 ASSERT(tmplTerminateContext(&m_data.context) == TMPL_SUCCESS);
     },
     // data
     {
	 tmplContext* context;
     }
    );
