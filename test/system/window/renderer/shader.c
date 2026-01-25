#ifndef P_GRAPHICS_SHADER_C
#define P_GRAPHICS_SHADER_C

#include "shader.h"

#include "gl.h"

Int pShaderStageKindCode(PShaderStageKind kind)
{
    switch (kind) {
        case PShaderStage_Vertex:   return GL_VERTEX_SHADER;
        case PShaderStage_Geometry: return GL_GEOMETRY_SHADER;
        case PShaderStage_Fragment: return GL_FRAGMENT_SHADER;

        default: break;
    }

    return 0;
}

B32 pShaderStageCreate(PShaderStage* self, PShaderStageKind kind)
{
    pMemorySet(self, sizeof *self, 0xAB);

    Int code   = pShaderStageKindCode(kind);
    Int handle = glCreateShader(code);

    if (handle == 0) return 0;

    self->handle = handle;

    return 1;
}

void pShaderStageDestroy(PShaderStage* self)
{
    if (self->handle != 0)
        glDeleteShader(self->handle);

    pMemorySet(self, sizeof *self, 0xAB);
}

B32 pShaderStageCompile(PShaderStage* self, PString8 source)
{
    if (source.size < 0) return 0;

    glShaderSource(self->handle, 1,
        (const GLchar* const*) &source.values, (GLint*) &source.size);

    glCompileShader(self->handle);

    Int status = 0;

    glGetShaderiv(self->handle,
        GL_COMPILE_STATUS, (GLint*) &status);

    if (status == GL_TRUE) return 1;

    return 0;
}

void pShaderScheduleClear(PShaderSchedule* self)
{
    for (Int i = 0; i < P_SHADER_SCHEDULE_STAGES; i += 1) {
        if (glIsShader(self->stages[i].handle) != 0)
            pShaderStageDestroy(&self->stages[i]);
    }
}

B32 pShaderScheduleCreate(PShaderSchedule* self, PShaderStageKind kind)
{
    if (kind != PShaderStage_None)
        return pShaderStageCreate(&self->stages[kind - 1], kind);

    return 0;
}

void pShaderScheduleDestroy(PShaderSchedule* self, PShaderStageKind kind)
{
    if (kind != PShaderStage_None)
        pShaderStageDestroy(&self->stages[kind - 1]);
}

B32 pShaderScheduleCompile(PShaderSchedule* self, PShaderStageKind kind, PString8 source)
{
    if (kind != PShaderStage_None)
        return pShaderStageCompile(&self->stages[kind - 1], source);

    return 0;
}

B32 pShaderCreate(PShader* self)
{
    pMemorySet(self, sizeof *self, 0xAB);

    Int handle = glCreateProgram();

    if (handle == 0) return 0;

    self->handle = handle;

    return 1;
}

void pShaderDestroy(PShader* self)
{
    if (self->handle != 0)
        glDeleteProgram(self->handle);

    pMemorySet(self, sizeof *self, 0xAB);
}

B32 pShaderLink(PShader* self, PShaderSchedule* schedule)
{
    for (Int i = 0; i < P_SHADER_SCHEDULE_STAGES; i += 1) {
        PShaderStage* stage = &schedule->stages[i];

        if (glIsShader(stage->handle) != 0)
            glAttachShader(self->handle, stage->handle);
    }

    glLinkProgram(self->handle);

    Int status = 0;

    glGetProgramiv(self->handle, GL_LINK_STATUS, (GLint*) &status);

    for (Int i = P_SHADER_SCHEDULE_STAGES; i > 0; i -= 1) {
        PShaderStage* stage = &schedule->stages[i - 1];

        if (glIsShader(stage->handle) != 0)
            glDetachShader(self->handle, stage->handle);
    }

    if (status == GL_TRUE) return 1;

    return 0;
}

#endif
