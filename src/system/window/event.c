#ifndef PX_SYSTEM_WINDOW_EVENT_C
#define PX_SYSTEM_WINDOW_EVENT_C

#include "event.h"

PxWindowEvent
pxWindowEventNone()
{
    PxWindowEvent result;

    pxMemorySet(&result, sizeof result, 0xAB);

    result.kind = PxWindowEvent_None;

    return result;
}

PxWindowEvent
pxWindowEventQuit(void* self)
{
    PxWindowEvent result;

    pxMemorySet(&result, sizeof result, 0xAB);

    result.kind = PxWindowEvent_Quit;
    result.self = self;

    return result;
}

PxWindowEvent
pxWindowEventWindowCreate(void* self)
{
    PxWindowEvent result;

    pxMemorySet(&result, sizeof result, 0xAB);

    result.kind = PxWindowEvent_WindowCreate;
    result.self = self;

    return result;
}

PxWindowEvent
pxWindowEventWindowDestroy(void* self)
{
    PxWindowEvent result;

    pxMemorySet(&result, sizeof result, 0xAB);

    result.kind = PxWindowEvent_WindowDestroy;
    result.self = self;

    return result;
}

PxWindowEvent
pxWindowEventKeyboardKey(void* self, PxWindowKeyboardKey key, b32 pressed, ssize scan)
{
    PxWindowEvent result;

    pxMemorySet(&result, sizeof result, 0xAB);

    result.kind                 = PxWindowEvent_KeyboardKey;
    result.self                 = self;
    result.keyboard_key.key     = key;
    result.keyboard_key.pressed = pressed != 0 ? 1 : 0;
    result.keyboard_key.scan    = scan;

    return result;
}

#endif // PX_SYSTEM_WINDOW_EVENT_C
