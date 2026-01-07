#include "../../../src/system/memory/export.h"
#include "../../../src/system/console/export.h"

#include <stdio.h>

int
main(int argc, char** argv)
{
    PxMemoryArena arena = pxSystemMemoryReserve(pxMemoryMiB(2));

    PxConsole* console = pxConsoleReserve(&arena);

    pxConsoleCreate(console);
    pxConsoleModeSet(console, PxConsoleMode_Raw);

    char c = 0;

    while ((c = getchar()) != 'q') {}

    pxConsoleDestroy(console);
}
