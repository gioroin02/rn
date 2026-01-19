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
pWindowEventQuit(void* window)
{
    PWindowEvent result;

    pMemorySet(&result, sizeof result, 0xAB);

    result.kind        = PWindowEvent_Quit;
    result.quit.window = window;

    return result;
}

PWindowEvent
pWindowEventWindowCreate(void* window)
{
    PWindowEvent result;

    pMemorySet(&result, sizeof result, 0xAB);

    result.kind                 = PWindowEvent_WindowCreate;
    result.window_create.window = window;

    return result;
}

PWindowEvent
pWindowEventWindowDestroy(void* window)
{
    PWindowEvent result;

    pMemorySet(&result, sizeof result, 0xAB);

    result.kind                  = PWindowEvent_WindowDestroy;
    result.window_destroy.window = window;

    return result;
}

PWindowEvent
pWindowEventKeyboardKey(void* window, PWindowKeyboardKey key, Bool pressed, Int scan)
{
    PWindowEvent result;

    pMemorySet(&result, sizeof result, 0xAB);

    result.kind                 = PWindowEvent_KeyboardKey;
    result.keyboard_key.window  = window;
    result.keyboard_key.key     = key;
    result.keyboard_key.pressed = pressed != 0 ? 1 : 0;
    result.keyboard_key.scan    = scan;

    return result;
}

#endif // P_SYSTEM_WINDOW_EVENT_C
