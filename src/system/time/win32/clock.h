#ifndef P_SYSTEM_WIN32_TIME_CLOCK_H
#define P_SYSTEM_WIN32_TIME_CLOCK_H

#include "import.h"

#define WIN32_LEAN_AND_MEAN
#define NOGDI

#include <windows.h>

typedef struct PWin32Clock
{
    LARGE_INTEGER frequency;
    LARGE_INTEGER counter;
}
PWin32Clock;

PWin32Clock* pWin32ClockReserve(PMemoryArena* arena);

B32 pWin32ClockCreate(PWin32Clock* self);

void pWin32ClockDestroy(PWin32Clock* self);

F32 pWin32ClockElapsed(PWin32Clock* self);

#endif
