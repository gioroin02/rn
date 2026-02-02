#include "../../../src/rho-base/string/export.h"
#include "../../../src/rho-system/memory/export.h"
#include "../../../src/rho-system/window/export.h"
#include "../../../src/rho-system/window/opengl/export.h"
#include "../../../src/rho-system/time/export.h"

#include <stdio.h>
#include <math.h>

typedef struct Context
{
    RWindow* window;
    RClock*  clock;

    RWindowKeyboard keyboard;

    RBool32  active;
    RFloat32 time;
}
Context;

void context_update(Context* self)
{
    rho_clock_tick(self->clock);

    RFloat32 elapsed = rho_clock_seconds(self->clock);

    printf("\x1b\x63%8.3f (Hz)\n", 1.0 / elapsed);

    self->time += elapsed;
}

void context_paint(Context* self)
{
    RWindowAttribs attribs = rho_window_get_attribs(self->window);

    rho_window_swap_buffers(self->window);
}

void context_window_callback(Context* self, RWindowEvent event)
{
    switch (event.kind) {
        case RWindowEvent_Quit: self->active = 0; break;

        case RWindowEvent_KeyboardKey: {
            rho_window_keyboard_on_event(&self->keyboard, event.keyboard_key);

            if (rho_window_keyboard_is_stopping(&self->keyboard, RWindowKeyboard_Escape) != 0)
                self->active = 0;
        } break;

        case RWindowEvent_Paint: {
            context_update(self);
            context_paint(self);
        } break;

        default: break;
    }
}

int main(int argc, char** argv)
{
    RMemoryArena arena = rho_system_memory_reserve(rho_memory_kib(8));

    Context context;

    rho_memory_set(&context, sizeof context, 0xAB);

    context.clock    = rho_clock_reserve(&arena);
    context.window   = rho_window_reserve(&arena);
    context.keyboard = rho_window_keyboard_make();
    context.active   = 1;
    context.time     = 0;

    ROpenglContextAttribs opengl = {0};

    opengl.profile       = ROpenglProfile_Core;
    opengl.flag          = ROpenglContextFlag_Debug;
    opengl.version_major = 3;
    opengl.version_minor = 3;

    rho_window_create(context.window, rho_string8("Prova"), 800, 600);
    rho_window_opengl_create(context.window, opengl);

    rho_clock_create(context.clock);

    RWindowAttribs attribs = rho_window_get_attribs(context.window);

    attribs.visibility = RWindowVisibility_Show;

    rho_window_set_callback(context.window,
        &context, context_window_callback);

    rho_window_set_attribs(context.window, attribs);

    while (context.active != 0) {
        rho_window_poll_events(context.window);

        context_update(&context);
        context_paint(&context);
    }

    rho_window_destroy(context.window);
}
