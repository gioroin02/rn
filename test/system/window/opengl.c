#include "../../../src/string/export.h"
#include "../../../src/system/memory/export.h"
#include "../../../src/system/time/export.h"
#include "../../../src/system/window/export.h"
#include "../../../src/system/window/opengl/export.h"

#include "renderer/export.h"

#include <stdio.h>
#include <math.h>

typedef struct Vertex
{
    struct { F32 x, y; }    coord;
    struct { F32 r, g, b; } color;
}
Vertex;

#define SOURCE_VERTEX                             \
    "#version 330 core\n"                         \
    "\n"                                          \
    "layout (location = 0) in vec2 vert_coord;\n" \
    "layout (location = 1) in vec3 vert_color;\n" \
    "\n"                                          \
    "out vec3 frag_color;\n"                      \
    "\n"                                          \
    "void main() {\n"                             \
    "    frag_color  = vert_color;\n"             \
    "    gl_Position = vec4(vert_coord, 1, 1);\n" \
    "}\n"

#define SOURCE_FRAGMENT                                  \
    "#version 330 core\n"                                \
    "\n"                                                 \
    "in  vec3 frag_color;\n"                             \
    "out vec3  out_color;\n"                             \
    "\n"                                                 \
    "void main() {\n"                                    \
    "    float gamma_r = pow(frag_color.r, 0.80);\n"     \
    "    float gamma_g = pow(frag_color.g, 0.80);\n"     \
    "    float gamma_b = pow(frag_color.b, 0.80);\n"     \
    "\n"                                                 \
    "    out_color = vec3(gamma_r, gamma_g, gamma_b);\n" \
    "}\n"

typedef struct Context
{
    PWindow* window;
    PClock*  clock;

    PWindowKeybd keyboard;

    PShader       shader;
    PBufferVertex buff_vertex;
    PBufferIndex  buff_index;

    PVertexDescr descriptor;

    B32 active;
    F32 time;
}
Context;

void contextUpdate(Context* self)
{
    if (pWindowKeybdIsReleased(&self->keyboard, PWindowKeybd_Escape) != 0)
        self->active = 0;

    F32 elapsed = pClockElapsed(self->clock);

    printf("\x1b\x63%.3f Hz\n", 1.0 / elapsed);

    self->time += elapsed;

    PWindowAttribs attribs = pWindowGetAttribs(self->window);

    glViewport(0, 0, attribs.width, attribs.height);

    glClearColor(
        0.33 * (sin(self->time * 1) + 1),
        0.33 * (sin(self->time * 2) + 1),
        0.33 * (sin(self->time * 3) + 1),
        1.0);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(self->shader.handle);

    glBindVertexArray(self->descriptor.handle);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    pWindowSwapBuffers(self->window);
}

void windowTimerCallback(Context* self, PWindow* window)
{
    contextUpdate(self);
}

int main(int argc, char** argv)
{
    PMemoryArena arena = pSystemMemoryReserve(pMemoryMIB(8));

    Context context;

    pMemorySet(&context, sizeof context, 0xAB);

    context.window   = pWindowReserve(&arena);
    context.clock    = pClockReserve(&arena);
    context.keyboard = pWindowKeybdMake();
    context.active   = 1;

    pWindowCreate(context.window, pString8("Prova"), 800, 600);

    POpenglContextAttribs opengl;

    opengl.profile       = POpenglProfile_Core;
    opengl.version_major = 3;
    opengl.version_minor = 3;
    opengl.flag          = POpenglContextFlag_Debug;

    pWindowOpenglCreate(context.window, opengl);

    pClockCreate(context.clock);

    PShaderSchedule schedule;

    PString8 source_vertex = pString8(SOURCE_VERTEX);

    pShaderScheduleCreate(&schedule, PShaderStage_Vertex);

    B32 status_vertex = pShaderScheduleCompile(&schedule,
        PShaderStage_Vertex, pString8(SOURCE_VERTEX));

    pShaderScheduleCreate(&schedule, PShaderStage_Fragment);

    B32 status_fragment = pShaderScheduleCompile(&schedule,
        PShaderStage_Fragment, pString8(SOURCE_FRAGMENT));

    pShaderCreate(&context.shader);

    pShaderLink(&context.shader, &schedule);

    PVertexLayout layout;

    pVertexLayoutClear(&layout);

    pVertexLayoutPush(&layout, PVertexField_F32, 2);
    pVertexLayoutPush(&layout, PVertexField_F32, 3);

    Vertex vertex_data[] = {
        (Vertex) {.coord = {-0.75, -0.75}, .color = {1, 0, 0}},
        (Vertex) {.coord = {+0.75, -0.75}, .color = {0, 1, 0}},
        (Vertex) {.coord = {-0.75, +0.75}, .color = {0, 0, 0}},
        (Vertex) {.coord = {+0.75, +0.75}, .color = {0, 0, 1}},
    };

    U32 index_data[] = {0, 1, 2, 1, 2, 3};

    pBufferVertexCreateOf(&context.buff_vertex, Vertex, 32);
    pBufferIndexCreateOf(&context.buff_index, U32, 256);

    pBufferVertexWrite(&context.buff_vertex, (U8*) vertex_data, 0, sizeof vertex_data);
    pBufferIndexWrite(&context.buff_index,   (U8*)  index_data, 0,  sizeof index_data);

    pVertexDescrCreate(&context.descriptor);

    pVertexDescrApplyLayout(&context.descriptor, &layout,
        &context.buff_vertex, &context.buff_index);

    PWindowAttribs attribs = pWindowGetAttribs(context.window);

    attribs.visibility = PWindowVisibility_Show;

    pWindowSetTimerCallback(context.window,
        &context, windowTimerCallback);

    pWindowSetAttribs(context.window, attribs);

    while (context.active != 0) {
        PWindowEvent event;

        pMemorySet(&event, sizeof event, 0xAB);

        while (pWindowPollEvent(context.window, &event) != 0) {
            switch (event.kind) {
                case PWindowEvent_Quit: context.active = 0; break;

                case PWindowEvent_KeybdKey:
                    pWindowKeybdUpdate(&context.keyboard, event.keybd_key);
                break;

                default: break;
            }

            pMemorySet(&event, sizeof event, 0xAB);
        }

        contextUpdate(&context);
    }

    pWindowDestroy(context.window);
}
