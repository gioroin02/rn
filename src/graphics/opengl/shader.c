#ifndef P_GRAPHICS_OPENGL_SHADER_C
#define P_GRAPHICS_OPENGL_SHADER_C

#include "shader.h"

#include "glad.h"

Int pOglShaderStageKindCode(POglShaderStageKind kind)
{
    switch (kind) {
        case POglShaderStage_Vertex:   return GL_VERTEX_SHADER;
        case POglShaderStage_Geometry: return GL_GEOMETRY_SHADER;
        case POglShaderStage_Fragment: return GL_FRAGMENT_SHADER;

        default: break;
    }

    return 0;
}

Bool pOglShaderStageCreate(POglShaderStage* self, POglShaderStageKind kind)
{
    pMemorySet(self, sizeof *self, 0xAB);

    Int code   = pOglShaderStageKindCode(kind);
    Int handle = glCreateShader(code);

    if (handle == 0) return 0;

    self->handle = handle;

    return 1;
}

void pOglShaderStageDestroy(POglShaderStage* self)
{
    if (glIsShader(self->handle) != 0)
        glDeleteShader(self->handle);

    pMemorySet(self, sizeof *self, 0xAB);
}

Bool pOglShaderStageCompile(POglShaderStage* self, PString8 source)
{
    if (source.size < 0) return 0;

    glShaderSource(self->handle, 1, (const GLchar**) &source.values,
        (const GLint*) &source.size);

    glCompileShader(self->handle);

    Int status = 0;

    glGetShaderiv(self->handle, GL_COMPILE_STATUS, (GLint*) &status);

    if (status == GL_TRUE) return 1;

    return 0;
}

void pOglShaderScheduleClear(POglShaderSchedule* self)
{
    Int index = 0;

    for (index = 0; index < POGL_SHADER_SCHEDULE_STAGES; index += 1) {
        if (glIsShader(self->stages[index].handle) != 0)
            pOglShaderStageDestroy(&self->stages[index]);
    }
}

Bool pOglShaderScheduleCreate(POglShaderSchedule* self, POglShaderStageKind kind)
{
    int error = glGetError();

    switch (kind) {
        case POglShaderStage_Vertex:   return pOglShaderStageCreate(&self->stages[0], kind);
        case POglShaderStage_Geometry: return pOglShaderStageCreate(&self->stages[1], kind);
        case POglShaderStage_Fragment: return pOglShaderStageCreate(&self->stages[2], kind);

        default: break;
    }

    return 0;
}

void pOglShaderScheduleDestroy(POglShaderSchedule* self, POglShaderStageKind kind)
{
    int error = glGetError();

    switch (kind) {
        case POglShaderStage_Vertex:   pOglShaderStageDestroy(&self->stages[0]); break;
        case POglShaderStage_Geometry: pOglShaderStageDestroy(&self->stages[1]); break;
        case POglShaderStage_Fragment: pOglShaderStageDestroy(&self->stages[2]); break;

        default: break;
    }
}

Bool pOglShaderScheduleCompile(POglShaderSchedule* self, POglShaderStageKind kind, PString8 source)
{
    int error = glGetError();

    switch (kind) {
        case POglShaderStage_Vertex:   return pOglShaderStageCompile(&self->stages[0], source);
        case POglShaderStage_Geometry: return pOglShaderStageCompile(&self->stages[1], source);
        case POglShaderStage_Fragment: return pOglShaderStageCompile(&self->stages[2], source);

        default: break;
    }

    return 0;
}

Bool pOglShaderCreate(POglShader* self)
{
    pMemorySet(self, sizeof *self, 0xAB);

    Int handle = glCreateProgram();

    if (handle == 0) return 0;

    self->handle = handle;

    return 1;
}

void pOglShaderDestroy(POglShader* self)
{
    if (glIsProgram(self->handle) != 0)
        glDeleteProgram(self->handle);

    pMemorySet(self, sizeof *self, 0xAB);
}

Bool pOglShaderLink(POglShader* self, POglShaderSchedule* schedule)
{
    Int index = 0;
    int error = glGetError();

    for (index = 0; index < POGL_SHADER_SCHEDULE_STAGES; index += 1) {
        POglShaderStage* stage = &schedule->stages[index];

        error = glGetError();

        if (glIsShader(stage->handle) != 0)
            glAttachShader(self->handle, stage->handle);
    }

    error = glGetError();

    glLinkProgram(self->handle);

    error = glGetError();

    Int status = 0;

    glGetProgramiv(self->handle, GL_LINK_STATUS, (GLint*) &status);

    for (index = POGL_SHADER_SCHEDULE_STAGES; index > 0; index -= 1) {
        POglShaderStage* stage = &schedule->stages[index - 1];

        if (glIsShader(stage->handle) != 0)
            glDetachShader(self->handle, stage->handle);
    }

    if (status == GL_TRUE) return 1;

    return 0;
}

#endif // P_GRAPHICS_OPENGL_SHADER_C
