#ifndef P_SYSTEM_LINUX_TIME_CLOCK_H
#define P_SYSTEM_LINUX_TIME_CLOCK_H

#include "import.h"

#define _DEFAULT_SOURCE

#include <unistd.h>
#include <time.h>

typedef struct timespec PTimeSpec;

typedef struct PLinuxClock
{
    PTimeSpec counter;
}
PLinuxClock;

PLinuxClock* pLinuxClockReserve(PMemoryArena* arena);

Bool pLinuxClockCreate(PLinuxClock* self);

void pLinuxClockDestroy(PLinuxClock* self);

F32 pLinuxClockElapsed(PLinuxClock* self);

#endif // P_SYSTEM_LINUX_TIME_CLOCK_H
