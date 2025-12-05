#ifndef RN_WIN32_ASYNCIO_TASK_H
#define RN_WIN32_ASYNCIO_TASK_H

#include "./import.h"

typedef struct RnWin32AsyncIOTaskAccept
{
    RnWin32SocketTCP* self;
    RnWin32SocketTCP* value;
    u8*               buffer;
    ssize             size;
}
RnWin32AsyncIOTaskAccept;

typedef struct RnWin32AsyncIOTaskConnect
{
    RnWin32SocketTCP* self;
    RnAddressIP       address;
    u16               port;
}
RnWin32AsyncIOTaskConnect;

typedef struct RnWin32AsyncIOTask
{
    RnAsyncIOEventKind kind;

    struct RnWin32AsyncIOTask* next;
    struct RnWin32AsyncIOTask* prev;

    OVERLAPPED overlap;

    union
    {
        RnWin32AsyncIOTaskAccept  accept;
        RnWin32AsyncIOTaskConnect connect;
    };
}
RnWin32AsyncIOTask;

RnWin32AsyncIOTask*
rnWin32AsyncIOTaskAccept(RnMemoryArena* arena, RnWin32SocketTCP* self, RnWin32SocketTCP* value);

RnWin32AsyncIOTask*
rnWin32AsyncIOTaskConnect(RnMemoryArena* arena, RnWin32SocketTCP* self, RnAddressIP address, u16 port);

#endif // RN_WIN32_ASYNCIO_TASK_H
