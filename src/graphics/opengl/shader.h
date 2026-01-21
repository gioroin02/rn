#ifndef P_GRAPHICS_OPENGL_SHADER_H
#define P_GRAPHICS_OPENGL_SHADER_H

#include "import.h"

#define POGL_SHADER_SCHEDULE_STAGES ((Int) 3)

typedef enum POglShaderStageKind
{
    POglShaderStage_None,
    POglShaderStage_Vertex,
    POglShaderStage_Geometry,
    POglShaderStage_Fragment,
}
POglShaderStageKind;

typedef struct POglShaderStage
{
    Int handle;
}
POglShaderStage;

typedef struct POglShader
{
    Int handle;
}
POglShader;

typedef struct POglShaderSchedule
{
    POglShaderStage stages[POGL_SHADER_SCHEDULE_STAGES];
}
POglShaderSchedule;

Bool pOglShaderStageCreate(POglShaderStage* self, POglShaderStageKind kind);

void pOglShaderStageDestroy(POglShaderStage* self);

Bool pOglShaderStageCompile(POglShaderStage* self, PString8 source);

void pOglShaderScheduleClear(POglShaderSchedule* self);

Bool pOglShaderScheduleCreate(POglShaderSchedule* self, POglShaderStageKind kind);

void pOglShaderScheduleDestroy(POglShaderSchedule* self, POglShaderStageKind kind);

Bool pOglShaderScheduleCompile(POglShaderSchedule* self, POglShaderStageKind kind, PString8 source);

Bool pOglShaderCreate(POglShader* self);

void pOglShaderDestroy(POglShader* self);

Bool pOglShaderLink(POglShader* self, POglShaderSchedule* schedule);

#endif // P_GRAPHICS_OPENGL_SHADER_H
