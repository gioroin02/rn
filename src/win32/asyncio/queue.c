#ifndef RN_WIN32_ASYNCIO_QUEUE_C
#define RN_WIN32_ASYNCIO_QUEUE_C

#include "./queue.h"

static b32
rnWin32AsyncIOTaskPrepare(RnWin32AsyncIOTask* self, RnWin32AsyncIOQueue* queue)
{
    if (self->procPrepare != 0)
        return ((RnWin32AsyncIOProcPrepare*) self->procPrepare)(self, queue);

    return 0;
}

static b32
rnWin32AsyncIOTaskComplete(RnWin32AsyncIOTask* self, ssize bytes)
{
    if (self->procComplete != 0)
        return ((RnWin32AsyncIOProcComplete*) self->procComplete)(self, bytes);

    return 0;
}

static void
rnWin32AsyncIOQueueInsertTask(RnWin32AsyncIOQueue* self, RnWin32AsyncIOTask* task)
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

            task->prev = task->next = 0;

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
rnWin32AsyncIOQueueSubmit(RnWin32AsyncIOQueue* self, RnWin32AsyncIOTask* task)
{
    if (self == 0 || task == 0) return 0;

    if (rnWin32AsyncIOTaskPrepare(task, self) == 0)
        return 0;

    rnWin32AsyncIOQueueInsertTask(self, task);

    return 1;
}

b32
rnWin32AsyncIOQueuePoll(RnWin32AsyncIOQueue* self, ssize timeout)
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
        RnWin32AsyncIOTask* task =
            rnWin32AsyncIOQueueRemoveTaskByOverlapped(self, overlap);

        if (task == 0 || rnWin32AsyncIOTaskComplete(task, bytes) == 0)
            return 0;
    }

    return 1;
}

#endif // RN_WIN32_ASYNCIO_QUEUE_C
