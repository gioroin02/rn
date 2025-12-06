#ifndef RN_SYSTEM_ASYNCIO_TASK_H
#define RN_SYSTEM_ASYNCIO_TASK_H

#include "./import.h"

typedef void RnAsyncIOTask;

RnAsyncIOTask*
rnAsyncIOTaskAccept(RnMemoryArena* arena, RnSocketTCP* socket, RnSocketTCP* value);

RnAsyncIOTask*
rnAsyncIOTaskConnect(RnMemoryArena* arena, RnSocketTCP* socket, RnAddressIP address, u16 port);

RnAsyncIOTask*
rnAsyncIOTaskWrite(RnMemoryArena* arena, RnSocketTCP* socket, u8* buffer, ssize size);

RnAsyncIOTask*
rnAsyncIOTaskRead(RnMemoryArena* arena, RnSocketTCP* socket, u8* buffer, ssize size);

#endif // RN_SYSTEM_ASYNCIO_TASK_H
