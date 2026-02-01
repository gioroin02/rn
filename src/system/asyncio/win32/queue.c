#ifndef RHO_SYSTEM_ASYNCIO_WIN32_QUEUE_C
#define RHO_SYSTEM_ASYNCIO_WIN32_QUEUE_C

#include "queue.h"

static void rho_win32_io_queue_insert_back(RWin32IoQueue* self, RWin32IoTask* value)
{
    if (self->list_front != NULL)
        self->list_back->list_next = value;
    else
        self->list_front = value;

    self->list_back = value;
}

static RWin32IoTask* rho_win32_io_queue_remove_front(RWin32IoQueue* self)
{
    RWin32IoTask* result = self->list_front;

    if (result == NULL) return result;

    self->list_front = result->list_next;

    if (self->list_front == NULL)
        self->list_back = NULL;

    return result;
}

static RWin32IoTask* rho_win32_io_queue_remove(RWin32IoQueue* self, RWin32IoTask* prev)
{
    if (prev == NULL)
        return rho_win32_io_queue_remove_front(self);

    RWin32IoTask* result = prev->list_next;

    if (result == NULL) return NULL;

    prev->list_next = result->list_next;

    return result;
}

static RWin32IoTask* rho_win32_io_queue_remove_by_overlap(RWin32IoQueue* self, OVERLAPPED* overlap)
{
    RWin32IoTask* prev = NULL;
    RWin32IoTask* task = self->list_front;

    while (task != 0) {
        if (&task->overlap == overlap)
            return rho_win32_io_queue_remove(self, prev);

        prev = task;
        task = task->list_next;
    }

    return NULL;
}

RWin32IoQueue* rho_win32_io_queue_reserve(RMemoryArena* arena)
{
    return rho_memory_arena_reserve_of(arena, RWin32IoQueue, 1);
}

RBool32 rho_win32_io_queue_create(RWin32IoQueue* self, RMemoryPool pool)
{
    rho_memory_set(self, sizeof *self, 0xAB);

    self->handle     = NULL;
    self->pool       = rho_memory_pool_make(NULL, 0, 0);
    self->list_front = NULL;
    self->list_back  = NULL;

    HANDLE handle = CreateIoCompletionPort(
        INVALID_HANDLE_VALUE, NULL, 0, 0);

    if (handle == NULL) return 0;

    self->handle = handle;
    self->pool   = pool;

    return 1;
}

void rho_win32_io_queue_destroy(RWin32IoQueue* self)
{
    if (self->handle != NULL)
        CloseHandle(self->handle);

    rho_memory_set(self, sizeof *self, 0xAB);
}

RIoEvent* rho_win32_io_queue_poll_event(RWin32IoQueue* self, RInt timeout, RMemoryArena* arena)
{
    RInt time = timeout >= 0 ? timeout : INFINITE;

    // Note(Gio): This is useless but must not be null.
    ULONG_PTR complet = 0;

    RIoEvent*   result  = NULL;
    RInt        bytes   = 0;
    OVERLAPPED* overlap = NULL;

    BOOL status = GetQueuedCompletionStatus(self->handle, (DWORD*) &bytes,
        &complet, &overlap, time);

    if (status == 0 && GetLastError() != WAIT_TIMEOUT) return result;

    RWin32IoTask* value = rho_win32_io_queue_remove_by_overlap(self, overlap);

    if (value != NULL && value->callback != NULL)
        result = ((RWin32IoProc*) value->callback)(value, bytes, arena);

    rho_memory_pool_release(&self->pool, value);

    return result;
}

RBool32 rho_win32_io_queue_submit(RWin32IoQueue* self, RWin32IoTask* value)
{
    if (value == NULL) return 0;

    rho_win32_io_queue_insert_back(self, value);

    return 1;
}

#endif
