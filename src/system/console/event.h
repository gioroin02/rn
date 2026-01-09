#ifndef PX_SYSTEM_CONSOLE_EVENT_H
#define PX_SYSTEM_CONSOLE_EVENT_H

#include "import.h"

typedef enum PxConsoleKeyboardKey
{
    PxConsoleKeyboardKey_None,
    PxConsoleKeyboardKey_A,
    PxConsoleKeyboardKey_B,
    PxConsoleKeyboardKey_C,
    PxConsoleKeyboardKey_D,
    PxConsoleKeyboardKey_E,
    PxConsoleKeyboardKey_F,
    PxConsoleKeyboardKey_G,
    PxConsoleKeyboardKey_H,
    PxConsoleKeyboardKey_I,
    PxConsoleKeyboardKey_J,
    PxConsoleKeyboardKey_K,
    PxConsoleKeyboardKey_L,
    PxConsoleKeyboardKey_M,
    PxConsoleKeyboardKey_N,
    PxConsoleKeyboardKey_O,
    PxConsoleKeyboardKey_P,
    PxConsoleKeyboardKey_Q,
    PxConsoleKeyboardKey_R,
    PxConsoleKeyboardKey_S,
    PxConsoleKeyboardKey_T,
    PxConsoleKeyboardKey_U,
    PxConsoleKeyboardKey_V,
    PxConsoleKeyboardKey_W,
    PxConsoleKeyboardKey_X,
    PxConsoleKeyboardKey_Y,
    PxConsoleKeyboardKey_Z,
    PxConsoleKeyboardKey_0,
    PxConsoleKeyboardKey_1,
    PxConsoleKeyboardKey_2,
    PxConsoleKeyboardKey_3,
    PxConsoleKeyboardKey_4,
    PxConsoleKeyboardKey_5,
    PxConsoleKeyboardKey_6,
    PxConsoleKeyboardKey_7,
    PxConsoleKeyboardKey_8,
    PxConsoleKeyboardKey_9,
    PxConsoleKeyboardKey_Space,
    PxConsoleKeyboardKey_Minus,
    PxConsoleKeyboardKey_Equal,
    PxConsoleKeyboardKey_SquareLeft,
    PxConsoleKeyboardKey_SquareRight,
    PxConsoleKeyboardKey_BackSlash,
    PxConsoleKeyboardKey_SemiColon,
    PxConsoleKeyboardKey_Apostrophe,
    PxConsoleKeyboardKey_Grave,
    PxConsoleKeyboardKey_Comma,
    PxConsoleKeyboardKey_Period,
    PxConsoleKeyboardKey_Slash,
    PxConsoleKeyboardKey_Up,
    PxConsoleKeyboardKey_Down,
    PxConsoleKeyboardKey_Left,
    PxConsoleKeyboardKey_Right,
    PxConsoleKeyboardKey_Home,
    PxConsoleKeyboardKey_End,
    PxConsoleKeyboardKey_PageUp,
    PxConsoleKeyboardKey_PageDown,
    PxConsoleKeyboardKey_Insert,
    PxConsoleKeyboardKey_Delete,
    PxConsoleKeyboardKey_F1,
    PxConsoleKeyboardKey_F2,
    PxConsoleKeyboardKey_F3,
    PxConsoleKeyboardKey_F4,
    PxConsoleKeyboardKey_F5,
    PxConsoleKeyboardKey_F6,
    PxConsoleKeyboardKey_F7,
    PxConsoleKeyboardKey_F8,
    PxConsoleKeyboardKey_F9,
    PxConsoleKeyboardKey_F10,
    PxConsoleKeyboardKey_F11,
    PxConsoleKeyboardKey_F12,
    PxConsoleKeyboardKey_Enter,
    PxConsoleKeyboardKey_Escape,
    PxConsoleKeyboardKey_BackSpace,
    PxConsoleKeyboardKey_Tab,
}
PxConsoleKeyboardKey;

typedef enum PxConsoleEventKind
{
    PxConsoleEvent_None,
    PxConsoleEvent_KeyboardKey,
}
PxConsoleEventKind;

typedef struct PxConsoleEventKeyboardKey
{
    PxConsoleKeyboardKey key;
}
PxConsoleEventKeyboardKey;

typedef struct PxConsoleEvent
{
    PxConsoleEventKind kind;

    union
    {
        PxConsoleEventKeyboardKey keyboard_key;
    };
}
PxConsoleEvent;

PxConsoleEvent
pxConsoleEventKeyboardKey(PxConsoleKeyboardKey key);

#endif // PX_SYSTEM_CONSOLE_EVENT_H
