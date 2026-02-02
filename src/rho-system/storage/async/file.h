#ifndef RHO_SYSTEM_STORAGE_ASYNC_FILE_H
#define RHO_SYSTEM_STORAGE_ASYNC_FILE_H

#include "import.h"

typedef enum RFileEventKind
{
    RFileEvent_None,
    RFileEvent_Write,
    RFileEvent_Read,
}
RFileEventKind;

typedef struct RFileEventWrite
{
    void*   ctxt;
    RFile*  file;
    RUint8* pntr;
    RInt    start;
    RInt    stop;
    RInt    bytes;
}
RFileEventWrite;

typedef struct RFileEventRead
{
    void*   ctxt;
    RFile*  file;
    RUint8* pntr;
    RInt    start;
    RInt    stop;
    RInt    bytes;
}
RFileEventRead;

typedef struct RFileEvent
{
    RIoEventFamily family;
    RFileEventKind kind;

    union
    {
        RFileEventWrite write;
        RFileEventRead  read;
    };
}
RFileEvent;

RFileEvent rho_file_event_write(RFile* self, RUint8* pntr, RInt start, RInt stop, RInt bytes, void* ctxt);

RFileEvent rho_file_event_read(RFile* self, RUint8* pntr, RInt start, RInt stop, RInt bytes, void* ctxt);

RBool32 rho_file_async_write(RFile* self, RUint8* pntr, RInt start, RInt stop, RIoQueue* queue, void* ctxt);

RBool32 rho_file_async_read(RFile* self, RUint8* pntr, RInt start, RInt stop, RIoQueue* queue, void* ctxt);

#endif
