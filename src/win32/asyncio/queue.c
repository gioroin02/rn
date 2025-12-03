#ifndef RN_WIN32_ASYNCIO_QUEUE_C
#define RN_WIN32_ASYNCIO_QUEUE_C

#include "./queue.h"

#include <stdio.h>

extern LPFN_CONNECTEX            connectEx;
extern LPFN_ACCEPTEX             acceptEx;
extern LPFN_GETACCEPTEXSOCKADDRS getAcceptExSockAddrs;

RnWin32AsyncIOQueue*
rnWin32AsyncIOQueueReserve(RnMemoryArena* arena)
{
    return rnMemoryArenaReserveOneOf(arena, RnWin32AsyncIOQueue);
}

b32
rnWin32AsyncIOQueueCreate(RnWin32AsyncIOQueue* self)
{
    if (self == 0) return 0;

    HANDLE handle = CreateIoCompletionPort(
        INVALID_HANDLE_VALUE, 0, 0, 0);

    if (handle == 0) return 0;

    self->handle = handle;

    return 1;
}

void
rnWin32AsyncIOQueueDestroy(RnWin32AsyncIOQueue* self)
{
    if (self == 0) return;

    if (self->handle != 0)
        CloseHandle(self->handle);

    *self = (RnWin32AsyncIOQueue) {0};
}

b32
rnWin32AsyncIOQueueBindSocketTCP(RnWin32AsyncIOQueue* self, RnWin32SocketTCP* value)
{
    if (self == 0 || value == 0 || value->storage.ss_family == 0)
        return 0;

    if (value->handle == INVALID_SOCKET) return 0;

    HANDLE handle = ((HANDLE) value->handle);

    if (CreateIoCompletionPort(handle, self->handle, 0, 0) == 0)
        return 0;

    return 1;
}

b32
rnWin32SocketTCPAcceptAsync(RnWin32SocketTCP* self, RnWin32SocketTCP* value, RnMemoryArena* arena, RnWin32AsyncIOQueue* queue)
{
    ssize size = 0;

    if (self == 0 || value == 0 || queue == 0) return 0;

    if (self->storage.ss_family == AF_INET)  size = sizeof(RnSockAddrIn4) + 16;
    if (self->storage.ss_family == AF_INET6) size = sizeof(RnSockAddrIn6) + 16;

    if (size == 0 || rnWin32AsyncIOQueueBindSocketTCP(queue, value) == 0) return 0;

    RnWin32AsyncIOTask* task = rnMemoryArenaReserveOneOf(arena, RnWin32AsyncIOTask);

    if (task == 0) return 0;

    task->kind         = RnAsyncIOEvent_Accept;
    task->socket       = self;
    task->overlap      = (OVERLAPPED) {.hEvent = (HANDLE) task};
    task->acceptSocket = value;
    task->acceptBuffer = rnMemoryArenaReserveManyOf(arena, u8, size * 2);
    task->acceptSize   = size;

    if (queue->head != 0 && queue->tail != 0) {
        queue->tail->next = task;
        task->prev        = queue->tail;
    } else
        queue->head = queue->tail = task;

    DWORD bytes = 0;

    BOOL status = acceptEx(task->socket->handle, task->acceptSocket->handle,
        task->acceptBuffer, 0, size, size, &bytes, &task->overlap);

    if (status == 0 && WSAGetLastError() != ERROR_IO_PENDING)
        return 0;

    return 1;
}

b32
rnWin32AsyncIOQueuePoll(RnWin32AsyncIOQueue* self, RnAsyncIOEvent* event, ssize timeout)
{
    DWORD time = timeout >= 0 ? timeout : INFINITE;

    if (self == 0) return 0;

    DWORD       bytes   = 0;
    ULONG_PTR   key     = 0;
    OVERLAPPED* overlap = 0;

    BOOL status = GetQueuedCompletionStatus(self->handle,
        &bytes, &key, &overlap, time);

    if (status == 0) {
        if (GetLastError() != WAIT_TIMEOUT) {
            if (event != 0)
                *event = rnAsyncIOEventError();

            return 1;
        }

        return 0;
    }

    printf("Task found! %u\n", status);

    RnWin32AsyncIOTask* task = ((RnWin32AsyncIOTask*) overlap->hEvent);

    if (task->prev != 0)
        task->prev->next = task->next;
    else
        self->head = task->next;

    if (task->next != 0)
        task->next->prev = task->prev;
    else
        self->tail = task->prev;

    switch (task->kind) {
        case RnAsyncIOEvent_Accept: {
            setsockopt(task->acceptSocket->handle, SOL_SOCKET,
                SO_UPDATE_ACCEPT_CONTEXT, ((char*) &task->socket->handle), sizeof(SOCKET));

            RnSockAddrStorage localAddr  = {0};
            INT               localSize  = task->acceptSize;
            RnSockAddrStorage otherAddr = {0};
            INT               otherSize = task->acceptSize;

            getAcceptExSockAddrs(task->acceptBuffer, 0, task->acceptSize, task->acceptSize,
                ((RnSockAddr**) &localAddr), &localSize, ((RnSockAddr**) &otherAddr), &otherSize);

            event->kind   = RnAsyncIOEvent_Accept;
            event->socket = task->acceptSocket;

            memcpy(&((RnWin32SocketTCP*) event->socket)->storage,
                &otherAddr, otherSize);
        } break;

        default: break;
    }

    return 1;
}

#endif // RN_WIN32_ASYNCIO_QUEUE_C
