#ifndef RN_WIN32_ASYNCIO_EVENT_H
#define RN_WIN32_ASYNCIO_EVENT_H

#include "./import.h"

#define rnAsyncIOEventError() \
    ((RnAsyncIOEvent) {.kind = RnAsyncIOEvent_Error})

typedef enum RnAsyncIOEventKind
{
    RnAsyncIOEvent_None,

    RnAsyncIOEvent_Error,

    RnAsyncIOEvent_Accept,
    RnAsyncIOEvent_Connect,
    RnAsyncIOEvent_Write,
    RnAsyncIOEvent_Read,
    RnAsyncIOEvent_Close,
}
RnAsyncIOEventKind;

typedef struct RnAsyncIOEventAccept
{
    RnSocketTCP* socket;
    RnSocketTCP* value;
}
RnAsyncIOEventAccept;

typedef struct RnAsyncIOEventConnect
{
    RnSocketTCP* socket;
    b32          status;
}
RnAsyncIOEventConnect;

typedef struct RnAsyncIOEventWrite
{
    RnSocketTCP* socket;
    u8*          buffer;
    ssize        size;
    ssize        count;
}
RnAsyncIOEventWrite;

typedef struct RnAsyncIOEventRead
{
    RnSocketTCP* socket;
    u8*          buffer;
    ssize        size;
    ssize        count;
}
RnAsyncIOEventRead;

typedef struct RnAsyncIOEventClose
{
    RnSocketTCP* socket;
}
RnAsyncIOEventClose;

typedef struct RnAsyncIOEvent
{
    RnAsyncIOEventKind kind;

    union
    {
        RnAsyncIOEventAccept  accept;
        RnAsyncIOEventConnect connect;
        RnAsyncIOEventWrite   write;
        RnAsyncIOEventRead    read;
        RnAsyncIOEventClose   close;
    };
}
RnAsyncIOEvent;

RnAsyncIOEvent
rnAsyncIOEventAccept(RnSocketTCP* socket, RnSocketTCP* value);

RnAsyncIOEvent
rnAsyncIOEventConnect(RnSocketTCP* socket, b32 status);

RnAsyncIOEvent
rnAsyncIOEventWrite(RnSocketTCP* socket, u8* buffer, ssize size, ssize count);

RnAsyncIOEvent
rnAsyncIOEventRead(RnSocketTCP* socket, u8* buffer, ssize size, ssize count);

RnAsyncIOEvent
rnAsyncIOEventClose(RnSocketTCP* socket);

#endif // RN_WIN32_ASYNCIO_EVENT_H
