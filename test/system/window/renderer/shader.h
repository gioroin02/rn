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

Bool pShaderStageCreate(PShaderStage* self, PShaderStageKind kind);

void pShaderStageDestroy(PShaderStage* self);

Bool pShaderStageCompile(PShaderStage* self, PString8 source);

void pShaderScheduleClear(PShaderSchedule* self);

Bool pShaderScheduleCreate(PShaderSchedule* self, PShaderStageKind kind);

void pShaderScheduleDestroy(PShaderSchedule* self, PShaderStageKind kind);

Bool pShaderScheduleCompile(PShaderSchedule* self, PShaderStageKind kind, PString8 source);

Bool pShaderCreate(PShader* self);

void pShaderDestroy(PShader* self);

Bool pShaderLink(PShader* self, PShaderSchedule* schedule);

#endif // P_GRAPHICS_SHADER_H
