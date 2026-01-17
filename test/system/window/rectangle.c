#include "rasterize.h"

#include <stdio.h>
#include <math.h>

typedef struct Context
{
    PWindow* window;
    PBitmap* bitmap;
    PClock*  clock;

    f32 ticks;
    f32 time;
    b32 active;
}
Context;

void contextUpdate(Context* self)
{
    f32 elapsed = pClockElapsed(self->clock);

    ssize width  = pBitmapWidth(self->bitmap);
    ssize height = pBitmapHeight(self->bitmap);
    ssize x      = pWindowWidthGet(self->window) / 2 - width / 2;
    ssize y      = pWindowHeightGet(self->window) / 2 - height / 2;

    self->ticks += elapsed;
    self->time  += elapsed;

    pWindowClear(self->window, 0x0F, 0x0F, 0x0F);

    f32 delta_sin = sin(self->ticks * 5);
    f32 delta_cos = cos(self->ticks * 5);

    pBitmapFill(self->bitmap, 0x08, 0x08, 0x08, 0xFF);

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

    pWindowPaint(self->window, 0, 0, width, height, self->bitmap);

    pWindowFlush(self->window);
}

int main(int argc, char** argv)
{
    PMemoryArena arena = pSystemMemoryReserve(pMemoryMIB(8));

    Context context;

    pMemorySet(&context, sizeof context, 0xAB);

    context.window = pWindowReserve(&arena);
    context.bitmap = pBitmapReserve(&arena);
    context.clock  = pClockReserve(&arena);
    context.ticks  = 0;
    context.active = 1;

    pWindowCreate(context.window, pString8("Prova"), 1600, 900);
    pBitmapCreate(context.bitmap, &arena, 400, 400);
    pClockCreate(context.clock);

    pWindowPntrContextSet(context.window, &context);
    pWindowProcUpdateSet(context.window, contextUpdate);
    pWindowVisibilitySet(context.window, PWindowVisibility_Show);

    while (context.active != 0) {
        PWindowEvent event;

        pMemorySet(&event, sizeof event, 0xAB);

        while (pWindowPollEvent(context.window, &event) != 0) {
            switch (event.kind) {
                case PWindowEvent_Quit: context.active = 0; break;

                case PWindowEvent_KeyboardKey: {
                    PWindowKeyboardKey key     = event.keyboard_key.key;
                    b32                 pressed = event.keyboard_key.pressed;

                    if (pressed != 0 && key == PWindowKeyboardKey_Escape)
                        context.active = 0;
                } break;

                default: break;
            }

            pMemorySet(&event, sizeof event, 0xAB);
        }

        contextUpdate(&context);
    }

    pWindowDestroy(context.window);
}
