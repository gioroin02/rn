#include "../../../src/string/export.h"
#include "../../../src/system/memory/export.h"
#include "../../../src/system/window/export.h"

#include <stdio.h>

int main(int argc, char** argv)
{
    PxMemoryArena arena = pxSystemMemoryReserve(pxMemoryMIB(2));

    PxWindow* window = pxWindowReserve(&arena);

    pxWindowCreate(window, pxString8("Prova"), 800, 600);
    pxWindowVisibilitySet(window, PxWindowVisibility_Show);

    PxWindowEvent event;

    b32   active = 1;
    ssize index  = 0;

    u32 color = 0;

    for (index = 0; active != 0; index = (index + 1) % PX_MEMORY_MIB) {
        if (index % 50000 == 0) {
            u8 red   = (color & ((u32) 0x0000FF)) >> 0;
            u8 green = (color & ((u32) 0x00FF00)) >> 8;
            u8 blue  = (color & ((u32) 0xFF0000)) >> 16;

            red   = red + 1;
            green = green + 2;
            blue  = blue + 4;

            color = ((u32) red) << 0 | ((u32) green) << 8 | ((u32) blue) << 16;

            pxWindowColorSet(window, color);
        }

        while (pxWindowPollEvent(window, &event) != 0) {
            switch (event.kind) {
                case PxWindowEvent_Quit: active = 0; break;

                case PxWindowEvent_KeyboardKey: {
                    PxWindowKeyboardKey key     = event.keyboard_key.key;
                    b32                 pressed = event.keyboard_key.pressed;

                    if (pressed != 0 && key == PxWindowKeyboardKey_Escape)
                        active = 0;
                } break;

                default: break;
            }
        }
    }

    pxWindowDestroy(window);
}
