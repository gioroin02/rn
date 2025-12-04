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

#endif // RN_SYSTEM_ASYNCIO_EVENT_C
