#ifndef RN_SYSTEM_ASYNCIO_TASK_H
#define RN_SYSTEM_ASYNCIO_TASK_H

#include "./import.h"

typedef void RnAsyncIOTask;

RnAsyncIOTask*
rnAsyncIOTaskAccept(RnMemoryArena* arena, RnSocketTCP* self, RnSocketTCP* value);

RnAsyncIOTask*
rnAsyncIOTaskConnect(RnMemoryArena* arena, RnSocketTCP* self, RnAddressIP address, u16 port);

#endif // RN_SYSTEM_ASYNCIO_TASK_H
