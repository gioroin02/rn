#ifndef PX_SYSTEM_TERMINAL_COMMON_H
#define PX_SYSTEM_TERMINAL_COMMON_H

#include "import.h"

typedef enum PxTerminalMode
{
    PxTerminalMode_None,
    PxTerminalMode_Cooked,
    PxTerminalMode_Raw,
}
PxTerminalMode;

typedef void PxTerminal;

PxTerminal*
pxTerminalReserve(PxMemoryArena* arena);

b32
pxTerminalCreate(PxTerminal* self);

void
pxTerminalDestroy(PxTerminal* self);

b32
pxTerminalModeSet(PxTerminal* self, PxTerminalMode mode);

PxTerminalMode
pxTerminalModeGet(PxTerminal* self);

#endif // PX_SYSTEM_TERMINAL_COMMON_H
