#ifndef RHO_SYSTEM_ASYNCIO_LINUX_QUEUE_C
#define RHO_SYSTEM_ASYNCIO_LINUX_QUEUE_C

#include "queue.h"

static void rho_linux_io_queue_insert_back(RLinuxIoQueue* self, RLinuxIoTask* value)
{
    if (self->list_front != NULL)
        self->list_back->list_next = value;
    else
        self->list_front = value;

    self->list_back = value;
}

static RLinuxIoTask* rho_linux_io_queue_remove_front(RLinuxIoQueue* self)
{
    RLinuxIoTask* result = self->list_front;

    if (result == NULL) return result;

    self->list_front = result->list_next;

    if (self->list_front == NULL)
        self->list_back = NULL;

    return result;
}

static RLinuxIoTask* rho_linux_io_queue_remove(RLinuxIoQueue* self, RLinuxIoTask* prev)
{
    if (prev == NULL)
        return rho_linux_io_queue_remove_front(self);

    RLinuxIoTask* result = prev->list_next;

    if (result == NULL) return NULL;

    prev->list_next = result->list_next;

    return result;
}

static RLinuxIoTask* rho_linux_io_queue_remove_by_address(RLinuxIoQueue* self, void* address)
{
    RLinuxIoTask* prev = NULL;
    RLinuxIoTask* task = self->list_front;

    while (task != 0) {
        if (task == address)
            return rho_linux_io_queue_remove(self, prev);

        prev = task;
        task = task->list_next;
    }

    return NULL;
}

RLinuxIoQueue* rho_linux_io_queue_reserve(RMemoryArena* arena)
{
    return rho_memory_arena_reserve_of(arena, RLinuxIoQueue, 1);
}

RBool32 rho_linux_io_queue_create(RLinuxIoQueue* self, RMemoryPool pool)
{
    rho_memory_set(self, sizeof *self, 0xAB);

    self->handle     = -1;
    self->pool       = rho_memory_pool_make(NULL, 0, 0);
    self->list_front = NULL;
    self->list_back  = NULL;

    int handle = epoll_create1(EPOLL_CLOEXEC);

    if (handle == -1) return 0;

    self->handle = handle;
    self->pool   = pool;

    return 1;
}

void rho_linux_io_queue_destroy(RLinuxIoQueue* self)
{
    int status = 0;

    if (self->handle == -1) return;

    do {
        status = close(self->handle);
    }
    while (status == -1 && errno == EINTR);

    rho_memory_set(self, sizeof *self, 0xAB);
}

RIoEvent* rho_linux_io_queue_poll_event(RLinuxIoQueue* self, RInt timeout, RMemoryArena* arena)
{
    RInt time = timeout >= 0 ? timeout : -1;

    RLinuxEpollEvent notif  = {0};
    RIoEvent*        result = NULL;
    int              status = 0;

    do {
        status = epoll_wait(self->handle, &notif, 1, time);
    }
    while (status == -1 && errno == EINTR);

    if (status <= 0) return result;

    RLinuxIoTask* value = rho_linux_io_queue_remove_by_address(self, notif.data.ptr);

    if (value != NULL && value->callback != NULL)
        result = ((RLinuxIoProc*) value->callback)(value, arena);

    rho_memory_pool_release(&self->pool, value);

    return result;
}

RBool32 rho_linux_io_queue_submit(RLinuxIoQueue* self, RLinuxIoTask* value)
{
    if (value == NULL) return 0;

    rho_linux_io_queue_insert_back(self, value);

    return 1;
}

#endif
