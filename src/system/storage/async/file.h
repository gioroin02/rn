#ifndef P_SYSTEM_STORAGE_ASYNC_FILE_H
#define P_SYSTEM_STORAGE_ASYNC_FILE_H

#include "import.h"

typedef enum PFileEventKind
{
    PFileEvent_None,
    PFileEvent_Write,
    PFileEvent_Read,
}
PFileEventKind;

typedef struct PFileEventWrite
{
    void*  ctxt;
    PFile* file;
    U8*    pntr;
    Int    start;
    Int    stop;
    Int    bytes;
}
PFileEventWrite;

typedef struct PFileEventRead
{
    void*  ctxt;
    PFile* file;
    U8*    pntr;
    Int    start;
    Int    stop;
    Int    bytes;
}
PFileEventRead;

typedef struct PFileEvent
{
    PFileEventKind kind;

    union
    {
        PFileEventWrite write;
        PFileEventRead  read;
    };
}
PFileEvent;

PFileEvent pFileEventWrite(PFile* self, U8* pntr, Int start, Int stop, Int bytes, void* ctxt);

PFileEvent pFileEventRead(PFile* self, U8* pntr, Int start, Int stop, Int bytes, void* ctxt);

B32 pFileWriteAsync(PFile* self, U8* pntr, Int start, Int stop, PAsyncIoQueue* queue, void* ctxt);

B32 pFileReadAsync(PFile* self, U8* pntr, Int start, Int stop, PAsyncIoQueue* queue, void* ctxt);

#endif
