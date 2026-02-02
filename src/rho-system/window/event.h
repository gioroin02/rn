#ifndef RHO_SYSTEM_WINDOW_EVENT_H
#define RHO_SYSTEM_WINDOW_EVENT_H

#include "import.h"

typedef enum RWindowKeyboardKey
{
    RWindowKeyboard_None,
    RWindowKeyboard_A,
    RWindowKeyboard_B,
    RWindowKeyboard_C,
    RWindowKeyboard_D,
    RWindowKeyboard_E,
    RWindowKeyboard_F,
    RWindowKeyboard_G,
    RWindowKeyboard_H,
    RWindowKeyboard_I,
    RWindowKeyboard_J,
    RWindowKeyboard_K,
    RWindowKeyboard_L,
    RWindowKeyboard_M,
    RWindowKeyboard_N,
    RWindowKeyboard_O,
    RWindowKeyboard_P,
    RWindowKeyboard_Q,
    RWindowKeyboard_R,
    RWindowKeyboard_S,
    RWindowKeyboard_T,
    RWindowKeyboard_U,
    RWindowKeyboard_V,
    RWindowKeyboard_W,
    RWindowKeyboard_X,
    RWindowKeyboard_Y,
    RWindowKeyboard_Z,
    RWindowKeyboard_0,
    RWindowKeyboard_1,
    RWindowKeyboard_2,
    RWindowKeyboard_3,
    RWindowKeyboard_4,
    RWindowKeyboard_5,
    RWindowKeyboard_6,
    RWindowKeyboard_7,
    RWindowKeyboard_8,
    RWindowKeyboard_9,
    RWindowKeyboard_Space,
    RWindowKeyboard_Minus,
    RWindowKeyboard_Equal,
    RWindowKeyboard_SquareLeft,
    RWindowKeyboard_SquareRight,
    RWindowKeyboard_BackSlash,
    RWindowKeyboard_SemiColon,
    RWindowKeyboard_Apostrophe,
    RWindowKeyboard_Grave,
    RWindowKeyboard_Comma,
    RWindowKeyboard_Period,
    RWindowKeyboard_Slash,
    RWindowKeyboard_Up,
    RWindowKeyboard_Down,
    RWindowKeyboard_Left,
    RWindowKeyboard_Right,
    RWindowKeyboard_Home,
    RWindowKeyboard_End,
    RWindowKeyboard_PageUp,
    RWindowKeyboard_PageDown,
    RWindowKeyboard_Insert,
    RWindowKeyboard_Delete,
    RWindowKeyboard_F1,
    RWindowKeyboard_F2,
    RWindowKeyboard_F3,
    RWindowKeyboard_F4,
    RWindowKeyboard_F5,
    RWindowKeyboard_F6,
    RWindowKeyboard_F7,
    RWindowKeyboard_F8,
    RWindowKeyboard_F9,
    RWindowKeyboard_F10,
    RWindowKeyboard_F11,
    RWindowKeyboard_F12,
    RWindowKeyboard_Enter,
    RWindowKeyboard_Escape,
    RWindowKeyboard_BackSpace,
    RWindowKeyboard_Tab,
}
RWindowKeyboardKey;

typedef enum RWindowEventKind
{
    RWindowEvent_None,
    RWindowEvent_Quit,
    RWindowEvent_Paint,
    RWindowEvent_KeyboardKey,
}
RWindowEventKind;

typedef struct RWindowEventQuit
{
    void* window;
}
RWindowEventQuit;

typedef struct RWindowEventPaint
{
    void* window;
}
RWindowEventPaint;

typedef struct RWindowEventKeyboardKey
{
    void* window;

    RWindowKeyboardKey key;

    RInt    scan;
    RBool32 pressed;
}
RWindowEventKeyboardKey;

typedef struct RWindowEvent
{
    RWindowEventKind kind;

    union
    {
        RWindowEventQuit        quit;
        RWindowEventPaint       paint;
        RWindowEventKeyboardKey keyboard_key;
    };
}
RWindowEvent;

RWindowEvent rho_window_event_none();

RWindowEvent rho_window_event_quit(void* window);

RWindowEvent rho_window_event_paint(void* window);

RWindowEvent rho_window_event_keyboard_key(void* window, RWindowKeyboardKey key, RBool32 pressed, RInt scan);

#endif
