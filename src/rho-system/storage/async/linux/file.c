#ifndef RHO_SYSTEM_LINUX_STORAGE_ASYNC_FILE_C
#define RHO_SYSTEM_LINUX_STORAGE_ASYNC_FILE_C

#include "file.h"

static RBool32 rLinuxIoQueueBindFile(RLinuxIoQueue* self, RLinuxFile* file, RLinuxIoTask* task)
{
    int handle = (int) file->handle;
    int queue  = (int) self->handle;

    RLinuxEpollEvent notif = {0};

    notif.events   = EPOLLIN | EPOLLOUT;
    notif.data.ptr = task;

    // TODO(Gio): check if could encounter EINTR.

    int status = epoll_ctl(queue, EPOLL_CTL_ADD, handle, &notif);

    if (status == -1 && errno == EEXIST)
        status = epoll_ctl(queue, EPOLL_CTL_MOD, handle, &notif);

    return status != -1 ? 1 : 0;
}

static RBool32 rho_linux_file_begin_write(RLinuxFileWrite* task, RLinuxIoQueue* queue)
{
    RLinuxFile* self = task->self;

    rLinuxIoQueueBindFile(queue,
        self, (RLinuxIoTask*) task);

    return 1;
}

static RIoEvent* rho_linux_file_end_write(RLinuxFileWrite* task, RMemoryArena* arena)
{
    RLinuxFile* self  = task->self;
    RUint8*     pntr  = task->pntr;
    RInt        start = task->start;
    RInt        stop  = task->stop;

    RInt bytes = rho_linux_file_write(self, pntr, start, stop);

    RFileEvent* result =
        rho_memory_arena_reserve_of(arena, RFileEvent, 1);

    if (result == NULL) return NULL;

    *result = rho_file_event_write(
        (RFile*) self, pntr, start, stop, bytes, task->ctxt);

    return (RIoEvent*) result;
}

static RBool32 rho_linux_file_begin_read(RLinuxFileRead* task, RLinuxIoQueue* queue)
{
    RLinuxFile* self = task->self;

    rLinuxIoQueueBindFile(queue,
        self, (RLinuxIoTask*) task);

    return 1;
}

static RIoEvent* rho_linux_file_end_read(RLinuxFileRead* task, RMemoryArena* arena)
{
    RLinuxFile* self  = task->self;
    RUint8*     pntr  = task->pntr;
    RInt        start = task->start;
    RInt        stop  = task->stop;

    RInt bytes = rho_linux_file_read(self, pntr, start, stop);

    RFileEvent* result =
        rho_memory_arena_reserve_of(arena, RFileEvent, 1);

    if (result == NULL) return NULL;

    *result = rho_file_event_read(
        (RFile*) self, pntr, start, stop, bytes, task->ctxt);

    return (RIoEvent*) result;
}

RBool32 rho_linux_file_async_write(RLinuxFile* self, RUint8* pntr, RInt start, RInt stop, RLinuxIoQueue* queue, void* ctxt)
{
    RLinuxFileWrite* result = rho_memory_pool_reserve_of(
        &queue->pool, RLinuxFileWrite, 1);

    if (result != NULL) {
        result->self      = self;
        result->pntr      = pntr;
        result->start     = start;
        result->stop      = stop;
        result->ctxt      = ctxt;
        result->callback  = rho_linux_file_end_write;
        result->list_next = NULL;

        if (rho_linux_file_begin_write(result, queue) != 0)
            return rho_linux_io_queue_submit(queue, (RLinuxIoTask*) result);

        rho_memory_pool_release(&queue->pool, result);
    }

    return 0;
}

RBool32 rho_linux_file_async_read(RLinuxFile* self, RUint8* pntr, RInt start, RInt stop, RLinuxIoQueue* queue, void* ctxt)
{
    RLinuxFileRead* result = rho_memory_pool_reserve_of(
        &queue->pool, RLinuxFileRead, 1);

    if (result != NULL) {
        result->self      = self;
        result->pntr      = pntr;
        result->start     = start;
        result->stop      = stop;
        result->ctxt      = ctxt;
        result->callback  = rho_linux_file_end_read;
        result->list_next = NULL;

        if (rho_linux_file_begin_read(result, queue) != 0)
            return rho_linux_io_queue_submit(queue, (RLinuxIoTask*) result);

        rho_memory_pool_release(&queue->pool, result);
    }

    return 0;
}

#endif
