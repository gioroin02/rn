#ifndef P_SYSTEM_CONSOLE_EVENT_H
#define P_SYSTEM_CONSOLE_EVENT_H

#include "import.h"

typedef enum PConsoleKeybdKey
{
    PConsoleKeybd_None,
    PConsoleKeybd_A,
    PConsoleKeybd_B,
    PConsoleKeybd_C,
    PConsoleKeybd_D,
    PConsoleKeybd_E,
    PConsoleKeybd_F,
    PConsoleKeybd_G,
    PConsoleKeybd_H,
    PConsoleKeybd_I,
    PConsoleKeybd_J,
    PConsoleKeybd_K,
    PConsoleKeybd_L,
    PConsoleKeybd_M,
    PConsoleKeybd_N,
    PConsoleKeybd_O,
    PConsoleKeybd_P,
    PConsoleKeybd_Q,
    PConsoleKeybd_R,
    PConsoleKeybd_S,
    PConsoleKeybd_T,
    PConsoleKeybd_U,
    PConsoleKeybd_V,
    PConsoleKeybd_W,
    PConsoleKeybd_X,
    PConsoleKeybd_Y,
    PConsoleKeybd_Z,
    PConsoleKeybd_0,
    PConsoleKeybd_1,
    PConsoleKeybd_2,
    PConsoleKeybd_3,
    PConsoleKeybd_4,
    PConsoleKeybd_5,
    PConsoleKeybd_6,
    PConsoleKeybd_7,
    PConsoleKeybd_8,
    PConsoleKeybd_9,
    PConsoleKeybd_Space,
    PConsoleKeybd_Minus,
    PConsoleKeybd_Equal,
    PConsoleKeybd_SquareLeft,
    PConsoleKeybd_SquareRight,
    PConsoleKeybd_BackSlash,
    PConsoleKeybd_SemiColon,
    PConsoleKeybd_Apostrophe,
    PConsoleKeybd_Grave,
    PConsoleKeybd_Comma,
    PConsoleKeybd_Period,
    PConsoleKeybd_Slash,
    PConsoleKeybd_Up,
    PConsoleKeybd_Down,
    PConsoleKeybd_Left,
    PConsoleKeybd_Right,
    PConsoleKeybd_Home,
    PConsoleKeybd_End,
    PConsoleKeybd_PageUp,
    PConsoleKeybd_PageDown,
    PConsoleKeybd_Insert,
    PConsoleKeybd_Delete,
    PConsoleKeybd_F1,
    PConsoleKeybd_F2,
    PConsoleKeybd_F3,
    PConsoleKeybd_F4,
    PConsoleKeybd_F5,
    PConsoleKeybd_F6,
    PConsoleKeybd_F7,
    PConsoleKeybd_F8,
    PConsoleKeybd_F9,
    PConsoleKeybd_F10,
    PConsoleKeybd_F11,
    PConsoleKeybd_F12,
    PConsoleKeybd_Enter,
    PConsoleKeybd_Escape,
    PConsoleKeybd_BackSpace,
    PConsoleKeybd_Tab,
}
PConsoleKeybdKey;

typedef enum PConsoleEventKind
{
    PConsoleEvent_None,
    PConsoleEvent_KeybdKey,
}
PConsoleEventKind;

typedef struct PConsoleEventKeybdKey
{
    PConsoleKeybdKey key;
}
PConsoleEventKeybdKey;

typedef struct PConsoleEvent
{
    PConsoleEventKind kind;

    union
    {
        PConsoleEventKeybdKey keybd_key;
    };
}
PConsoleEvent;

PConsoleEvent
pConsoleEventKeybdKey(PConsoleKeybdKey key);

#endif // P_SYSTEM_CONSOLE_EVENT_H
