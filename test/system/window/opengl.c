#include "../../../src/string/export.h"
#include "../../../src/system/memory/export.h"
#include "../../../src/system/time/export.h"
#include "../../../src/system/window/export.h"
#include "../../../src/graphics/opengl/export.h"

#include "../../../src/graphics/opengl/glad.h"

#include <stdio.h>
#include <math.h>

typedef struct Vertex
{
    struct { F32 x, y; }    coord;
    struct { F32 r, g, b; } color;
}
Vertex;

#define SOURCE_VERTEX                                    \
    "#version 330 core\n"                                \
    "\n"                                                 \
    "layout (location = 0) in vec2 layout_vert_coord;\n" \
    "layout (location = 1) in vec3 layout_vert_color;\n" \
    "\n"                                                 \
    "out vec3 vert_color;\n"                             \
    "\n"                                                 \
    "void main() {\n"                                    \
    "    vert_color  = layout_vert_color;\n"             \
    "    gl_Position = vec4(layout_vert_coord, 1, 1);\n" \
    "}\n"

#define SOURCE_FRAGMENT                       \
    "#version 330 core\n"                     \
    "\n"                                      \
    "in  vec3 vert_color;\n"                  \
    "out vec4 frag_color;\n"                  \
    "\n"                                      \
    "void main() {\n"                         \
    "    frag_color = vec4(vert_color, 1);\n" \
    "}\n"

typedef struct Context
{
    PWindow* window;
    PClock*  clock;

    POglShader       shader;
    POglBufferVertex buff_vertex;

    Int layout;

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

    glBindVertexArray(self->layout);
    glUseProgram(self->shader.handle);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    glBindVertexArray(0);

    pWindowSwapBuffers(self->window);
}

void layoutApplyVertex(Int layout, POglBufferVertex* buffer, Vertex* item)
{
    glBindVertexArray(layout);

    glBindBuffer(GL_ARRAY_BUFFER, buffer->handle);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE,
        sizeof *item, (void*) pOffsetOf(item, coord));

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,
        sizeof *item, (void*) pOffsetOf(item, color));

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

int main(int argc, char** argv)
{
    PMemoryArena arena = pSystemMemoryReserve(pMemoryMIB(8));

    Context context;

    pMemorySet(&context, sizeof context, 0xAB);

    context.window = pWindowReserve(&arena);

    pWindowCreate(context.window, pString8("Prova"), 800, 600);

    gladLoadGLLoader(pOpenglProcAddress);

    POglShaderSchedule schedule;

    PString8 source_vertex = pString8(SOURCE_VERTEX);

    pOglShaderScheduleCreate(&schedule, POglShaderStage_Vertex);

    Bool status_vertex = pOglShaderScheduleCompile(&schedule,
        POglShaderStage_Vertex, pString8(SOURCE_VERTEX));

    pOglShaderScheduleCreate(&schedule, POglShaderStage_Fragment);

    Bool status_fragment = pOglShaderScheduleCompile(&schedule,
        POglShaderStage_Fragment, pString8(SOURCE_FRAGMENT));

    pOglShaderCreate(&context.shader);

    pOglShaderLink(&context.shader, &schedule);

    pOglBufferVertexCreateOf(&context.buff_vertex, Vertex, 32);

    Vertex vert_data[3] = {
        (Vertex) {.coord = {-0.50, -0.33}, .color = {1, 0, 0}},
        (Vertex) {.coord = {    0,  0.50}, .color = {0, 1, 0}},
        (Vertex) {.coord = {+0.50, -0.33}, .color = {0, 0, 1}},
    };

    pOglBufferVertexWrite(&context.buff_vertex,
        (U8*) vert_data, 0, sizeof vert_data);

    context.layout = 0;

    glGenVertexArrays(1, (GLuint*) &context.layout);

    layoutApplyVertex(context.layout, &context.buff_vertex, vert_data);

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
