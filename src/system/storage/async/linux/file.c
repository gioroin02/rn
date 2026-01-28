#ifndef P_SYSTEM_LINUX_STORAGE_ASYNC_FILE_C
#define P_SYSTEM_LINUX_STORAGE_ASYNC_FILE_C

#include "file.h"

static B32 pLinuxAsyncIoQueueBindFile(PLinuxAsyncIoQueue* self, PLinuxFile* file, PLinuxAsyncIoTask* task)
{
    int handle = (int) file->handle;
    int queue  = (int) self->handle;

    PEpollEvent notif = {0};

    notif.events   = EPOLLIN | EPOLLOUT;
    notif.data.ptr = task;

    // TODO(Gio): check if could encounter EINTR.

    int status = epoll_ctl(queue, EPOLL_CTL_ADD, handle, &notif);

    if (status == -1 && errno == EEXIST)
        status = epoll_ctl(queue, EPOLL_CTL_MOD, handle, &notif);

    return status != -1 ? 1 : 0;
}

static B32 pLinuxFileWriteBegin(PLinuxFileWrite* task, PLinuxAsyncIoQueue* queue)
{
    PLinuxFile* self = task->self;

    pLinuxAsyncIoQueueBindFile(queue,
        self, (PLinuxAsyncIoTask*) task);

    return 1;
}

static PAsyncIoEventKind pLinuxFileWriteEnd(PLinuxFileWrite* task, PMemoryArena* arena, PAsyncIoEvent** event)
{
    PLinuxFile* self  = task->self;
    U8*         pntr  = task->pntr;
    Int         start = task->start;
    Int         stop  = task->stop;

    Int bytes = pLinuxFileWrite(self, pntr, start, stop);

    PFileEvent* result =
        pMemoryArenaReserveOneOf(arena, PFileEvent);

    if (result != NULL) {
        *result = pFileEventWrite((PFile*) self,
            pntr, start, stop, bytes, task->ctxt);

        if (event != NULL) *event = (PAsyncIoEvent*) result;

        return PAsyncIoEvent_Tcp;
    }

    return PAsyncIoEvent_None;
}

static B32 pLinuxFileReadBegin(PLinuxFileRead* task, PLinuxAsyncIoQueue* queue)
{
    PLinuxFile* self = task->self;

    pLinuxAsyncIoQueueBindFile(queue,
        self, (PLinuxAsyncIoTask*) task);

    return 1;
}

static PAsyncIoEventKind pLinuxFileReadEnd(PLinuxFileRead* task, PMemoryArena* arena, PAsyncIoEvent** event)
{
    PLinuxFile* self  = task->self;
    U8*         pntr  = task->pntr;
    Int         start = task->start;
    Int         stop  = task->stop;

    Int bytes = pLinuxFileRead(self, pntr, start, stop);

    PFileEvent* result =
        pMemoryArenaReserveOneOf(arena, PFileEvent);

    if (result != NULL) {
        *result = pFileEventRead((PFile*) self,
            pntr, start, stop, bytes, task->ctxt);

        if (event != NULL) *event = (PAsyncIoEvent*) result;

        return PAsyncIoEvent_Tcp;
    }

    return PAsyncIoEvent_None;
}

B32 pLinuxFileWriteAsync(PLinuxFile* self, U8* pntr, Int start, Int stop, PLinuxAsyncIoQueue* queue, void* ctxt)
{
    PLinuxFileWrite* result =
        pMemoryPoolReserveOneOf(&queue->pool, PLinuxFileWrite);

    if (result != NULL) {
        result->self      = self;
        result->pntr      = pntr;
        result->start     = start;
        result->stop      = stop;
        result->ctxt      = ctxt;
        result->callback  = pLinuxFileWriteEnd;
        result->list_next = NULL;

        if (pLinuxFileWriteBegin(result, queue) != 0)
            return pLinuxAsyncIoQueueSubmit(queue, (PLinuxAsyncIoTask*) result);

        pMemoryPoolRelease(&queue->pool, result);
    }

    return 0;
}

B32 pLinuxFileReadAsync(PLinuxFile* self, U8* pntr, Int start, Int stop, PLinuxAsyncIoQueue* queue, void* ctxt)
{
    PLinuxFileRead* result =
        pMemoryPoolReserveOneOf(&queue->pool, PLinuxFileRead);

    if (result != NULL) {
        result->self      = self;
        result->pntr      = pntr;
        result->start     = start;
        result->stop      = stop;
        result->ctxt      = ctxt;
        result->callback  = pLinuxFileReadEnd;
        result->list_next = NULL;

        if (pLinuxFileReadBegin(result, queue) != 0)
            return pLinuxAsyncIoQueueSubmit(queue, (PLinuxAsyncIoTask*) result);

        pMemoryPoolRelease(&queue->pool, result);
    }

    return 0;
}

#endif
