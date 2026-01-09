#ifndef PX_SYSTEM_WINDOW_EVENT_H
#define PX_SYSTEM_WINDOW_EVENT_H

#include "import.h"

typedef enum PxWindowKeyboardKey
{
    PxWindowKeyboardKey_None,
    PxWindowKeyboardKey_A,
    PxWindowKeyboardKey_B,
    PxWindowKeyboardKey_C,
    PxWindowKeyboardKey_D,
    PxWindowKeyboardKey_E,
    PxWindowKeyboardKey_F,
    PxWindowKeyboardKey_G,
    PxWindowKeyboardKey_H,
    PxWindowKeyboardKey_I,
    PxWindowKeyboardKey_J,
    PxWindowKeyboardKey_K,
    PxWindowKeyboardKey_L,
    PxWindowKeyboardKey_M,
    PxWindowKeyboardKey_N,
    PxWindowKeyboardKey_O,
    PxWindowKeyboardKey_P,
    PxWindowKeyboardKey_Q,
    PxWindowKeyboardKey_R,
    PxWindowKeyboardKey_S,
    PxWindowKeyboardKey_T,
    PxWindowKeyboardKey_U,
    PxWindowKeyboardKey_V,
    PxWindowKeyboardKey_W,
    PxWindowKeyboardKey_X,
    PxWindowKeyboardKey_Y,
    PxWindowKeyboardKey_Z,
    PxWindowKeyboardKey_0,
    PxWindowKeyboardKey_1,
    PxWindowKeyboardKey_2,
    PxWindowKeyboardKey_3,
    PxWindowKeyboardKey_4,
    PxWindowKeyboardKey_5,
    PxWindowKeyboardKey_6,
    PxWindowKeyboardKey_7,
    PxWindowKeyboardKey_8,
    PxWindowKeyboardKey_9,
    PxWindowKeyboardKey_Space,
    PxWindowKeyboardKey_Minus,
    PxWindowKeyboardKey_Equal,
    PxWindowKeyboardKey_SquareLeft,
    PxWindowKeyboardKey_SquareRight,
    PxWindowKeyboardKey_BackSlash,
    PxWindowKeyboardKey_SemiColon,
    PxWindowKeyboardKey_Apostrophe,
    PxWindowKeyboardKey_Grave,
    PxWindowKeyboardKey_Comma,
    PxWindowKeyboardKey_Period,
    PxWindowKeyboardKey_Slash,
    PxWindowKeyboardKey_Up,
    PxWindowKeyboardKey_Down,
    PxWindowKeyboardKey_Left,
    PxWindowKeyboardKey_Right,
    PxWindowKeyboardKey_Home,
    PxWindowKeyboardKey_End,
    PxWindowKeyboardKey_PageUp,
    PxWindowKeyboardKey_PageDown,
    PxWindowKeyboardKey_Insert,
    PxWindowKeyboardKey_Delete,
    PxWindowKeyboardKey_F1,
    PxWindowKeyboardKey_F2,
    PxWindowKeyboardKey_F3,
    PxWindowKeyboardKey_F4,
    PxWindowKeyboardKey_F5,
    PxWindowKeyboardKey_F6,
    PxWindowKeyboardKey_F7,
    PxWindowKeyboardKey_F8,
    PxWindowKeyboardKey_F9,
    PxWindowKeyboardKey_F10,
    PxWindowKeyboardKey_F11,
    PxWindowKeyboardKey_F12,
    PxWindowKeyboardKey_Enter,
    PxWindowKeyboardKey_Escape,
    PxWindowKeyboardKey_BackSpace,
    PxWindowKeyboardKey_Tab,
}
PxWindowKeyboardKey;

typedef enum PxWindowEventKind
{
    PxWindowEvent_None,
    PxWindowEvent_Quit,
    PxWindowEvent_KeyboardKey,
}
PxWindowEventKind;

typedef struct PxWindowEventKeyboardKey
{
    PxWindowKeyboardKey key;

    b32   pressed;
    ssize scan;
}
PxWindowEventKeyboardKey;

typedef struct PxWindowEvent
{
    PxWindowEventKind kind;

    union
    {
        PxWindowEventKeyboardKey keyboard_key;
    };
}
PxWindowEvent;

PxWindowEvent
pxWindowEventQuit();

PxWindowEvent
pxWindowEventKeyboardKey(PxWindowKeyboardKey key, b32 pressed, ssize scan);

#endif // PX_SYSTEM_WINDOW_EVENT_H
