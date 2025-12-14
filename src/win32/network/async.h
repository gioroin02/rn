#ifndef RN_WIN32_NETWORK_ASYNC_H
#define RN_WIN32_NETWORK_ASYNC_H

#include "./socket-tcp.h"
#include "./socket-udp.h"

typedef struct RnWin32SocketTCPTaskAccept
{
    RnWin32SocketTCP* listener;
    RnWin32SocketTCP* socket;

    u8    buffer[256];
    ssize size;
}
RnWin32SocketTCPTaskAccept;

typedef struct RnWin32SocketTCPTaskConnect
{
    RnWin32SocketTCP* socket;
    RnAddressIP       address;
    u16               port;
}
RnWin32SocketTCPTaskConnect;

typedef struct RnWin32SocketTCPTaskWrite
{
    RnWin32SocketTCP* socket;
    u8*               values;
    ssize             start;
    ssize             stop;
    WSABUF            buffer;
    DWORD             flags;
}
RnWin32SocketTCPTaskWrite;

typedef struct RnWin32SocketTCPTaskRead
{
    RnWin32SocketTCP* socket;
    u8*               values;
    ssize             start;
    ssize             stop;
    WSABUF            buffer;
    DWORD             flags;
}
RnWin32SocketTCPTaskRead;

typedef struct RnWin32SocketTCPTask
{
    RnSocketTCPAsyncKind kind;

    void* ctxt;

    union
    {
        RnWin32SocketTCPTaskAccept  accept;
        RnWin32SocketTCPTaskConnect connect;
        RnWin32SocketTCPTaskWrite   write;
        RnWin32SocketTCPTaskRead    read;
    };
}
RnWin32SocketTCPTask;

RnWin32AsyncIOTask*
rnWin32SocketTCPAsyncAccept(RnMemoryArena* arena, void* ctxt, void* proc,
    RnWin32SocketTCP* listener, RnWin32SocketTCP* socket);

RnWin32AsyncIOTask*
rnWin32SocketTCPAsyncConnect(RnMemoryArena* arena, void* ctxt, void* proc,
    RnWin32SocketTCP* socket, RnAddressIP address, u16 port);

RnWin32AsyncIOTask*
rnWin32SocketTCPAsyncWrite(RnMemoryArena* arena, void* ctxt, void* proc,
    RnWin32SocketTCP* socket, u8* values, ssize start, ssize stop);

RnWin32AsyncIOTask*
rnWin32SocketTCPAsyncRead(RnMemoryArena* arena, void* ctxt, void* proc,
    RnWin32SocketTCP* socket, u8* values, ssize start, ssize stop);

#endif // RN_WIN32_NETWORK_ASYNC_H
