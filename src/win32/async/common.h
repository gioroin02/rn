#ifndef PX_WIN32_ASYNC_COMMON_H
#define PX_WIN32_ASYNC_COMMON_H

#include "import.h"

#define WIN32_LEAN_AND_MEAN

#include <windows.h>

typedef struct PxWin32AsyncTask
{
    ssize kind;
    void* body;
    void* event;

    void* proc_prepare;
    void* proc_complete;

    OVERLAPPED overlap;

    struct PxWin32AsyncTask* pending_next;
}
PxWin32AsyncTask;

typedef struct PxWin32Async
{
    HANDLE handle;

    PxWin32AsyncTask* pending_front;
    PxWin32AsyncTask* pending_back;
}
PxWin32Async;

typedef b32 (PxWin32AsyncTaskProcPrepare)  (PxWin32AsyncTask*, PxWin32Async*);
typedef b32 (PxWin32AsyncTaskProcComplete) (PxWin32AsyncTask*, ssize);

PxWin32Async*
pxWin32AsyncReserve(PxMemoryArena* arena);

b32
pxWin32AsyncCreate(PxWin32Async* self);

void
pxWin32AsyncDestroy(PxWin32Async* self);

b32
pxWin32AsyncSubmit(PxWin32Async* self, ssize kind, PxWin32AsyncTask* task);

ssize
pxWin32AsyncPoll(PxWin32Async* self, void** event, ssize timeout);

#endif // PX_WIN32_ASYNC_COMMON_H
