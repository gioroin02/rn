#ifndef RN_SYSTEM_ASYNCIO_TASK_C
#define RN_SYSTEM_ASYNCIO_TASK_C

#include "./task.h"

#if RN_SYSTEM == RN_SYSTEM_WINDOWS

    #include "../../win32/asyncio/export.c"

    #define __rnAsyncIOTaskAccept__ rnWin32AsyncIOTaskAccept

#else

    #error "Unknown platform"

#endif

RnAsyncIOTask*
rnAsyncIOTaskAccept(RnMemoryArena* arena, RnSocketTCP* listener, RnSocketTCP* socket)
{
    return __rnAsyncIOTaskAccept__(arena, listener, socket);
}

#endif // RN_SYSTEM_ASYNCIO_TASK_C
