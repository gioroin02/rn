#ifndef PX_SYSTEM_CONSOLE_EVENT_C
#define PX_SYSTEM_CONSOLE_EVENT_C

#include "event.h"

PxConsoleEvent
pxConsoleEventKeyboardKey(PxConsoleKeyboardKey key)
{
    PxConsoleEvent result;

    pxMemorySet(&result, sizeof result, 0xAB);

    result.kind             = PxConsoleEvent_KeyboardKey;
    result.keyboard_key.key = key;

    return result;
}

#endif // PX_SYSTEM_CONSOLE_EVENT_C
