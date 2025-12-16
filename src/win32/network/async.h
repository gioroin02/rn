#ifndef PX_WIN32_NETWORK_ASYNC_H
#define PX_WIN32_NETWORK_ASYNC_H

#include "socket-tcp.h"
#include "socket-udp.h"

typedef struct PxWin32SocketTCPTaskAccept
{
    PxWin32SocketTCP* listener;
    PxWin32SocketTCP* socket;

    u8    buffer[256];
    ssize size;
}
PxWin32SocketTCPTaskAccept;

typedef struct PxWin32SocketTCPTaskConnect
{
    PxWin32SocketTCP* socket;
    PxAddressIP       address;
    u16               port;
}
PxWin32SocketTCPTaskConnect;

typedef struct PxWin32SocketTCPTaskWrite
{
    PxWin32SocketTCP* socket;
    u8*               values;
    ssize             start;
    ssize             stop;
    WSABUF            buffer;
    DWORD             flags;
}
PxWin32SocketTCPTaskWrite;

typedef struct PxWin32SocketTCPTaskRead
{
    PxWin32SocketTCP* socket;
    u8*               values;
    ssize             start;
    ssize             stop;
    WSABUF            buffer;
    DWORD             flags;
}
PxWin32SocketTCPTaskRead;

typedef struct PxWin32SocketTCPTask
{
    PxSocketTCPAsyncKind kind;

    void* ctxt;

    union
    {
        PxWin32SocketTCPTaskAccept  accept;
        PxWin32SocketTCPTaskConnect connect;
        PxWin32SocketTCPTaskWrite   write;
        PxWin32SocketTCPTaskRead    read;
    };
}
PxWin32SocketTCPTask;

PxWin32AsyncIOTask*
pxWin32SocketTCPAsyncAccept(PxMemoryArena* arena, void* ctxt, void* proc,
    PxWin32SocketTCP* listener, PxWin32SocketTCP* socket);

PxWin32AsyncIOTask*
pxWin32SocketTCPAsyncConnect(PxMemoryArena* arena, void* ctxt, void* proc,
    PxWin32SocketTCP* socket, PxAddressIP address, u16 port);

PxWin32AsyncIOTask*
pxWin32SocketTCPAsyncWrite(PxMemoryArena* arena, void* ctxt, void* proc,
    PxWin32SocketTCP* socket, u8* values, ssize start, ssize stop);

PxWin32AsyncIOTask*
pxWin32SocketTCPAsyncRead(PxMemoryArena* arena, void* ctxt, void* proc,
    PxWin32SocketTCP* socket, u8* values, ssize start, ssize stop);

#endif // PX_WIN32_NETWORK_ASYNC_H
