#ifndef RN_WIN32_ASYNCIO_TASK_H
#define RN_WIN32_ASYNCIO_TASK_H

#include "./import.h"

typedef struct RnWin32AsyncIOTaskAccept
{
    RnWin32SocketTCP* socket;
    RnWin32SocketTCP* value;
    u8*               buffer;
    ssize             size;
}
RnWin32AsyncIOTaskAccept;

typedef struct RnWin32AsyncIOTaskConnect
{
    RnWin32SocketTCP* socket;
    RnAddressIP       address;
    u16               port;
}
RnWin32AsyncIOTaskConnect;

typedef struct RnWin32AsyncIOTaskWrite
{
    RnWin32SocketTCP* socket;
    WSABUF            buffer;
    DWORD             flags;
}
RnWin32AsyncIOTaskWrite;

typedef struct RnWin32AsyncIOTaskRead
{
    RnWin32SocketTCP* socket;
    WSABUF            buffer;
    DWORD             flags;
}
RnWin32AsyncIOTaskRead;

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
        RnWin32AsyncIOTaskWrite   write;
        RnWin32AsyncIOTaskRead    read;
    };
}
RnWin32AsyncIOTask;

RnWin32AsyncIOTask*
rnWin32AsyncIOTaskAccept(RnMemoryArena* arena, RnWin32SocketTCP* socket, RnWin32SocketTCP* value);

RnWin32AsyncIOTask*
rnWin32AsyncIOTaskConnect(RnMemoryArena* arena, RnWin32SocketTCP* socket, RnAddressIP address, u16 port);

RnWin32AsyncIOTask*
rnWin32AsyncIOTaskWrite(RnMemoryArena* arena, RnWin32SocketTCP* socket, u8* buffer, ssize size);

RnWin32AsyncIOTask*
rnWin32AsyncIOTaskRead(RnMemoryArena* arena, RnWin32SocketTCP* socket, u8* buffer, ssize size);

#endif // RN_WIN32_ASYNCIO_TASK_H
