#include "../../../src/string/export.h"
#include "../../../src/system/memory/export.h"
#include "../../../src/system/window/export.h"

#include <stdio.h>

void gradient(PxWindowSurface* surface, ssize offset_x, ssize offset_y)
{
    ssize col = 0;
    ssize row = 0;

    for (col = 0; col < pxWindowSurfaceWidth(surface); col += 1) {
        for (row = 0; row < pxWindowSurfaceHeight(surface); row += 1) {
            u32 red   = col + offset_x;
            u32 blue  = row + offset_y;
            u32 green = 256 - red / 2 - blue / 2;

            pxWindowSurfacePixelSet(surface, col, row, red, green, blue, 0);
        }
    }
}

int main(int argc, char** argv)
{
    PxMemoryArena arena = pxSystemMemoryReserve(pxMemoryMIB(8));

    PxWindow*        window  = pxWindowReserve(&arena);
    PxWindowSurface* surface = pxWindowSurfaceReserve(&arena);

    pxWindowCreate(window, pxString8("Prova"), 800, 600);

    pxWindowSurfaceCreate(surface, &arena, 800, 600);

    b32   active   = 1;
    ssize offset_x = 0;
    ssize offset_y = 0;

    pxWindowClear(window);

    pxWindowClearColorSet(window, 255, 0, 255, 0);
    pxWindowVisibilitySet(window, PxWindowVisibility_Show);

    while (active != 0) {
        PxWindowEvent event;

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

        gradient(surface, offset_x, offset_y);

        offset_x += 1;
        offset_y += 1;

        pxWindowFlush(window, surface);
    }

    pxWindowDestroy(window);
}
