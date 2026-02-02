#ifndef RHO_SYSTEM_STORAGE_ASYNC_FILE_C
#define RHO_SYSTEM_STORAGE_ASYNC_FILE_C

#include "file.h"

#if RHO_SYSTEM == RHO_SYSTEM_WINDOWS

    #include "win32/export.c"

    #define __RIoQueue__ RWin32IoQueue
    #define __RFile__    RWin32File

    #define __rho_file_async_write__ rho_win32_file_async_write
    #define __rho_file_async_read__  rho_win32_file_async_read

#elif RHO_SYSTEM == RHO_SYSTEM_LINUX

    #include "linux/export.c"

    #define __RIoQueue__ RLinuxIoQueue
    #define __RFile__    RLinuxFile

    #define __rho_file_async_write__ rho_linux_file_async_write
    #define __rho_file_async_read__  rho_linux_file_async_read


#else

    #error "Unknown platform"

#endif

RFileEvent rho_file_event_write(RFile* self, RUint8* pntr, RInt start, RInt stop, RInt bytes, void* ctxt)
{
    RFileEvent result = {0};

    rho_memory_set(&result, sizeof result, 0xAB);

    result.family      = RIoEventFamily_File;
    result.kind        = RFileEvent_Write;
    result.write.ctxt  = ctxt;
    result.write.file  = self;
    result.write.pntr  = pntr;
    result.write.start = start;
    result.write.stop  = stop;
    result.write.bytes = bytes;

    return result;
}

RFileEvent rho_file_event_read(RFile* self, RUint8* pntr, RInt start, RInt stop, RInt bytes, void* ctxt)
{
    RFileEvent result = {0};

    rho_memory_set(&result, sizeof result, 0xAB);

    result.family     = RIoEventFamily_File;
    result.kind       = RFileEvent_Read;
    result.read.ctxt  = ctxt;
    result.read.file  = self;
    result.read.pntr  = pntr;
    result.read.start = start;
    result.read.stop  = stop;
    result.read.bytes = bytes;

    return result;
}

RBool32 rho_file_async_write(RFile* self, RUint8* pntr, RInt start, RInt stop, RIoQueue* queue, void* ctxt)
{
    return __rho_file_async_write__((__RFile__*) self, pntr, start, stop, (__RIoQueue__*) queue, ctxt);
}

RBool32 rho_file_async_read(RFile* self, RUint8* pntr, RInt start, RInt stop, RIoQueue* queue, void* ctxt)
{
    return __rho_file_async_read__((__RFile__*) self, pntr, start, stop, (__RIoQueue__*) queue, ctxt);
}

#endif
