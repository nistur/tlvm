#ifndef __TLVM_TIME_H__
#define __TLVM_TIME_H__

#include "tlvm.h"

tlvmLong   tlvmGetTime();

tlvmReturn tlvmResetClock(tlvmContext* context);

tlvmReturn tlvmSleepUntil(tlvmContext* context, tlvmLong cycles);

tlvmReturn tlvmPauseClock(tlvmContext* context);

tlvmReturn tlvmResumeClock(tlvmContext* context);

#endif/*__TLVM_TIME_H__*/