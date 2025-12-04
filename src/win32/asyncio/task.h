#ifndef RN_WIN32_ASYNCIO_TASK_H
#define RN_WIN32_ASYNCIO_TASK_H

#include "./import.h"

typedef struct RnWin32AyncIOTaskAccept
{
    RnWin32SocketTCP* listener;
    RnWin32SocketTCP* socket;
    u8*               buffer;
    ssize             size;
}
RnWin32AsyncIOTaskAccept;

typedef struct RnWin32AsyncIOTask
{
    RnAsyncIOEventKind kind;

    struct RnWin32AsyncIOTask* next;
    struct RnWin32AsyncIOTask* prev;

    OVERLAPPED overlap;

    union
    {
        RnWin32AsyncIOTaskAccept accept;
    };
}
RnWin32AsyncIOTask;

RnWin32AsyncIOTask*
rnWin32AsyncIOTaskAccept(RnMemoryArena* arena, RnWin32SocketTCP* listener, RnWin32SocketTCP* socket);

#endif // RN_WIN32_ASYNCIO_TASK_H
