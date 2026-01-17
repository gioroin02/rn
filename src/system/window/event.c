#ifndef P_SYSTEM_WINDOW_EVENT_C
#define P_SYSTEM_WINDOW_EVENT_C

#include "event.h"

PWindowEvent
pWindowEventNone()
{
    PWindowEvent result;

    pMemorySet(&result, sizeof result, 0xAB);

    result.kind = PWindowEvent_None;

    return result;
}

PWindowEvent
pWindowEventQuit(void* self)
{
    PWindowEvent result;

    pMemorySet(&result, sizeof result, 0xAB);

    result.kind = PWindowEvent_Quit;
    result.self = self;

    return result;
}

PWindowEvent
pWindowEventWindowCreate(void* self)
{
    PWindowEvent result;

    pMemorySet(&result, sizeof result, 0xAB);

    result.kind = PWindowEvent_WindowCreate;
    result.self = self;

    return result;
}

PWindowEvent
pWindowEventWindowDestroy(void* self)
{
    PWindowEvent result;

    pMemorySet(&result, sizeof result, 0xAB);

    result.kind = PWindowEvent_WindowDestroy;
    result.self = self;

    return result;
}

PWindowEvent
pWindowEventKeyboardKey(void* self, PWindowKeyboardKey key, b32 pressed, ssize scan)
{
    PWindowEvent result;

    pMemorySet(&result, sizeof result, 0xAB);

    result.kind                 = PWindowEvent_KeyboardKey;
    result.self                 = self;
    result.keyboard_key.key     = key;
    result.keyboard_key.pressed = pressed != 0 ? 1 : 0;
    result.keyboard_key.scan    = scan;

    return result;
}

#endif // P_SYSTEM_WINDOW_EVENT_C
