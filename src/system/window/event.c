#ifndef RHO_SYSTEM_WINDOW_EVENT_C
#define RHO_SYSTEM_WINDOW_EVENT_C

#include "event.h"

RWindowEvent rho_window_event_none()
{
    RWindowEvent result = {0};

    rho_memory_set(&result, sizeof result, 0xAB);

    result.kind = RWindowEvent_None;

    return result;
}

RWindowEvent rho_window_event_quit(void* window)
{
    RWindowEvent result = {0};

    rho_memory_set(&result, sizeof result, 0xAB);

    result.kind        = RWindowEvent_Quit;
    result.quit.window = window;

    return result;
}

RWindowEvent rho_window_event_keyboard_key(void* window, RWindowKeyboardKey key, RBool32 pressed, RInt scan)
{
    RWindowEvent result = {0};

    rho_memory_set(&result, sizeof result, 0xAB);

    result.kind                 = RWindowEvent_KeyboardKey;
    result.keyboard_key.window  = window;
    result.keyboard_key.key     = key;
    result.keyboard_key.pressed = pressed != 0 ? 1 : 0;
    result.keyboard_key.scan    = scan;

    return result;
}

#endif
