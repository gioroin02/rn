#ifndef P_SYSTEM_ASYNCIO_QUEUE_H
#define P_SYSTEM_ASYNCIO_QUEUE_H

#include "import.h"

typedef struct PAsyncIoQueue { U8 __private__; } PAsyncIoQueue;

PAsyncIoQueue* pAsyncIoQueueReserve(PMemoryArena* arena);

Bool pAsyncIoQueueCreate(PAsyncIoQueue* self, PMemoryPool pool);

void pAsyncIoQueueDestroy(PAsyncIoQueue* self);

void pAsyncIoQueuePollEvents(PAsyncIoQueue* self, Int timeout);

#endif // P_SYSTEM_ASYNCIO_QUEUE_H
