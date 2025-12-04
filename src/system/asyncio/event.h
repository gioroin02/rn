#ifndef RN_WIN32_ASYNCIO_EVENT_H
#define RN_WIN32_ASYNCIO_EVENT_H

#include "./import.h"

#define rnAsyncIOEventError() \
    ((RnAsyncIOEvent) {.kind = RnAsyncIOEvent_Error})

typedef enum RnAsyncIOEventKind
{
    RnAsyncIOEvent_None,

    RnAsyncIOEvent_Error,

    RnAsyncIOEvent_Connect,
    RnAsyncIOEvent_Accept,
}
RnAsyncIOEventKind;

typedef struct RnAsyncIOEventAccept
{
    RnSocketTCP* socket;
}
RnAsyncIOEventAccept;

typedef struct RnAsyncIOEvent
{
    RnAsyncIOEventKind kind;

    union
    {
        RnAsyncIOEventAccept accept;
    };
}
RnAsyncIOEvent;

RnAsyncIOEvent
rnAsyncIOEventAccept(RnSocketTCP* socket);

#endif // RN_WIN32_ASYNCIO_EVENT_H
