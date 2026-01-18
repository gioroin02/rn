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
    PFile* file;
    U8*    pntr;
    Int    start;
    Int    stop;
    Int    bytes;
}
PFileEventWrite;

typedef struct PFileEventRead
{
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

    void* ctxt;

    union
    {
        PFileEventWrite write;
        PFileEventRead  read;
    };
}
PFileEvent;

PFileEvent pFileEventWrite(PFile* self, U8* pntr, Int start, Int stop, Int bytes, void* ctxt);

PFileEvent pFileEventRead(PFile* self, U8* pntr, Int start, Int stop, Int bytes, void* ctxt);

Bool pFileWriteAsync(PFile* self, U8* pntr, Int start, Int stop, PAsyncIoQueue* queue, void* ctxt);

Bool pFileReadAsync(PFile* self, U8* pntr, Int start, Int stop, PAsyncIoQueue* queue, void* ctxt);

#endif // P_SYSTEM_STORAGE_ASYNC_FILE_H
