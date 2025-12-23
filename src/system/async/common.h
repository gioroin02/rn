#ifndef PX_SYSTEM_ASYNC_COMMON_H
#define PX_SYSTEM_ASYNC_COMMON_H

#include "import.h"

typedef void PxAsync;
typedef void PxAsyncTask;

PxAsync*
pxAsyncReserve(PxMemoryArena* arena);

b32
pxAsyncCreate(PxAsync* self);

void
pxAsyncDestroy(PxAsync* self);

b32
pxAsyncSubmit(PxAsync* self, ssize kind, PxAsyncTask* task);

ssize
pxAsyncPoll(PxAsync* self, void** event, ssize timeout);

#endif // PX_SYSTEM_ASYNC_COMMON_H
