#ifndef RHO_GRAPHICS_OPENGL_COMMON_H
#define RHO_GRAPHICS_OPENGL_COMMON_H

#include "import.h"

typedef enum ROpenglProfile
{
    ROpenglProfile_None,
    ROpenglProfile_Compatibility,
    ROpenglProfile_Core,
}
ROpenglProfile;

typedef enum ROpenglContextFlag
{
    ROpenglContextFlag_None  = 0,
    ROpenglContextFlag_Debug = 1 << 0,
}
ROpenglContextFlag;

typedef struct ROpenglContextAttribs
{
    ROpenglProfile profile;

    ROpenglContextFlag flag;

    RInt16 version_major;
    RInt16 version_minor;
}
ROpenglContextAttribs;

void* rho_opengl_loader(void* symbol);

#endif
