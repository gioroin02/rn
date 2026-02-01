#ifndef RHO_SYSTEM_STORAGE_FILE_C
#define RHO_SYSTEM_STORAGE_FILE_C

#include "file.h"

#if RHO_SYSTEM == RHO_SYSTEM_WINDOWS

    #include "win32/export.c"

    #define __RFile__ RWin32File

    #define __rho_file_find__    rho_win32_file_find
    #define __rho_file_delete__  rho_win32_file_delete
    #define __rho_file_reserve__ rho_win32_file_reserve
    #define __rho_file_open__    rho_win32_file_open
    #define __rho_file_close__   rho_win32_file_close
    #define __rho_file_write__   rho_win32_file_write
    #define __rho_file_read__    rho_win32_file_read

#elif RHO_SYSTEM == RHO_SYSTEM_LINUX

    #include "linux/export.c"

    #define __RFile__ RLinuxFile

    #define __rho_file_find__    rho_linux_file_find
    #define __rho_file_delete__  rho_linux_file_delete
    #define __rho_file_reserve__ rho_linux_file_reserve
    #define __rho_file_open__    rho_linux_file_open
    #define __rho_file_close__   rho_linux_file_close
    #define __rho_file_write__   rho_linux_file_write
    #define __rho_file_read__    rho_linux_file_read

#else

    #error "Unknown platform"

#endif

RBool32 rho_file_find(RString8 name, RFileAttribs* attribs)
{
    return __rho_file_find__(name, attribs);
}

RBool32 rho_file_delete(RString8 name)
{
    return __rho_file_delete__(name);
}

RFile* rho_file_reserve(RMemoryArena* arena)
{
    return (RFile*) __rho_file_reserve__(arena);
}

RBool32 rho_file_open(RFile* self, RString8 name, RFileMode mode)
{
    return __rho_file_open__((__RFile__*) self, name, mode);
}

void rho_file_close(RFile* self)
{
    return __rho_file_close__((__RFile__*) self);
}

RInt rho_file_write(RFile* self, RUint8* pntr, RInt start, RInt stop)
{
    return __rho_file_write__((__RFile__*) self, pntr, start, stop);
}

RInt rho_file_read(RFile* self, RUint8* pntr, RInt start, RInt stop)
{
    return __rho_file_read__((__RFile__*) self, pntr, start, stop);
}

#endif
