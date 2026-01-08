#include "../../../src/system/memory/export.h"
#include "../../../src/system/console/export.h"

#include <stdio.h>

int main(int argc, char** argv)
{
    PxMemoryArena arena = pxSystemMemoryReserve(pxMebi(2));

    PxConsole* console = pxConsoleReserve(&arena);

    pxConsoleCreate(console);
    pxConsoleModeSet(console, PxConsoleMode_Raw);

    PxConsoleEvent event;

    b32 active = 1;

    while (active != 0) {
        while (pxConsolePollEvent(console, &event) != 0) {
            switch (event.kind) {
                case PxConsoleEvent_Keyboard:
                    if (event.keyboard.key == PxConsoleKey_Escape)
                        active = 0;
                break;

                default: break;
            }
        }
    }

    pxConsoleDestroy(console);
}
