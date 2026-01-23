#ifndef P_SYSTEM_WINDOW_INPUT_C
#define P_SYSTEM_WINDOW_INPUT_C

#include "input.h"

PWindowKeybd pWindowKeybdMake()
{
    PWindowKeybd result;

    pMemorySet(&result, sizeof result, 0x00);

    return result;
}

void pWindowKeybdUpdate(PWindowKeybd* self, PWindowEventKeybdKey event)
{
    if (event.key != PWindowKeybd_None)
        pWindowKeybdSet(self, event.key, event.pressed);
}

void pWindowKeybdSet(PWindowKeybd* self, PWindowKeybdKey key, Bool state)
{
    if (key < 0 ||key >= (sizeof self->state_curr * 8))
        return;

    Int index = key >> 3;
    Int mask  = 1 << (key & 0x7);

    U8 prev = self->state_prev[index];
    U8 curr = self->state_curr[index];

    prev = (curr & mask) != 0 ?
        prev | mask : prev & ~mask;

    curr = state != 0 ?
        curr | mask : curr & ~mask;

    self->state_prev[index] = prev;
    self->state_curr[index] = curr;
}

PWindowKeybdKeyState pWindowKeybdGet(PWindowKeybd* self, PWindowKeybdKey key)
{
    if (key < 0 ||key >= (sizeof self->state_curr * 8))
        return PWindowKeybdKeyState_None;

    Int index = key >> 3;
    Int mask  = 1 << (key & 0x7);

    U8 prev = self->state_prev[index];
    U8 curr = self->state_curr[index];

    if ((curr & mask) != 0) {
        if ((prev & mask) != 0)
            return PWindowKeybdKeyState_Active;

        return PWindowKeybdKeyState_Pressed;
    }

    if ((prev & mask) != 0)
        return PWindowKeybdKeyState_Released;

    return PWindowKeybdKeyState_None;
}

#endif // P_SYSTEM_WINDOW_INPUT_C
