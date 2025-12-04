#ifndef RN_WIN32_ASYNCIO_QUEUE_C
#define RN_WIN32_ASYNCIO_QUEUE_C

#include "./queue.h"

extern LPFN_CONNECTEX            connectEx;
extern LPFN_ACCEPTEX             acceptEx;
extern LPFN_GETACCEPTEXSOCKADDRS getAcceptExSockAddrs;

static b32
rnWin32AsyncIOQueueBindSocketTCP(RnWin32AsyncIOQueue* self, RnWin32SocketTCP* value)
{
    if (self == 0 || value == 0 || value->storage.ss_family == 0)
        return 0;

    HANDLE handle = ((HANDLE) value->handle);

    if (CreateIoCompletionPort(handle, self->handle, 0, 0) == 0)
        return 0;

    return 1;
}

static RnWin32AsyncIOTask*
rnWin32AsyncIOQueueRemoveTaskByOverlapped(RnWin32AsyncIOQueue* self, OVERLAPPED* overlap)
{
    if (self == 0 || overlap == 0) return 0;

    for (RnWin32AsyncIOTask* task = self->head; task != 0; task = task->next) {
        if (&task->overlap == overlap) {
            if (task->prev)
                task->prev->next = task->next;
            else
                self->head = task->next;

            if (task->next)
                task->next->prev = task->prev;
            else
                self->tail = task->prev;

            task->prev = task->next = NULL;

            return task;
        }
    }

    return 0;
}

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
rnWin32AsyncIOQueueSubmit(RnWin32AsyncIOQueue* queue, RnMemoryArena* arena, RnWin32AsyncIOTask* task)
{
    if (queue == 0 || task == 0) return 0;

    switch (task->kind) {
        case RnAsyncIOEvent_Accept: {
            // TODO(gio): Work on an explicit "interest group"

            RnWin32SocketTCP* listener = task->accept.listener;
            RnWin32SocketTCP* socket   = task->accept.socket;
            u8*               buffer   = task->accept.buffer;
            ssize             size     = task->accept.size;

            rnWin32AsyncIOQueueBindSocketTCP(queue, listener);

            if (rnWin32AsyncIOQueueBindSocketTCP(queue, socket) == 0)
                return 0;

            DWORD bytes = 0;

            BOOL status = acceptEx(listener->handle, socket->handle, buffer,
                0, size, size, &bytes, &task->overlap);

            if (status == SOCKET_ERROR && WSAGetLastError() != ERROR_IO_PENDING)
                return 0;
        } break;

        default: return 0;
    }

    // TODO(gio): Make this a binary tree to speed up search time

    if (queue->head != 0 && queue->tail != 0) {
        queue->tail->next = task;
        task->prev        = queue->tail;
    } else
        queue->head = queue->tail = task;

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

    BOOL status = GetQueuedCompletionStatus(self->handle, &bytes, &key, &overlap, time);

    if (status == 0) {
        if (GetLastError() != WAIT_TIMEOUT) {
            if (event != 0)
                *event = rnAsyncIOEventError();

            return 1;
        }

        return 0;
    }

    RnWin32AsyncIOTask* task = rnWin32AsyncIOQueueRemoveTaskByOverlapped(self, overlap);

    switch (task->kind) {
        case RnAsyncIOEvent_Accept: {
            RnSockAddrStorage localAddr = {0};
            INT               localSize = task->accept.size;
            RnSockAddrStorage otherAddr = {0};
            INT               otherSize = task->accept.size;

            setsockopt(task->accept.socket->handle, SOL_SOCKET, SO_UPDATE_ACCEPT_CONTEXT,
                ((char*) &task->accept.listener->handle), sizeof(task->accept.listener->handle));

            getAcceptExSockAddrs(task->accept.buffer, 0, task->accept.size, task->accept.size,
                ((RnSockAddr**) &localAddr), &localSize, ((RnSockAddr**) &otherAddr), &otherSize);

            event->kind          = RnAsyncIOEvent_Accept;
            event->accept.socket = task->accept.socket;

            ((RnWin32SocketTCP*) event->accept.socket)->storage =
                otherAddr;
        } break;

        default: return 0;
    }

    return 1;
}

#endif // RN_WIN32_ASYNCIO_QUEUE_C
