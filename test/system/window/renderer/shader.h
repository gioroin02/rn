#ifndef P_GRAPHICS_SHADER_H
#define P_GRAPHICS_SHADER_H

#include "import.h"

#define P_SHADER_SCHEDULE_STAGES ((Int) 3)

typedef enum PShaderStageKind
{
    PShaderStage_None,
    PShaderStage_Vertex,
    PShaderStage_Geometry,
    PShaderStage_Fragment,
}
PShaderStageKind;

typedef struct PShaderStage
{
    Int handle;
}
PShaderStage;

typedef struct PShader
{
    Int handle;
}
PShader;

typedef struct PShaderSchedule
{
    PShaderStage stages[P_SHADER_SCHEDULE_STAGES];
}
PShaderSchedule;

B32 pShaderStageCreate(PShaderStage* self, PShaderStageKind kind);

void pShaderStageDestroy(PShaderStage* self);

B32 pShaderStageCompile(PShaderStage* self, PString8 source);

void pShaderScheduleClear(PShaderSchedule* self);

B32 pShaderScheduleCreate(PShaderSchedule* self, PShaderStageKind kind);

void pShaderScheduleDestroy(PShaderSchedule* self, PShaderStageKind kind);

B32 pShaderScheduleCompile(PShaderSchedule* self, PShaderStageKind kind, PString8 source);

B32 pShaderCreate(PShader* self);

void pShaderDestroy(PShader* self);

B32 pShaderLink(PShader* self, PShaderSchedule* schedule);

#endif
