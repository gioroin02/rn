#include "../../../src/string/export.h"
#include "../../../src/system/memory/export.h"
#include "../../../src/system/time/export.h"
#include "../../../src/system/window/export.h"

#include <stdio.h>
#include <math.h>

#include "glad.h"

char* vertex =
"#version 330 core\n"
"\n"
"void main() {}\n";

char* fragment =
"#version 330 core\n"
"\n"
"void main() {\n"
"gl_FragColor = glFragCoord;\n"
"}\n";

typedef struct Context
{
    PWindow* window;
    PClock*  clock;

    F32 time;
}
Context;

void windowPaintCallback(Context* self, PWindow* window)
{
    F32 elapsed = pClockElapsed(self->clock);

    printf("\x1b\x63%.3f Hz\n", 1.0 / elapsed);

    self->time += elapsed;

    PWindowAttribs attribs = pWindowGetAttribs(window);

    glViewport(0, 0, attribs.width, attribs.height);

    glClearColor(
        0.33 * (sin(self->time * 1) + 1),
        0.33 * (sin(self->time * 2) + 1),
        0.33 * (sin(self->time * 3) + 1),
        1.0);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    pWindowSwapBuffers(window);
}

int main(int argc, char** argv)
{
    PMemoryArena arena = pSystemMemoryReserve(pMemoryMIB(8));

    Context context;

    pMemorySet(&context, sizeof context, 0xAB);

    context.window = pWindowReserve(&arena);

    pWindowCreate(context.window, pString8("Prova"), 800, 600);

    gladLoadGLLoader(pOpenglProcAddress);

    Bool active = 1;

    PWindowAttribs attribs = pWindowGetAttribs(context.window);

    attribs.visibility = PWindowVisibility_Show;

    pWindowSetCallback(context.window, &context, windowPaintCallback);
    pWindowSetAttribs(context.window, attribs);

    context.clock = pClockReserve(&arena);

    pClockCreate(context.clock);

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

        windowPaintCallback(&context, context.window);
    }

    pWindowDestroy(context.window);
}
