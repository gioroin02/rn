#ifndef P_SYSTEM_WIN32_ASYNCIO_QUEUE_C
#define P_SYSTEM_WIN32_ASYNCIO_QUEUE_C

#include "queue.h"

static void pWin32AsyncIoQueueInsertBack(PWin32AsyncIoQueue* self, PWin32AsyncIoTask* value)
{
    if (self->list_front != NULL)
        self->list_back->list_next = value;
    else
        self->list_front = value;

    self->list_back = value;
}

static PWin32AsyncIoTask* pWin32AsyncIoQueueRemoveFront(PWin32AsyncIoQueue* self)
{
    PWin32AsyncIoTask* result = self->list_front;

    if (result == NULL) return result;

    self->list_front = result->list_next;

    if (self->list_front == NULL)
        self->list_back = NULL;

    return result;
}

static PWin32AsyncIoTask* pWin32AsyncIoQueueRemove(PWin32AsyncIoQueue* self, PWin32AsyncIoTask* prev)
{
    if (prev == NULL)
        return pWin32AsyncIoQueueRemoveFront(self);

    PWin32AsyncIoTask* result = prev->list_next;

    if (result == NULL) return NULL;

    prev->list_next = result->list_next;

    return result;
}

static PWin32AsyncIoTask* pWin32AsyncIoQueueRemoveByOverlapped(PWin32AsyncIoQueue* self, OVERLAPPED* overlap)
{
    PWin32AsyncIoTask* prev = NULL;
    PWin32AsyncIoTask* task = self->list_front;

    while (task != 0) {
        if (&task->overlap == overlap)
            return pWin32AsyncIoQueueRemove(self, prev);

        prev = task;
        task = task->list_next;
    }

    return NULL;
}

PWin32AsyncIoQueue* pWin32AsyncIoQueueReserve(PMemoryArena* arena)
{
    return pMemoryArenaReserveOneOf(arena, PWin32AsyncIoQueue);
}

B32 pWin32AsyncIoQueueCreate(PWin32AsyncIoQueue* self, PMemoryPool pool)
{
    pMemorySet(self, sizeof *self, 0xAB);

    self->handle     = NULL;
    self->pool       = pMemoryPoolMake(NULL, 0, 0);
    self->list_front = NULL;
    self->list_back  = NULL;

    HANDLE handle = CreateIoCompletionPort(
        INVALID_HANDLE_VALUE, NULL, 0, 0);

    if (handle == NULL) return 0;

    self->handle = handle;
    self->pool   = pool;

    return 1;
}

void pWin32AsyncIoQueueDestroy(PWin32AsyncIoQueue* self)
{
    if (self->handle != NULL)
        CloseHandle(self->handle);

    pMemorySet(self, sizeof *self, 0xAB);
}

PAsyncIoEventKind pWin32AsyncIoQueuePollEvent(PWin32AsyncIoQueue* self, Int timeout, PMemoryArena* arena, PAsyncIoEvent** event)
{
    Int time = timeout >= 0 ? timeout : INFINITE;

    PAsyncIoEventKind result  = PAsyncIoEvent_None;
    Int               bytes   = 0;
    OVERLAPPED*       overlap = NULL;

    // Note(Gio): This is useless but must not be null.
    ULONG_PTR complet = 0;

    BOOL status = GetQueuedCompletionStatus(self->handle,
        (DWORD*) &bytes, &complet, &overlap, time);

    if (status == 0 && GetLastError() != WAIT_TIMEOUT) return result;

    PWin32AsyncIoTask* value = pWin32AsyncIoQueueRemoveByOverlapped(self, overlap);

    if (value != NULL && value->callback != NULL)
        result = ((PWin32AsyncIoProc*) value->callback)(value, bytes, arena, event);

    pMemoryPoolRelease(&self->pool, value);

    return result;
}

B32 pWin32AsyncIoQueueSubmit(PWin32AsyncIoQueue* self, PWin32AsyncIoTask* value)
{
    if (value == NULL) return 0;

    pWin32AsyncIoQueueInsertBack(self, value);

    return 1;
}

#endif
