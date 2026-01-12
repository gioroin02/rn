#include "../../../src/string/export.h"
#include "../../../src/system/memory/export.h"
#include "../../../src/system/time/export.h"
#include "../../../src/system/window/export.h"

#include <stdio.h>
#include <math.h>

typedef struct Context
{
    PxWindow*        window;
    PxWindowSurface* surface;
    PxClock*         clock;

    f32 ticks;
    f32 time;
    b32 active;
}
Context;

void paintLine(PxWindowSurface* surface, ssize x0, ssize y0, ssize x1, ssize y1, u8 red, u8 green, u8 blue, u8 alpha)
{
    ssize start_x = pxMin(x0, x1);
    ssize stop_x  = pxMax(x0, x1);
    ssize start_y = pxMin(y0, y1);
    ssize stop_y  = pxMax(y0, y1);

    f32 delta_x = stop_x - start_x;
    f32 delta_y = stop_y - start_y;

    if (delta_x > delta_y) {
        if (x0 > x1) { ssize a = x0, b = y0; x0 = x1, y0 = y1; x1 = a, y1 = b; }

        f32 slope = x0 != x1 ? (f32) (y1 - y0) / (f32) (x1 - x0) : 0;

        f32 x = 0;
        f32 y = y0;

        for (x = start_x; x <= stop_x; x += 1, y += slope)
            pxWindowSurfacePixelSet(surface, x, y, red, green, blue, alpha);
    }
    else {
        if (y0 > y1) { ssize a = x0, b = y0; x0 = x1, y0 = y1; x1 = a, y1 = b; }

        f32 slope = y0 != y1 ? (f32) (x1 - x0) / (f32) (y1 - y0) : 0;

        f32 x = x0;
        f32 y = 0;

        for (y = start_y; y <= stop_y; y += 1, x += slope)
            pxWindowSurfacePixelSet(surface, x, y, red, green, blue, alpha);
    }
}

void paintTriangleFrame(PxWindowSurface* surface, ssize x0, ssize y0, ssize x1, ssize y1, ssize x2, ssize y2,
    u8 red, u8 green, u8 blue, u8 alpha)
{
    paintLine(surface, x0, y0, x1, y1, red, green, blue, alpha);
    paintLine(surface, x0, y0, x2, y2, red, green, blue, alpha);
    paintLine(surface, x1, y1, x2, y2, red, green, blue, alpha);
}

void paintGradient(PxWindowSurface* surface, ssize offset_x, ssize offset_y)
{
    ssize col = 0;
    ssize row = 0;

    for (col = 0; col < pxWindowSurfaceWidth(surface); col += 1) {
        for (row = 0; row < pxWindowSurfaceHeight(surface); row += 1) {
            u32 red   = col + offset_x;
            u32 blue  = row + offset_y;
            u32 green = (red + blue) / 4;

            pxWindowSurfacePixelSet(surface, col, row, red, green, blue, 0);
        }
    }
}

void contextUpdate(Context* self)
{
    f32 elapsed = pxClockElapsed(self->clock);

    self->ticks += elapsed;
    self->time  += elapsed;

    if (self->time >= 0.0166f) {
        self->time -= 0.0166f;

        pxWindowClear(self->window, 0, 32, 0);

        f32 delta_sin = sin(self->ticks * 10) * 10;
        f32 delta_cos = cos(self->ticks * 10) * 10;

        pxWindowSurfaceFill(self->surface, 0, 0, 0, 0);

        paintTriangleFrame(self->surface,
            300 + delta_sin, 100 + delta_cos,
            300 + delta_cos, 300 + delta_sin,
            400 + delta_sin, 100 + delta_cos,
            0, 255, 0, 0);

        paintTriangleFrame(self->surface,
            300 + delta_cos, 300 + delta_sin,
            400 + delta_sin, 100 + delta_cos,
            400 + delta_cos, 300 + delta_sin,
            0, 255, 0, 0);

        ssize width  = pxWindowSurfaceWidth(self->surface);
        ssize height = pxWindowSurfaceHeight(self->surface);
        ssize x      = pxWindowWidthGet(self->window) / 2 - width / 2;
        ssize y      = pxWindowHeightGet(self->window) / 2 - height / 2;

        pxWindowPaint(self->window, x, y, width, height, self->surface);

        pxWindowFlush(self->window);
    }
}

int main(int argc, char** argv)
{
    PxMemoryArena arena = pxSystemMemoryReserve(pxMemoryMIB(8));

    Context context;

    pxMemorySet(&context, sizeof context, 0xAB);

    context.window  = pxWindowReserve(&arena);
    context.surface = pxWindowSurfaceReserve(&arena);
    context.clock   = pxClockReserve(&arena);
    context.ticks   = 0;
    context.active  = 1;

    pxWindowCreate(context.window, pxString8("Prova"), 1600, 900);

    pxWindowSurfaceCreate(context.surface, &arena, 800, 800);

    pxClockCreate(context.clock);

    pxWindowClear(context.window, 0, 0, 0);

    pxWindowPntrContextSet(context.window, &context);
    pxWindowProcUpdateSet(context.window, contextUpdate);
    pxWindowVisibilitySet(context.window, PxWindowVisibility_Show);

    while (context.active != 0) {
        PxWindowEvent event;

        pxMemorySet(&event, sizeof event, 0xAB);

        while (pxWindowPollEvent(context.window, &event) != 0) {
            switch (event.kind) {
                case PxWindowEvent_Quit: context.active = 0; break;

                case PxWindowEvent_KeyboardKey: {
                    PxWindowKeyboardKey key     = event.keyboard_key.key;
                    b32                 pressed = event.keyboard_key.pressed;

                    if (pressed != 0 && key == PxWindowKeyboardKey_Escape)
                        context.active = 0;
                } break;

                default: break;
            }

            pxMemorySet(&event, sizeof event, 0xAB);
        }

        contextUpdate(&context);
    }

    pxWindowDestroy(context.window);
}
