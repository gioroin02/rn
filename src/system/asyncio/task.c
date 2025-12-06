#ifndef RN_SYSTEM_ASYNCIO_TASK_C
#define RN_SYSTEM_ASYNCIO_TASK_C

#include "./task.h"

#if RN_SYSTEM == RN_SYSTEM_WINDOWS

    #include "../../win32/asyncio/export.c"

    #define __rnAsyncIOTaskAccept__  rnWin32AsyncIOTaskAccept
    #define __rnAsyncIOTaskConnect__ rnWin32AsyncIOTaskConnect
    #define __rnAsyncIOTaskWrite__   rnWin32AsyncIOTaskWrite
    #define __rnAsyncIOTaskRead__    rnWin32AsyncIOTaskRead

#else

    #error "Unknown platform"

#endif

RnAsyncIOTask*
rnAsyncIOTaskAccept(RnMemoryArena* arena, RnSocketTCP* socket, RnSocketTCP* value)
{
    return __rnAsyncIOTaskAccept__(arena, socket, value);
}

RnAsyncIOTask*
rnAsyncIOTaskConnect(RnMemoryArena* arena, RnSocketTCP* socket, RnAddressIP address, u16 port)
{
    return __rnAsyncIOTaskConnect__(arena, socket, address, port);
}

RnAsyncIOTask*
rnAsyncIOTaskWrite(RnMemoryArena* arena, RnSocketTCP* socket, u8* buffer, ssize size)
{
    return __rnAsyncIOTaskWrite__(arena, socket, buffer, size);
}

RnAsyncIOTask*
rnAsyncIOTaskRead(RnMemoryArena* arena, RnSocketTCP* socket, u8* buffer, ssize size)
{
    return __rnAsyncIOTaskRead__(arena, socket, buffer, size);
}

#endif // RN_SYSTEM_ASYNCIO_TASK_C
