#ifndef PX_WIN32_ASYNCIO_QUEUE_C
#define PX_WIN32_ASYNCIO_QUEUE_C

#include "queue.h"

static b32
pxWin32AsyncIOTaskPrepare(PxWin32AsyncIOTask* self, PxWin32AsyncIOQueue* queue)
{
    if (self->procPrepare != 0)
        return ((PxWin32AsyncIOProcPrepare*) self->procPrepare)(self, queue);

    return 0;
}

static b32
pxWin32AsyncIOTaskComplete(PxWin32AsyncIOTask* self, ssize bytes)
{
    if (self->procComplete != 0)
        return ((PxWin32AsyncIOProcComplete*) self->procComplete)(self, bytes);

    return 0;
}

static void
pxWin32AsyncIOQueueInsertTask(PxWin32AsyncIOQueue* self, PxWin32AsyncIOTask* task)
{
    if (self->head == 0 && self->tail == 0) {
        self->head = task;
        self->tail = self->head;
    } else {
        if (self->head == self->tail) {
            self->tail = task;

            self->head->next = self->tail;
            self->tail->prev = self->head;
        } else {
            self->tail->next = task;
            task->prev       = self->tail;

            self->tail = task;
        }
    }
}

static PxWin32AsyncIOTask*
pxWin32AsyncIOQueueRemoveTaskByOverlapped(PxWin32AsyncIOQueue* self, OVERLAPPED* overlap)
{
    if (self == 0 || overlap == 0) return 0;

    for (PxWin32AsyncIOTask* task = self->head; task != 0; task = task->next) {
        if (&task->overlap == overlap) {
            if (task->prev)
                task->prev->next = task->next;
            else
                self->head = task->next;

            if (task->next)
                task->next->prev = task->prev;
            else
                self->tail = task->prev;

            task->prev = task->next = 0;

            return task;
        }
    }

    return 0;
}

PxWin32AsyncIOQueue*
pxWin32AsyncIOQueueReserve(PxMemoryArena* arena)
{
    return pxMemoryArenaReserveOneOf(arena, PxWin32AsyncIOQueue);
}

b32
pxWin32AsyncIOQueueCreate(PxWin32AsyncIOQueue* self)
{
    if (self == 0) return 0;

    HANDLE handle = CreateIoCompletionPort(
        INVALID_HANDLE_VALUE, 0, 0, 0);

    if (handle == 0) return 0;

    self->handle = handle;

    return 1;
}

void
pxWin32AsyncIOQueueDestroy(PxWin32AsyncIOQueue* self)
{
    if (self == 0) return;

    if (self->handle != 0)
        CloseHandle(self->handle);

    *self = (PxWin32AsyncIOQueue) {0};
}

b32
pxWin32AsyncIOQueueSubmit(PxWin32AsyncIOQueue* self, PxWin32AsyncIOTask* task)
{
    if (self == 0 || task == 0) return 0;

    if (pxWin32AsyncIOTaskPrepare(task, self) == 0)
        return 0;

    pxWin32AsyncIOQueueInsertTask(self, task);

    return 1;
}

b32
pxWin32AsyncIOQueuePoll(PxWin32AsyncIOQueue* self, ssize timeout)
{
    DWORD time = timeout >= 0 ? timeout : INFINITE;

    if (self == 0) return 0;

    DWORD       bytes   = 0;
    ULONG_PTR   key     = 0;
    OVERLAPPED* overlap = 0;

    BOOL status = GetQueuedCompletionStatus(self->handle,
        &bytes, &key, &overlap, time);

    if (status == 0 && GetLastError() != WAIT_TIMEOUT)
        return 0;

    if (status != 0) {
        PxWin32AsyncIOTask* task =
            pxWin32AsyncIOQueueRemoveTaskByOverlapped(self, overlap);

        if (task == 0 || pxWin32AsyncIOTaskComplete(task, bytes) == 0)
            return 0;
    }

    return 1;
}

#endif // PX_WIN32_ASYNCIO_QUEUE_C
