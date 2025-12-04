#ifndef RN_WIN32_ASYNCIO_QUEUE_H
#define RN_WIN32_ASYNCIO_QUEUE_H

#include "./import.h"

#pragma comment(lib, "ws2_32.lib")

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <mswsock.h>

typedef struct RnWin32AsyncIOTask
{
    /* Inherits */
    OVERLAPPED overlap;

    RnAsyncIOEventKind kind;

    struct RnWin32AsyncIOTask* next;
    struct RnWin32AsyncIOTask* prev;

    RnWin32SocketTCP*  socket;
    RnWin32SocketTCP*  acceptSocket;
    u8*                acceptBuffer;
    ssize              acceptSize;

}
RnWin32AsyncIOTask;

typedef struct RnWin32AsyncIOQueue
{
    HANDLE handle;

    RnWin32AsyncIOTask* head;
    RnWin32AsyncIOTask* tail;
}
RnWin32AsyncIOQueue;

RnWin32AsyncIOQueue*
rnWin32AsyncIOQueueReserve(RnMemoryArena* arena);

b32
rnWin32AsyncIOQueueCreate(RnWin32AsyncIOQueue* self);

void
rnWin32AsyncIOQueueDestroy(RnWin32AsyncIOQueue* self);

b32
rnWin32AsyncIOQueueBindSocketTCP(RnWin32AsyncIOQueue* self, RnWin32SocketTCP* handle);

b32
rnWin32SocketTCPAcceptAsync(RnWin32SocketTCP* self, RnWin32SocketTCP* value, RnMemoryArena* arena, RnWin32AsyncIOQueue* queue);

b32
rnWin32AsyncIOQueuePoll(RnWin32AsyncIOQueue* self, RnAsyncIOEvent* event, ssize timeout);

#endif // RN_WIN32_ASYNCIO_QUEUE_H
