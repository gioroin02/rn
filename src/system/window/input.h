#ifndef P_SYSTEM_WINDOW_INPUT_H
#define P_SYSTEM_WINDOW_INPUT_H

#include "event.h"

#define pWindowKeybdIsActive(self, key) \
    (pWindowKeybdGet(self, key) == PWindowKeybdKeyState_Active ? 1 : 0)

#define pWindowKeybdIsPressed(self, key) \
    (pWindowKeybdGet(self, key) == PWindowKeybdKeyState_Pressed ? 1 : 0)

#define pWindowKeybdIsReleased(self, key) \
   (pWindowKeybdGet(self, key) == PWindowKeybdKeyState_Released ? 1 : 0)

typedef struct PWindowKeybd
{
    U8 state_prev[16];
    U8 state_curr[16];
}
PWindowKeybd;

typedef enum PWindowKeybdKeyState
{
    PWindowKeybdKeyState_None,
    PWindowKeybdKeyState_Active,
    PWindowKeybdKeyState_Pressed,
    PWindowKeybdKeyState_Released,
}
PWindowKeybdKeyState;

PWindowKeybd pWindowKeybdMake();

void pWindowKeybdUpdate(PWindowKeybd* self, PWindowEventKeybdKey event);

void pWindowKeybdSet(PWindowKeybd* self, PWindowKeybdKey key, B32 state);

PWindowKeybdKeyState pWindowKeybdGet(PWindowKeybd* self, PWindowKeybdKey key);

#endif
