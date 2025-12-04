#ifndef RN_SYSTEM_ASYNCIO_TASK_H
#define RN_SYSTEM_ASYNCIO_TASK_H

#include "./import.h"

typedef void RnAsyncIOTask;

RnAsyncIOTask*
rnAsyncIOTaskAccept(RnMemoryArena* arena, RnSocketTCP* listener, RnSocketTCP* socket);

#endif // RN_SYSTEM_ASYNCIO_TASK_H
