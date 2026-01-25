#ifndef P_SYSTEM_LINUX_ASYNCIO_QUEUE_C
#define P_SYSTEM_LINUX_ASYNCIO_QUEUE_C

#include "queue.h"

static void pLinuxAsyncIoQueueInsertBack(PLinuxAsyncIoQueue* self, PLinuxAsyncIoTask* value)
{
    if (self->list_front != NULL)
        self->list_back->list_next = value;
    else
        self->list_front = value;

    self->list_back = value;
}

static PLinuxAsyncIoTask* pLinuxAsyncIoQueueRemoveFront(PLinuxAsyncIoQueue* self)
{
    PLinuxAsyncIoTask* result = self->list_front;

    if (result == NULL) return result;

    self->list_front = result->list_next;

    if (self->list_front == NULL)
        self->list_back = NULL;

    return result;
}

static PLinuxAsyncIoTask* pLinuxAsyncIoQueueRemove(PLinuxAsyncIoQueue* self, PLinuxAsyncIoTask* prev)
{
    if (prev == NULL)
        return pLinuxAsyncIoQueueRemoveFront(self);

    PLinuxAsyncIoTask* result = prev->list_next;

    if (result == NULL) return NULL;

    prev->list_next = result->list_next;

    return result;
}

static PLinuxAsyncIoTask* pLinuxAsyncIoQueueRemoveByAddress(PLinuxAsyncIoQueue* self, void* address)
{
    PLinuxAsyncIoTask* prev = NULL;
    PLinuxAsyncIoTask* task = self->list_front;

    while (task != 0) {
        if (task == address)
            return pLinuxAsyncIoQueueRemove(self, prev);

        prev = task;
        task = task->list_next;
    }

    return NULL;
}

PLinuxAsyncIoQueue* pLinuxAsyncIoQueueReserve(PMemoryArena* arena)
{
    return pMemoryArenaReserveOneOf(arena, PLinuxAsyncIoQueue);
}

B32 pLinuxAsyncIoQueueCreate(PLinuxAsyncIoQueue* self, PMemoryPool pool)
{
    pMemorySet(self, sizeof *self, 0xAB);

    int handle = epoll_create1(EPOLL_CLOEXEC);

    if (handle != -1) {
        self->handle     = handle;
        self->pool       = pool;
        self->list_front = NULL;
        self->list_back  = NULL;

        return 1;
    }

    return 0;
}

void pLinuxAsyncIoQueueDestroy(PLinuxAsyncIoQueue* self)
{
    if (self->handle != -1)
        close(self->handle);

    pMemorySet(self, sizeof *self, 0xAB);
}

PAsyncIoEventKind pLinuxAsyncIoQueuePollEvent(PLinuxAsyncIoQueue* self, Int timeout, PMemoryArena* arena, PAsyncIoEvent** event)
{
    Int time = timeout >= 0 ? timeout : -1;

    PAsyncIoEventKind result = PAsyncIoEvent_None;
    PEpollEvent       notif;

    int status = epoll_wait(self->handle, &notif, 1, time);

    if (status <= 0) return result;

    PLinuxAsyncIoTask* value = pLinuxAsyncIoQueueRemoveByAddress(self, notif.data.ptr);

    if (value != NULL && value->callback != NULL)
        result = ((PLinuxAsyncIoProc*) value->callback)(value, arena, event);

    pMemoryPoolRelease(&self->pool, value);

    return result;
}

B32 pLinuxAsyncIoQueueSubmit(PLinuxAsyncIoQueue* self, PLinuxAsyncIoTask* value)
{
    if (value == NULL) return 0;

    pLinuxAsyncIoQueueInsertBack(self, value);

    return 1;
}

#endif
