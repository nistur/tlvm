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

#include "tlvm_internal.h"

#include <sys/time.h> // gettimeofday
#include <unistd.h>   // usleep

tlvmLong tlvmGetTime()
{
	struct timeval time;
	gettimeofday(&time, 0);
	return (((tlvmLong)time.tv_sec) << 32) | (tlvmLong)time.tv_usec;
}


tlvmReturn tlvmResetClock(tlvmContext* context)
{
    TLVM_NULL_CHECK(context, NO_CONTEXT);

	context->m_StartTime = tlvmGetTime();

	TLVM_RETURN_CODE(SUCCESS);
}

tlvmReturn tlvmSleepUntil(tlvmContext* context, tlvmLong cycles)
{
    TLVM_NULL_CHECK(context, NO_CONTEXT);

    TLVM_NULL_CHECK(context->m_StartTime, INVALID_INPUT);
    TLVM_NULL_CHECK(context->m_Clockspeed, INVALID_INPUT);

	tlvmLong time = tlvmGetTime();
	tlvmLong dt = time - context->m_StartTime - context->m_TimeOffset;
	tlvmLong mhz = context->m_Clockspeed >> 10;
	tlvmLong khz = context->m_Clockspeed & 0x3FF;

	tlvmLong desiredTime = cycles;
	desiredTime *= 1000;
	if(khz > 0)
		desiredTime /= (khz * 1000);
	desiredTime *= 1000;
	if(mhz > 0)
		desiredTime /= (mhz * 1000000);

	desiredTime -= dt >= desiredTime ? desiredTime : dt;

	if(desiredTime > 0)
		usleep(desiredTime);

	TLVM_RETURN_CODE(SUCCESS);
}

tlvmReturn tlvmPauseClock(tlvmContext* context)
{
    TLVM_NULL_CHECK(context, NO_CONTEXT);

	context->m_TimeOffset -= tlvmGetTime();

	TLVM_RETURN_CODE(SUCCESS);
}

tlvmReturn tlvmResumeClock(tlvmContext* context)
{
    TLVM_NULL_CHECK(context, NO_CONTEXT);

	context->m_TimeOffset += tlvmGetTime();

	TLVM_RETURN_CODE(SUCCESS);
}