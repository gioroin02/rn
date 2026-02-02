#ifndef RHO_SYSTEM_WINDOW_INPUT_C
#define RHO_SYSTEM_WINDOW_INPUT_C

#include "input.h"

RWindowKeyboard rho_window_keyboard_make()
{
    RWindowKeyboard result = {0};

    return result;
}

void rho_window_keyboard_update(RWindowKeyboard* self, RWindowKeyboardKey key, RBool32 state)
{
    if (key < 0 || key >= (sizeof self->state_curr * 8))
        return;

    RInt   index = key >> 3;
    RInt   mask  = 1 << (key & 0x7);
    RUint8 prev = self->state_prev[index];
    RUint8 curr = self->state_curr[index];

    prev = (curr & mask) != 0 ?
        prev | mask : prev & ~mask;

    curr = state != 0 ?
        curr | mask : curr & ~mask;

    self->state_prev[index] = prev;
    self->state_curr[index] = curr;
}

RBool32 rho_window_keyboard_is_active(RWindowKeyboard* self, RWindowKeyboardKey key)
{
    if (key < 0 || key >= (sizeof self->state_curr * 8))
        return 0;

    RInt   index = key >> 3;
    RInt   mask  = 1 << (key & 0x7);
    RUint8 curr = self->state_curr[index];

    return (curr & mask) != 0 ? 1 : 0;
}

RBool32 rho_window_keyboard_is_starting(RWindowKeyboard* self, RWindowKeyboardKey key)
{
    if (key < 0 || key >= (sizeof self->state_curr * 8))
        return 0;

    RInt   index = key >> 3;
    RInt   mask  = 1 << (key & 0x7);
    RUint8 curr = self->state_curr[index];
    RUint8 prev = self->state_prev[index];

    return (curr & mask) != 0 && (prev & mask) == 0 ? 1 : 0;
}

RBool32 rho_window_keyboard_is_stopping(RWindowKeyboard* self, RWindowKeyboardKey key)
{
    if (key < 0 || key >= (sizeof self->state_curr * 8))
        return 0;

    RInt   index = key >> 3;
    RInt   mask  = 1 << (key & 0x7);
    RUint8 curr = self->state_curr[index];
    RUint8 prev = self->state_prev[index];

    return (curr & mask) == 0 && (prev & mask) != 0 ? 1 : 0;
}

void rho_window_keyboard_on_event(RWindowKeyboard* self, RWindowEventKeyboardKey event)
{
    if (event.key != RWindowKeyboard_None)
        rho_window_keyboard_update(self, event.key, event.pressed);
}

#endif
