#ifndef RHO_SYSTEM_WINDOW_INPUT_H
#define RHO_SYSTEM_WINDOW_INPUT_H

#include "event.h"

typedef struct RWindowKeyboard
{
    RUint8 state_prev[16];
    RUint8 state_curr[16];
}
RWindowKeyboard;

RWindowKeyboard rho_window_keyboard_make();

void rho_window_keyboard_update(RWindowKeyboard* self, RWindowKeyboardKey key, RBool32 state);

RBool32 rho_window_keyboard_is_active(RWindowKeyboard* self, RWindowKeyboardKey key);

RBool32 rho_window_keyboard_is_starting(RWindowKeyboard* self, RWindowKeyboardKey key);

RBool32 rho_window_keyboard_is_stopping(RWindowKeyboard* self, RWindowKeyboardKey key);

void rho_window_keyboard_on_event(RWindowKeyboard* self, RWindowEventKeyboardKey event);

#endif
