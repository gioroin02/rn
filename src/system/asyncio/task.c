#ifndef RN_SYSTEM_ASYNCIO_TASK_C
#define RN_SYSTEM_ASYNCIO_TASK_C

#include "./task.h"

#if RN_SYSTEM == RN_SYSTEM_WINDOWS

    #include "../../win32/asyncio/export.c"

    #define __rnAsyncIOTaskAccept__  rnWin32AsyncIOTaskAccept
    #define __rnAsyncIOTaskConnect__ rnWin32AsyncIOTaskConnect


#else

    #error "Unknown platform"

#endif

RnAsyncIOTask*
rnAsyncIOTaskAccept(RnMemoryArena* arena, RnSocketTCP* self, RnSocketTCP* value)
{
    return __rnAsyncIOTaskAccept__(arena, self, value);
}

RnAsyncIOTask*
rnAsyncIOTaskConnect(RnMemoryArena* arena, RnSocketTCP* self, RnAddressIP address, u16 port)
{
    return __rnAsyncIOTaskConnect__(arena, self, address, port);
}

#endif // RN_SYSTEM_ASYNCIO_TASK_C
