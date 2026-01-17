#include "../../../src/system/memory/export.h"
#include "../../../src/system/console/export.h"

#include <stdio.h>

int main(int argc, char** argv)
{
    PMemoryArena arena = pSystemMemoryReserve(pMemoryMIB(2));

    PConsole* console = pConsoleReserve(&arena);

    pConsoleCreate(console);
    pConsoleModeSet(console, PConsoleMode_Raw);

    PConsoleEvent event;

    Bool active = 1;

    while (active != 0) {
        while (pConsolePollEvent(console, &event) != 0) {
            switch (event.kind) {
                case PConsoleEvent_KeyboardKey: {
                    if (event.keyboard_key.key == PConsoleKeyboard_Escape)
                        active = 0;
                } break;

                default: break;
            }
        }
    }

    pConsoleDestroy(console);
}
