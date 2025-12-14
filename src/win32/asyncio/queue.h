#ifndef RN_WIN32_ASYNCIO_QUEUE_H
#define RN_WIN32_ASYNCIO_QUEUE_H

#include "./import.h"

#define WIN32_LEAN_AND_MEAN

#include <windows.h>

typedef struct RnWin32AsyncIOTask
{
    void* ctxt;
    void* procCallback;
    void* procPrepare;
    void* procComplete;

    OVERLAPPED overlap;

    struct RnWin32AsyncIOTask* prev;
    struct RnWin32AsyncIOTask* next;
}
RnWin32AsyncIOTask;

typedef struct RnWin32AsyncIOQueue
{
    HANDLE handle;

    RnWin32AsyncIOTask* head;
    RnWin32AsyncIOTask* tail;
}
RnWin32AsyncIOQueue;

typedef void (RnWin32AsyncIOProcCallback) (void*, void*);
typedef b32  (RnWin32AsyncIOProcPrepare)  (RnWin32AsyncIOTask*, RnWin32AsyncIOQueue*);
typedef b32  (RnWin32AsyncIOProcComplete) (RnWin32AsyncIOTask*, ssize);

RnWin32AsyncIOQueue*
rnWin32AsyncIOQueueReserve(RnMemoryArena* arena);

b32
rnWin32AsyncIOQueueCreate(RnWin32AsyncIOQueue* self);

void
rnWin32AsyncIOQueueDestroy(RnWin32AsyncIOQueue* self);

b32
rnWin32AsyncIOQueueSubmit(RnWin32AsyncIOQueue* self, RnWin32AsyncIOTask* task);

b32
rnWin32AsyncIOQueuePoll(RnWin32AsyncIOQueue* self, ssize timeout);

#endif // RN_WIN32_ASYNCIO_QUEUE_H
