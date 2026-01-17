#ifndef P_SYSTEM_WINDOW_EVENT_H
#define P_SYSTEM_WINDOW_EVENT_H

#include "import.h"

typedef enum PWindowKeyboardKey
{
    PWindowKeyboardKey_None,
    PWindowKeyboardKey_A,
    PWindowKeyboardKey_B,
    PWindowKeyboardKey_C,
    PWindowKeyboardKey_D,
    PWindowKeyboardKey_E,
    PWindowKeyboardKey_F,
    PWindowKeyboardKey_G,
    PWindowKeyboardKey_H,
    PWindowKeyboardKey_I,
    PWindowKeyboardKey_J,
    PWindowKeyboardKey_K,
    PWindowKeyboardKey_L,
    PWindowKeyboardKey_M,
    PWindowKeyboardKey_N,
    PWindowKeyboardKey_O,
    PWindowKeyboardKey_P,
    PWindowKeyboardKey_Q,
    PWindowKeyboardKey_R,
    PWindowKeyboardKey_S,
    PWindowKeyboardKey_T,
    PWindowKeyboardKey_U,
    PWindowKeyboardKey_V,
    PWindowKeyboardKey_W,
    PWindowKeyboardKey_X,
    PWindowKeyboardKey_Y,
    PWindowKeyboardKey_Z,
    PWindowKeyboardKey_0,
    PWindowKeyboardKey_1,
    PWindowKeyboardKey_2,
    PWindowKeyboardKey_3,
    PWindowKeyboardKey_4,
    PWindowKeyboardKey_5,
    PWindowKeyboardKey_6,
    PWindowKeyboardKey_7,
    PWindowKeyboardKey_8,
    PWindowKeyboardKey_9,
    PWindowKeyboardKey_Space,
    PWindowKeyboardKey_Minus,
    PWindowKeyboardKey_Equal,
    PWindowKeyboardKey_SquareLeft,
    PWindowKeyboardKey_SquareRight,
    PWindowKeyboardKey_BackSlash,
    PWindowKeyboardKey_SemiColon,
    PWindowKeyboardKey_Apostrophe,
    PWindowKeyboardKey_Grave,
    PWindowKeyboardKey_Comma,
    PWindowKeyboardKey_Period,
    PWindowKeyboardKey_Slash,
    PWindowKeyboardKey_Up,
    PWindowKeyboardKey_Down,
    PWindowKeyboardKey_Left,
    PWindowKeyboardKey_Right,
    PWindowKeyboardKey_Home,
    PWindowKeyboardKey_End,
    PWindowKeyboardKey_PageUp,
    PWindowKeyboardKey_PageDown,
    PWindowKeyboardKey_Insert,
    PWindowKeyboardKey_Delete,
    PWindowKeyboardKey_F1,
    PWindowKeyboardKey_F2,
    PWindowKeyboardKey_F3,
    PWindowKeyboardKey_F4,
    PWindowKeyboardKey_F5,
    PWindowKeyboardKey_F6,
    PWindowKeyboardKey_F7,
    PWindowKeyboardKey_F8,
    PWindowKeyboardKey_F9,
    PWindowKeyboardKey_F10,
    PWindowKeyboardKey_F11,
    PWindowKeyboardKey_F12,
    PWindowKeyboardKey_Enter,
    PWindowKeyboardKey_Escape,
    PWindowKeyboardKey_BackSpace,
    PWindowKeyboardKey_Tab,
}
PWindowKeyboardKey;

typedef enum PWindowEventKind
{
    PWindowEvent_None,
    PWindowEvent_Quit,
    PWindowEvent_WindowCreate,
    PWindowEvent_WindowDestroy,
    PWindowEvent_KeyboardKey,
}
PWindowEventKind;

typedef struct PWindowEventKeyboardKey
{
    PWindowKeyboardKey key;

    b32   pressed;
    ssize scan;
}
PWindowEventKeyboardKey;

typedef struct PWindowEvent
{
    PWindowEventKind kind;

    void* self;

    union
    {
        PWindowEventKeyboardKey keyboard_key;
    };
}
PWindowEvent;

PWindowEvent
pWindowEventNone();

PWindowEvent
pWindowEventQuit(void* self);

PWindowEvent
pWindowEventWindowCreate(void* self);

PWindowEvent
pWindowEventWindowDestroy(void* self);

PWindowEvent
pWindowEventKeyboardKey(void* self, PWindowKeyboardKey key, b32 pressed, ssize scan);

#endif // P_SYSTEM_WINDOW_EVENT_H
