#include "../../../src/system/memory/export.h"
#include "../../../src/system/console/export.h"

#include <stdio.h>

int main(int argc, char** argv)
{
    PxMemoryArena arena = pxSystemMemoryReserve(pxMemoryMIB(2));

    PxConsole* console = pxConsoleReserve(&arena);

    pxConsoleCreate(console);
    pxConsoleModeSet(console, PxConsoleMode_Raw);

    PxConsoleEvent event;

    b32 active = 1;

    while (active != 0) {
        while (pxConsolePollEvent(console, &event) != 0) {
            switch (event.kind) {
                case PxConsoleEvent_KeyboardKey: {
                    PxConsoleKeyboardKey key = event.keyboard_key.key;

                    if (key == PxConsoleKeyboardKey_Escape) active = 0;
                } break;

                default: break;
            }
        }
    }

    pxConsoleDestroy(console);
}
