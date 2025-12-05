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
}
RnAsyncIOEventKind;

typedef struct RnAsyncIOEventAccept
{
    RnSocketTCP* socket;
}
RnAsyncIOEventAccept;

typedef struct RnAsyncIOEventConnect
{
    b32 status;
}
RnAsyncIOEventConnect;

typedef struct RnAsyncIOEvent
{
    RnAsyncIOEventKind kind;

    union
    {
        RnAsyncIOEventAccept  accept;
        RnAsyncIOEventConnect connect;
    };
}
RnAsyncIOEvent;

RnAsyncIOEvent
rnAsyncIOEventAccept(RnSocketTCP* socket);

RnAsyncIOEvent
rnAsyncIOEventConnect(b32 status);

#endif // RN_WIN32_ASYNCIO_EVENT_H
