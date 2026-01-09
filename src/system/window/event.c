#ifndef PX_SYSTEM_WINDOW_EVENT_C
#define PX_SYSTEM_WINDOW_EVENT_C

#include "event.h"

PxWindowEvent
pxWindowEventQuit()
{
    PxWindowEvent result;

    pxMemorySet(&result, sizeof result, 0xAB);

    result.kind = PxWindowEvent_Quit;

    return result;
}

PxWindowEvent
pxWindowEventKeyboardKey(PxWindowKeyboardKey key, b32 pressed, ssize scan)
{
    PxWindowEvent result;

    pxMemorySet(&result, sizeof result, 0xAB);

    result.kind                 = PxWindowEvent_KeyboardKey;
    result.keyboard_key.key     = key;
    result.keyboard_key.pressed = pressed != 0 ? 1 : 0;
    result.keyboard_key.scan    = scan;

    return result;
}

#endif // PX_SYSTEM_WINDOW_EVENT_C
