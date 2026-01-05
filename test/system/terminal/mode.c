#include "../../../src/system/memory/export.h"
#include "../../../src/system/terminal/export.h"

#include <stdio.h>

int
main(int argc, char** argv)
{
    PxMemoryArena arena = pxSystemMemoryReserve(pxMemoryMiB(2));

    PxTerminal* terminal = pxTerminalReserve(&arena);

    pxTerminalCreate(terminal);
    pxTerminalModeSet(terminal, PxTerminalMode_Raw);

    char c = 0;

    while ((c = getchar()) != 'q') {}

    pxTerminalDestroy(terminal);
}
