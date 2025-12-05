#ifndef RN_SYSTEM_ASYNCIO_EVENT_C
#define RN_SYSTEM_ASYNCIO_EVENT_C

#include "./event.h"

RnAsyncIOEvent
rnAsyncIOEventAccept(RnSocketTCP* socket)
{
    return (RnAsyncIOEvent) {
        .kind = RnAsyncIOEvent_Accept,

        .accept = {
            .socket = socket,
        },
    };
}

RnAsyncIOEvent
rnAsyncIOEventConnect(b32 status)
{
    return (RnAsyncIOEvent) {
        .kind = RnAsyncIOEvent_Connect,

        .connect = {
            .status = status != 0 ? 1 : 0,
        },
    };
}

#endif // RN_SYSTEM_ASYNCIO_EVENT_C
