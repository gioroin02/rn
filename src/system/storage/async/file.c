#ifndef P_SYSTEM_STORAGE_ASYNC_FILE_C
#define P_SYSTEM_STORAGE_ASYNC_FILE_C

#include "file.h"

#if P_SYSTEM == P_SYSTEM_WINDOWS

    #include "win32/export.c"

    #define __PAsyncIoQueue__ PWin32AsyncIoQueue
    #define __PFile__         PWin32File

    #define __pFileWriteAsync__ pWin32FileWriteAsync
    #define __pFileReadAsync__  pWin32FileReadAsync

#else

    #error "Unknown platform"

#endif

Bool pFileWriteAsync(PFile* self, U8* pntr, Int start, Int stop, PAsyncIoQueue* queue, void* ctxt, void* proc)
{
    return __pFileWriteAsync__(self, pntr, start, stop, queue, proc, ctxt);
}

Bool pFileReadAsync(PFile* self, U8* pntr, Int start, Int stop, PAsyncIoQueue* queue, void* ctxt, void* proc)
{
    return __pFileReadAsync__(self, pntr, start, stop, queue, proc, ctxt);
}

#endif // P_SYSTEM_STORAGE_ASYNC_FILE_C
