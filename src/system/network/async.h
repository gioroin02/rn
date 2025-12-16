#ifndef PX_SYSTEM_NETWORK_ASYNC_H
#define PX_SYSTEM_NETWORK_ASYNC_H

#include "socket-tcp.h"
#include "socket-udp.h"

typedef enum PxSocketTCPAsyncKind
{
    PxSocketTCPAsync_None,
    PxSocketTCPAsync_Error,
    PxSocketTCPAsync_Accept,
    PxSocketTCPAsync_Connect,
    PxSocketTCPAsync_Write,
    PxSocketTCPAsync_Read,
    PxSocketTCPAsync_Close,
}
PxSocketTCPAsyncKind;

typedef struct PxSocketTCPEventAccept
{
    PxSocketTCP* listener;
    PxSocketTCP* socket;
}
PxSocketTCPEventAccept;

typedef struct PxSocketTCPEventConnect
{
    PxSocketTCP* socket;
    b32          status;
}
PxSocketTCPEventConnect;

typedef struct PxSocketTCPEventWrite
{
    PxSocketTCP* socket;
    u8*          values;
    ssize        start;
    ssize        stop;
}
PxSocketTCPEventWrite;

typedef struct PxSocketTCPEventRead
{
    PxSocketTCP* socket;
    u8*          values;
    ssize        start;
    ssize        stop;
}
PxSocketTCPEventRead;

typedef struct PxSocketTCPEventClose
{
    PxSocketTCP* socket;
}
PxSocketTCPEventClose;

typedef struct PxSocketTCPEvent
{
    PxSocketTCPAsyncKind kind;

    void* ctxt;

    union
    {
        PxSocketTCPEventAccept  accept;
        PxSocketTCPEventConnect connect;
        PxSocketTCPEventWrite   write;
        PxSocketTCPEventRead    read;
        PxSocketTCPEventClose   close;
    };
}
PxSocketTCPEvent;

PxSocketTCPEvent
pxSocketTCPEventAccept(void* ctxt, PxSocketTCP* listener, PxSocketTCP* socket);

PxSocketTCPEvent
pxSocketTCPEventConnect(void* ctxt, PxSocketTCP* socket, b32 status);

PxSocketTCPEvent
pxSocketTCPEventWrite(void* ctxt, PxSocketTCP* socket, u8* values, ssize start, ssize stop);

PxSocketTCPEvent
pxSocketTCPEventRead(void* ctxt, PxSocketTCP* socket, u8* values, ssize start, ssize stop);

PxSocketTCPEvent
pxSocketTCPEventClose(void* ctxt, PxSocketTCP* socket);

PxAsyncIOTask*
pxSocketTCPAsyncAccept(PxMemoryArena* arena, void* ctxt, void* proc,
    PxSocketTCP* listener, PxSocketTCP* socket);

PxAsyncIOTask*
pxSocketTCPAsyncConnect(PxMemoryArena* arena, void* ctxt, void* proc,
    PxSocketTCP* socket, PxAddressIP address, u16 port);

PxAsyncIOTask*
pxSocketTCPAsyncWrite(PxMemoryArena* arena, void* ctxt, void* proc,
    PxSocketTCP* socket, u8* values, ssize start, ssize stop);

PxAsyncIOTask*
pxSocketTCPAsyncRead(PxMemoryArena* arena, void* ctxt, void* proc,
    PxSocketTCP* socket, u8* values, ssize start, ssize stop);

#endif // PX_SYSTEM_NETWORK_ASYNC_H
