#include "../../../src/string/export.h"
#include "../../../src/system/memory/export.h"
#include "../../../src/system/window/export.h"

#include <stdio.h>

typedef struct Context
{
    PxWindow*        window;
    PxWindowSurface* surface;

    ssize offset_x;
    ssize offset_y;
    ssize light;
}
Context;

void paintGradient(PxWindowSurface* surface, ssize offset_x, ssize offset_y)
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

void contextPaint(Context* self)
{
    self->offset_x += 1;
    self->offset_y += 1;

    paintGradient(self->surface, self->offset_x, self->offset_y);

    pxWindowClear(self->window, self->light, self->light, self->light);

    ssize width  = pxWindowSurfaceWidth(self->surface);
    ssize height = pxWindowSurfaceHeight(self->surface);
    ssize x      = pxWindowWidth(self->window) / 2 - width / 2;
    ssize y      = pxWindowHeight(self->window) / 2 - height / 2;

    pxWindowPaint(self->window, x, y, width, height, self->surface);

    self->light = (self->light + 1) % 256;
}

int main(int argc, char** argv)
{
    PxMemoryArena arena = pxSystemMemoryReserve(pxMemoryMIB(8));

    Context context;

    pxMemorySet(&context, sizeof context, 0xAB);

    context.window  = pxWindowReserve(&arena);
    context.surface = pxWindowSurfaceReserve(&arena);

    pxWindowCreate(context.window, pxString8("Prova"), 800, 600);

    pxWindowSurfaceCreate(context.surface, &arena, 800, 600);

    b32   active   = 1;
    ssize offset_x = 0;
    ssize offset_y = 0;
    usize light    = 0;

    pxWindowClear(context.window, 0, 0, 0);

    pxWindowProcPaintSet(context.window, &context, contextPaint);
    pxWindowVisibilitySet(context.window, PxWindowVisibility_Show);

    while (active != 0) {
        PxWindowEvent event;

        while (pxWindowPollEvent(context.window, &event) != 0) {
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

        contextPaint(&context);
    }

    pxWindowDestroy(context.window);
}
