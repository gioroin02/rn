#ifndef P_SYSTEM_WINDOW_EVENT_H
#define P_SYSTEM_WINDOW_EVENT_H

#include "import.h"

typedef enum PWindowKeybdKey
{
    PWindowKeybd_None,
    PWindowKeybd_A,
    PWindowKeybd_B,
    PWindowKeybd_C,
    PWindowKeybd_D,
    PWindowKeybd_E,
    PWindowKeybd_F,
    PWindowKeybd_G,
    PWindowKeybd_H,
    PWindowKeybd_I,
    PWindowKeybd_J,
    PWindowKeybd_K,
    PWindowKeybd_L,
    PWindowKeybd_M,
    PWindowKeybd_N,
    PWindowKeybd_O,
    PWindowKeybd_P,
    PWindowKeybd_Q,
    PWindowKeybd_R,
    PWindowKeybd_S,
    PWindowKeybd_T,
    PWindowKeybd_U,
    PWindowKeybd_V,
    PWindowKeybd_W,
    PWindowKeybd_X,
    PWindowKeybd_Y,
    PWindowKeybd_Z,
    PWindowKeybd_0,
    PWindowKeybd_1,
    PWindowKeybd_2,
    PWindowKeybd_3,
    PWindowKeybd_4,
    PWindowKeybd_5,
    PWindowKeybd_6,
    PWindowKeybd_7,
    PWindowKeybd_8,
    PWindowKeybd_9,
    PWindowKeybd_Space,
    PWindowKeybd_Minus,
    PWindowKeybd_Equal,
    PWindowKeybd_SquareLeft,
    PWindowKeybd_SquareRight,
    PWindowKeybd_BackSlash,
    PWindowKeybd_SemiColon,
    PWindowKeybd_Apostrophe,
    PWindowKeybd_Grave,
    PWindowKeybd_Comma,
    PWindowKeybd_Period,
    PWindowKeybd_Slash,
    PWindowKeybd_Up,
    PWindowKeybd_Down,
    PWindowKeybd_Left,
    PWindowKeybd_Right,
    PWindowKeybd_Home,
    PWindowKeybd_End,
    PWindowKeybd_PageUp,
    PWindowKeybd_PageDown,
    PWindowKeybd_Insert,
    PWindowKeybd_Delete,
    PWindowKeybd_F1,
    PWindowKeybd_F2,
    PWindowKeybd_F3,
    PWindowKeybd_F4,
    PWindowKeybd_F5,
    PWindowKeybd_F6,
    PWindowKeybd_F7,
    PWindowKeybd_F8,
    PWindowKeybd_F9,
    PWindowKeybd_F10,
    PWindowKeybd_F11,
    PWindowKeybd_F12,
    PWindowKeybd_Enter,
    PWindowKeybd_Escape,
    PWindowKeybd_BackSpace,
    PWindowKeybd_Tab,
}
PWindowKeybdKey;

typedef enum PWindowEventKind
{
    PWindowEvent_None,
    PWindowEvent_Quit,
    PWindowEvent_WindowCreate,
    PWindowEvent_WindowDestroy,
    PWindowEvent_KeybdKey,
}
PWindowEventKind;

typedef struct PWindowEventQuit
{
    void* window;
}
PWindowEventQuit;

typedef struct PWindowEventWindowCreate
{
    void* window;
}
PWindowEventWindowCreate;

typedef struct PWindowEventWindowDestroy
{
    void* window;
}
PWindowEventWindowDestroy;

typedef struct PWindowEventKeybdKey
{
    void* window;

    PWindowKeybdKey key;

    Int scan;
    B32 pressed;
}
PWindowEventKeybdKey;

typedef struct PWindowEvent
{
    PWindowEventKind kind;

    union
    {
        PWindowEventQuit          quit;
        PWindowEventWindowCreate  window_create;
        PWindowEventWindowDestroy window_destroy;
        PWindowEventKeybdKey      keybd_key;
    };
}
PWindowEvent;

PWindowEvent
pWindowEventNone();

PWindowEvent
pWindowEventQuit(void* window);

PWindowEvent
pWindowEventWindowCreate(void* window);

PWindowEvent
pWindowEventWindowDestroy(void* window);

PWindowEvent
pWindowEventKeybdKey(void* window, PWindowKeybdKey key, B32 pressed, Int scan);

#endif
