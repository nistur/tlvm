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
	if(context == NULL)
		tlvmReturnCode(NO_CONTEXT);

	context->m_StartTime = tlvmGetTime();

	tlvmReturnCode(SUCCESS);
}

tlvmReturn tlvmSleepUntil(tlvmContext* context, tlvmLong cycles)
{
	if(context == NULL)
		tlvmReturnCode(NO_CONTEXT);

	if(context->m_StartTime == 0 || context->m_Clockspeed == 0)
		tlvmReturnCode(INVALID_INPUT);

	tlvmLong time = tlvmGetTime();
	tlvmLong dt = time - context->m_StartTime;
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

	tlvmReturnCode(SUCCESS);
}