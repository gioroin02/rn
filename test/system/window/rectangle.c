#include "rasterize.h"

#include <stdio.h>
#include <math.h>

typedef struct Context
{
    PxWindow* window;
    PxBitmap* bitmap;
    PxClock*  clock;

    f32 ticks;
    f32 time;
    b32 active;
}
Context;

void contextUpdate(Context* self)
{
    f32 elapsed = pxClockElapsed(self->clock);

    ssize width  = pxBitmapWidth(self->bitmap);
    ssize height = pxBitmapHeight(self->bitmap);
    ssize x      = pxWindowWidthGet(self->window) / 2 - width / 2;
    ssize y      = pxWindowHeightGet(self->window) / 2 - height / 2;

    self->ticks += elapsed;
    self->time  += elapsed;

    pxWindowClear(self->window, 0x0F, 0x0F, 0x0F);

    f32 delta_sin = sin(self->ticks * 5);
    f32 delta_cos = cos(self->ticks * 5);

    pxBitmapFill(self->bitmap, 0x08, 0x08, 0x08, 0xFF);

    paintTriangle(self->bitmap,
        s64Vec2(100 + delta_sin * 5, 50 + delta_cos * 5),
        s64Vec2(50 + delta_cos * 5, 100 + delta_sin * 5),
        s64Vec2(50 + delta_cos * 5, 50 + delta_sin * 5),
        u8Vec4(0xFF, 0, 0, 0xFF),
        u8Vec4(0, 0xFF, 0, 0xFF),
        u8Vec4(0, 0, 0xFF, 0xFF));

    paintRectangleFrame(self->bitmap,
        s64Vec2(250 + delta_sin * 5, 250 + delta_sin * 5),
        s64Vec2(100 + delta_cos * 5, 75 + delta_cos * 5),
        u8Vec4(0xBE, 0x0A, 0xFF, 0xFF),
        u8Vec4(0xFF, 0xFF, 0x0A, 0xFF),
        u8Vec4(0x0A, 0xBE, 0xFF, 0xFF),
        u8Vec4(0xFF, 0x0A, 0xBE, 0xFF));

    paintSegment(self->bitmap,
        s64Vec2(250 + delta_cos * 5, 0),
        s64Vec2(0, 300 + delta_sin * 5),
        u8Vec4(0x14, 0x7D, 0xF5, 0xFF),
        u8Vec4(0xF5, 0x7D, 0x14, 0xFF));

    pxWindowPaint(self->window, 0, 0, width, height, self->bitmap);

    pxWindowFlush(self->window);
}

int main(int argc, char** argv)
{
    PxMemoryArena arena = pxSystemMemoryReserve(pxMemoryMIB(8));

    Context context;

    pxMemorySet(&context, sizeof context, 0xAB);

    context.window = pxWindowReserve(&arena);
    context.bitmap = pxBitmapReserve(&arena);
    context.clock  = pxClockReserve(&arena);
    context.ticks  = 0;
    context.active = 1;

    pxWindowCreate(context.window, pxString8("Prova"), 1600, 900);
    pxBitmapCreate(context.bitmap, &arena, 400, 400);
    pxClockCreate(context.clock);

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
