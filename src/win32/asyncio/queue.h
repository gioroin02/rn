#ifndef PX_WIN32_ASYNCIO_QUEUE_H
#define PX_WIN32_ASYNCIO_QUEUE_H

#include "import.h"

#define WIN32_LEAN_AND_MEAN

#include <windows.h>

typedef struct PxWin32AsyncIOTask
{
    void* ctxt;
    void* procCallback;
    void* procPrepare;
    void* procComplete;

    OVERLAPPED overlap;

    struct PxWin32AsyncIOTask* prev;
    struct PxWin32AsyncIOTask* next;
}
PxWin32AsyncIOTask;

typedef struct PxWin32AsyncIOQueue
{
    HANDLE handle;

    PxWin32AsyncIOTask* head;
    PxWin32AsyncIOTask* tail;
}
PxWin32AsyncIOQueue;

typedef void (PxWin32AsyncIOProcCallback) (void*, void*);
typedef b32  (PxWin32AsyncIOProcPrepare)  (PxWin32AsyncIOTask*, PxWin32AsyncIOQueue*);
typedef b32  (PxWin32AsyncIOProcComplete) (PxWin32AsyncIOTask*, ssize);

PxWin32AsyncIOQueue*
pxWin32AsyncIOQueueReserve(PxMemoryArena* arena);

b32
pxWin32AsyncIOQueueCreate(PxWin32AsyncIOQueue* self);

void
pxWin32AsyncIOQueueDestroy(PxWin32AsyncIOQueue* self);

b32
pxWin32AsyncIOQueueSubmit(PxWin32AsyncIOQueue* self, PxWin32AsyncIOTask* task);

b32
pxWin32AsyncIOQueuePoll(PxWin32AsyncIOQueue* self, ssize timeout);

#endif // PX_WIN32_ASYNCIO_QUEUE_H
