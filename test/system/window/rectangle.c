#include "../../../src/string/export.h"
#include "../../../src/system/memory/export.h"
#include "../../../src/system/time/export.h"
#include "../../../src/system/window/export.h"

#include "rasterize.h"

#include <stdio.h>
#include <math.h>

typedef struct Context
{
    PWindow* window;
    PClock*  clock;

    F32 time;
}
Context;

void windowPaintCallback(Context* self, PWindow* window, PFrameBuffer* buffer)
{
    F32 elapsed = pClockElapsed(self->clock);

    printf("\x1b\x63%.3f Hz\n", 1.0 / elapsed);

    self->time += elapsed;

    F32 speed = 2.5;

    F32 delta_sin = (sin(self->time * speed) + 1) / 2;
    F32 delta_cos = (cos(self->time * speed) + 1) / 2;

    pFrameBufferFill(buffer,
        63 * delta_sin,
        63 * delta_cos,
        63 * (delta_sin + delta_cos) / 2,
        0xFF);

    paintRectangleFrame(buffer,
        i64v2(800, 450),
        i64v2(1400, 700),
        u8v4(0xBE, 0x0A, 0xFF, 0xFF),
        u8v4(0xFF, 0xFF, 0x0A, 0xFF),
        u8v4(0x0A, 0xBE, 0xFF, 0xFF),
        u8v4(0xFF, 0x0A, 0xBE, 0xFF));

    paintTriangle(buffer,
        i64v2(400 + delta_sin * 50,  50 + delta_cos * 50),
        i64v2(500 + delta_cos * 50,  50 + delta_sin * 50),
        i64v2(400 + delta_sin * 50, 200 + delta_cos * 50),
        u8v4(0xFF, 0, 0, 0xFF),
        u8v4(0, 0xFF, 0, 0xFF),
        u8v4(0, 0, 0xFF, 0xFF));

    paintSegment(buffer,
        i64v2(250 + delta_cos * 50, 0),
        i64v2(0, 300 + delta_sin * 50),
        u8v4(0x14, 0x7D, 0xF5, 0xFF),
        u8v4(0xF5, 0x7D, 0x14, 0xFF));

    paintSegment(buffer,
        i64v2(300 + delta_cos * 50, 0),
        i64v2(0, 350 + delta_sin * 50),
        u8v4(0x14, 0x7D, 0xF5, 0xFF),
        u8v4(0xF5, 0x7D, 0x14, 0xFF));

    paintSegment(buffer,
        i64v2(350 + delta_cos * 50, 0),
        i64v2(0, 400 + delta_sin * 50),
        u8v4(0x14, 0x7D, 0xF5, 0xFF),
        u8v4(0xF5, 0x7D, 0x14, 0xFF));
}

int main(int argc, char** argv)
{
    PMemoryArena arena = pSystemMemoryReserve(pMemoryMIB(8));

    Context context;

    pMemorySet(&context, sizeof context, 0xAB);

    context.window = pWindowReserve(&arena);
    context.clock  = pClockReserve(&arena);

    pWindowCreate(context.window, pString8("Prova"), 800, 450);
    pClockCreate(context.clock);

    Bool active = 1;

    pWindowSetCallback(context.window, &context, windowPaintCallback);
    pWindowSetVisibility(context.window, PWindowVisibility_Show);

    while (active != 0) {
        PWindowEvent event;

        pMemorySet(&event, sizeof event, 0xAB);

        while (pWindowPollEvent(context.window, &event) != 0) {
            switch (event.kind) {
                case PWindowEvent_Quit: active = 0; break;

                case PWindowEvent_KeyboardKey: {
                    PWindowKeyboardKey key     = event.keyboard_key.key;
                    Bool               pressed = event.keyboard_key.pressed;

                    if (pressed != 0 && key == PWindowKeyboardKey_Escape)
                        active = 0;
                } break;

                default: break;
            }

            pMemorySet(&event, sizeof event, 0xAB);
        }

        PFrameBuffer* buffer = pWindowGetBuffer(context.window);

        windowPaintCallback(&context, context.window, buffer);

        pWindowFlushBuffer(context.window);
    }

    pWindowDestroy(context.window);
}
