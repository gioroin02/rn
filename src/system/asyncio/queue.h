#ifndef PX_SYSTEM_ASYNCIO_QUEUE_H
#define PX_SYSTEM_ASYNCIO_QUEUE_H

#include "import.h"

typedef void PxAsyncIOTask;
typedef void PxAsyncIOQueue;

PxAsyncIOQueue*
pxAsyncIOQueueReserve(PxMemoryArena* arena);

b32
pxAsyncIOQueueCreate(PxAsyncIOQueue* self);

void
pxAsyncIOQueueDestroy(PxAsyncIOQueue* self);

b32
pxAsyncIOQueueSubmit(PxAsyncIOQueue* self, PxAsyncIOTask* task);

b32
pxAsyncIOQueuePoll(PxAsyncIOQueue* self, ssize timeout);

#endif // PX_SYSTEM_ASYNCIO_QUEUE_H
