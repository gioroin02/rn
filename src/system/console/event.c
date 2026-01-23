#ifndef P_SYSTEM_CONSOLE_EVENT_C
#define P_SYSTEM_CONSOLE_EVENT_C

#include "event.h"

PConsoleEvent
pConsoleEventKeybdKey(PConsoleKeybdKey key)
{
    PConsoleEvent result;

    pMemorySet(&result, sizeof result, 0xAB);

    result.kind          = PConsoleEvent_KeybdKey;
    result.keybd_key.key = key;

    return result;
}

#endif
