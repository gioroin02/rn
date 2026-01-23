#ifndef P_SYSTEM_WIN32_STORAGE_ASYNC_FILE_H
#define P_SYSTEM_WIN32_STORAGE_ASYNC_FILE_H

#include "import.h"

typedef struct PWin32FileWrite
{
    __PWin32AsyncIoTaskTag__;

    PWin32File* self;
    void*       ctxt;

    U8* pntr;
    Int start;
    Int stop;
}
PWin32FileWrite;

typedef struct PWin32FileRead
{
    __PWin32AsyncIoTaskTag__;

    PWin32File* self;
    void*       ctxt;

    U8* pntr;
    Int start;
    Int stop;
}
PWin32FileRead;

Bool pWin32FileWriteAsync(PWin32File* self, U8* pntr, Int start, Int stop, PWin32AsyncIoQueue* queue, void* ctxt);

Bool pWin32FileReadAsync(PWin32File* self, U8* pntr, Int start, Int stop, PWin32AsyncIoQueue* queue, void* ctxt);

#endif
