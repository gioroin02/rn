#ifndef P_GRAPHICS_OPENGL_COMMON_H
#define P_GRAPHICS_OPENGL_COMMON_H

#include "import.h"

typedef enum POpenglProfile
{
    POpenglProfile_None,
    POpenglProfile_Compatibility,
    POpenglProfile_Core,
}
POpenglProfile;

typedef enum POpenglContextFlag
{
    POpenglContextFlag_None  = 0,
    POpenglContextFlag_Debug = 1 << 0,
}
POpenglContextFlag;

typedef struct POpenGLContextAttribs
{
    POpenglProfile profile;

    POpenglContextFlag flag;

    Int version_major;
    Int version_minor;
}
POpenglContextAttribs;

void* pOpenglLoader(void* symbol);

#endif
