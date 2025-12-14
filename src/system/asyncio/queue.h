#ifndef RN_SYSTEM_ASYNCIO_QUEUE_H
#define RN_SYSTEM_ASYNCIO_QUEUE_H

#include "./import.h"

typedef void RnAsyncIOTask;
typedef void RnAsyncIOQueue;

RnAsyncIOQueue*
rnAsyncIOQueueReserve(RnMemoryArena* arena);

b32
rnAsyncIOQueueCreate(RnAsyncIOQueue* self);

void
rnAsyncIOQueueDestroy(RnAsyncIOQueue* self);

b32
rnAsyncIOQueueSubmit(RnAsyncIOQueue* self, RnAsyncIOTask* task);

b32
rnAsyncIOQueuePoll(RnAsyncIOQueue* self, ssize timeout);

#endif // RN_SYSTEM_ASYNCIO_QUEUE_H
