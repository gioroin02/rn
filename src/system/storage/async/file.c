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

PFileEvent pFileEventWrite(PFile* self, U8* pntr, Int start, Int stop, Int bytes, void* ctxt)
{
    PFileEvent result;

    pMemorySet(&result, sizeof result, 0xAB);

    result.kind        = PFileEvent_Write;
    result.write.ctxt  = ctxt;
    result.write.file  = self;
    result.write.pntr  = pntr;
    result.write.start = start;
    result.write.stop  = stop;
    result.write.bytes = bytes;

    return result;
}

PFileEvent pFileEventRead(PFile* self, U8* pntr, Int start, Int stop, Int bytes, void* ctxt)
{
    PFileEvent result;

    pMemorySet(&result, sizeof result, 0xAB);

    result.kind       = PFileEvent_Read;
    result.read.ctxt  = ctxt;
    result.read.file  = self;
    result.read.pntr  = pntr;
    result.read.start = start;
    result.read.stop  = stop;
    result.read.bytes = bytes;

    return result;
}

Bool pFileWriteAsync(PFile* self, U8* pntr, Int start, Int stop, PAsyncIoQueue* queue, void* ctxt)
{
    return __pFileWriteAsync__((__PFile__*) self, pntr, start, stop, (__PAsyncIoQueue__*) queue, ctxt);
}

Bool pFileReadAsync(PFile* self, U8* pntr, Int start, Int stop, PAsyncIoQueue* queue, void* ctxt)
{
    return __pFileReadAsync__((__PFile__*) self, pntr, start, stop, (__PAsyncIoQueue__*) queue, ctxt);
}

#endif // P_SYSTEM_STORAGE_ASYNC_FILE_C
