#ifndef RN_SYSTEM_NETWORK_ASYNC_H
#define RN_SYSTEM_NETWORK_ASYNC_H

#include "./socket-tcp.h"
#include "./socket-udp.h"

typedef enum RnSocketTCPAsyncKind
{
    RnSocketTCPAsync_None,
    RnSocketTCPAsync_Error,
    RnSocketTCPAsync_Accept,
    RnSocketTCPAsync_Connect,
    RnSocketTCPAsync_Write,
    RnSocketTCPAsync_Read,
    RnSocketTCPAsync_Close,
}
RnSocketTCPAsyncKind;

typedef struct RnSocketTCPEventAccept
{
    RnSocketTCP* listener;
    RnSocketTCP* socket;
}
RnSocketTCPEventAccept;

typedef struct RnSocketTCPEventConnect
{
    RnSocketTCP* socket;
    b32          status;
}
RnSocketTCPEventConnect;

typedef struct RnSocketTCPEventWrite
{
    RnSocketTCP* socket;
    u8*          values;
    ssize        start;
    ssize        stop;
}
RnSocketTCPEventWrite;

typedef struct RnSocketTCPEventRead
{
    RnSocketTCP* socket;
    u8*          values;
    ssize        start;
    ssize        stop;
}
RnSocketTCPEventRead;

typedef struct RnSocketTCPEventClose
{
    RnSocketTCP* socket;
}
RnSocketTCPEventClose;

typedef struct RnSocketTCPEvent
{
    RnSocketTCPAsyncKind kind;

    void* ctxt;

    union
    {
        RnSocketTCPEventAccept  accept;
        RnSocketTCPEventConnect connect;
        RnSocketTCPEventWrite   write;
        RnSocketTCPEventRead    read;
        RnSocketTCPEventClose   close;
    };
}
RnSocketTCPEvent;

RnSocketTCPEvent
rnSocketTCPEventAccept(void* ctxt, RnSocketTCP* listener, RnSocketTCP* socket);

RnSocketTCPEvent
rnSocketTCPEventConnect(void* ctxt, RnSocketTCP* socket, b32 status);

RnSocketTCPEvent
rnSocketTCPEventWrite(void* ctxt, RnSocketTCP* socket, u8* values, ssize start, ssize stop);

RnSocketTCPEvent
rnSocketTCPEventRead(void* ctxt, RnSocketTCP* socket, u8* values, ssize start, ssize stop);

RnSocketTCPEvent
rnSocketTCPEventClose(void* ctxt, RnSocketTCP* socket);

RnAsyncIOTask*
rnSocketTCPAsyncAccept(RnMemoryArena* arena, void* ctxt, void* proc,
    RnSocketTCP* listener, RnSocketTCP* socket);

RnAsyncIOTask*
rnSocketTCPAsyncConnect(RnMemoryArena* arena, void* ctxt, void* proc,
    RnSocketTCP* socket, RnAddressIP address, u16 port);

RnAsyncIOTask*
rnSocketTCPAsyncWrite(RnMemoryArena* arena, void* ctxt, void* proc,
    RnSocketTCP* socket, u8* values, ssize start, ssize stop);

RnAsyncIOTask*
rnSocketTCPAsyncRead(RnMemoryArena* arena, void* ctxt, void* proc,
    RnSocketTCP* socket, u8* values, ssize start, ssize stop);

#endif // RN_SYSTEM_NETWORK_ASYNC_H
