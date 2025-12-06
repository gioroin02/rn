#ifndef RN_SYSTEM_ASYNCIO_EVENT_C
#define RN_SYSTEM_ASYNCIO_EVENT_C

#include "./event.h"

RnAsyncIOEvent
rnAsyncIOEventAccept(RnSocketTCP* socket, RnSocketTCP* value)
{
    return (RnAsyncIOEvent) {
        .kind = RnAsyncIOEvent_Accept,

        .accept = {
            .socket = socket,
            .value  = value,
        },
    };
}

RnAsyncIOEvent
rnAsyncIOEventConnect(RnSocketTCP* socket, b32 status)
{
    return (RnAsyncIOEvent) {
        .kind = RnAsyncIOEvent_Connect,

        .connect = {
            .socket = socket,
            .status = status != 0 ? 1 : 0,
        },
    };
}

RnAsyncIOEvent
rnAsyncIOEventWrite(RnSocketTCP* socket, u8* buffer, ssize size, ssize count)
{
    return (RnAsyncIOEvent) {
        .kind = RnAsyncIOEvent_Write,

        .write = {
            .socket = socket,
            .buffer = buffer,
            .size   = size,
            .count  = count,
        },
    };
}

RnAsyncIOEvent
rnAsyncIOEventRead(RnSocketTCP* socket, u8* buffer, ssize size, ssize count)
{
    return (RnAsyncIOEvent) {
        .kind = RnAsyncIOEvent_Read,

        .read = {
            .socket = socket,
            .buffer = buffer,
            .size   = size,
            .count  = count,
        },
    };
}

RnAsyncIOEvent
rnAsyncIOEventClose(RnSocketTCP* socket)
{
    return (RnAsyncIOEvent) {
        .kind = RnAsyncIOEvent_Close,
    };
}

#endif // RN_SYSTEM_ASYNCIO_EVENT_C
