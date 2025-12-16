#ifndef PX_SYSTEM_ASYNCIO_QUEUE_C
#define PX_SYSTEM_ASYNCIO_QUEUE_C

#include "queue.h"

#if PX_SYSTEM == PX_SYSTEM_WINDOWS

    #include "../../win32/asyncio/export.c"

    #define __pxAsyncIOQueueReserve__ pxWin32AsyncIOQueueReserve
    #define __pxAsyncIOQueueCreate__  pxWin32AsyncIOQueueCreate
    #define __pxAsyncIOQueueDestroy__ pxWin32AsyncIOQueueDestroy
    #define __pxAsyncIOQueueSubmit__  pxWin32AsyncIOQueueSubmit
    #define __pxAsyncIOQueuePoll__    pxWin32AsyncIOQueuePoll

#else

    #error "Unknown platform"

#endif

PxAsyncIOQueue*
pxAsyncIOQueueReserve(PxMemoryArena* arena)
{
    return __pxAsyncIOQueueReserve__(arena);
}

b32
pxAsyncIOQueueCreate(PxAsyncIOQueue* self)
{
    return __pxAsyncIOQueueCreate__(self);
}

void
pxAsyncIOQueueDestroy(PxAsyncIOQueue* self)
{
    return __pxAsyncIOQueueDestroy__(self);
}

b32
pxAsyncIOQueueSubmit(PxAsyncIOQueue* self, PxAsyncIOTask* task)
{
    return __pxAsyncIOQueueSubmit__(self, task);
}

b32
pxAsyncIOQueuePoll(PxAsyncIOQueue* self, ssize timeout)
{
    return __pxAsyncIOQueuePoll__(self, timeout);
}

#endif // PX_SYSTEM_ASYNCIO_QUEUE_C
