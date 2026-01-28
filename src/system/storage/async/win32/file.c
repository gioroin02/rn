#ifndef P_SYSTEM_WIN32_STORAGE_ASYNC_FILE_C
#define P_SYSTEM_WIN32_STORAGE_ASYNC_FILE_C

#include "file.h"

static B32 pWin32AsyncIoQueueBindFile(PWin32AsyncIoQueue* queue, PWin32File* file)
{
    HANDLE handle = file->handle;
    HANDLE result = CreateIoCompletionPort(handle, queue->handle, 0, 0);

    return result != NULL ? 1 : 0;
}

static B32 pWin32FileWriteBegin(PWin32FileWrite* task, PWin32AsyncIoQueue* queue)
{
    PWin32File* self = task->self;
    I8*         pntr = ((I8*) task->pntr) + task->start;
    Int         size = task->stop - task->start;

    pWin32AsyncIoQueueBindFile(queue, self);

    BOOL status = WriteFile(self->handle, pntr, size, NULL, &task->overlap);

    if (status == 0 && GetLastError() != ERROR_IO_PENDING)
        return 0;

    return 1;
}

static PAsyncIoEventKind pWin32FileWriteEnd(PWin32FileWrite* task, Int bytes, PMemoryArena* arena, PAsyncIoEvent** event)
{
    PWin32File* self  = task->self;
    U8*         pntr  = task->pntr;
    Int         start = task->start;
    Int         stop  = task->stop;

    PFileEvent* result = pMemoryArenaReserveOneOf(arena, PFileEvent);

    if (result != NULL) {
        *result = pFileEventWrite((PFile*) self,
            pntr, start, stop, bytes, task->ctxt);

        if (event != NULL) *event = (PAsyncIoEvent*) result;

        return PAsyncIoEvent_File;
    }

    return PAsyncIoEvent_None;
}

static B32 pWin32FileReadBegin(PWin32FileRead* task, PWin32AsyncIoQueue* queue)
{
    PWin32File* self = task->self;
    I8*         pntr = ((I8*) task->pntr) + task->start;
    Int         size = task->stop - task->start;

    pWin32AsyncIoQueueBindFile(queue, self);

    BOOL status = ReadFile(self->handle, pntr, size, NULL, &task->overlap);

    if (status == 0 && GetLastError() != ERROR_IO_PENDING)
        return 0;

    return 1;
}

static PAsyncIoEventKind pWin32FileReadEnd(PWin32FileRead* task, Int bytes, PMemoryArena* arena, PAsyncIoEvent** event)
{
    PWin32File* self  = task->self;
    U8*         pntr  = task->pntr;
    Int         start = task->start;
    Int         stop  = task->stop;

    PFileEvent* result = pMemoryArenaReserveOneOf(arena, PFileEvent);

    if (result != NULL) {
        *result = pFileEventRead((PFile*) self,
            pntr, start, stop, bytes, task->ctxt);

        if (event != NULL) *event = (PAsyncIoEvent*) result;

        return PAsyncIoEvent_File;
    }

    return PAsyncIoEvent_None;
}

B32 pWin32FileWriteAsync(PWin32File* self, U8* pntr, Int start, Int stop, PWin32AsyncIoQueue* queue, void* ctxt)
{
    PWin32FileWrite* result =
        pMemoryPoolReserveOneOf(&queue->pool, PWin32FileWrite);

    if (result != NULL) {
        result->self      = self;
        result->pntr      = pntr;
        result->start     = start;
        result->stop      = stop;
        result->ctxt      = ctxt;
        result->overlap   = (OVERLAPPED) {0};
        result->callback  = pWin32FileWriteEnd;
        result->list_next = NULL;

        if (pWin32FileWriteBegin(result, queue) != 0)
            return pWin32AsyncIoQueueSubmit(queue, (PWin32AsyncIoTask*) result);

        pMemoryPoolRelease(&queue->pool, result);
    }

    return 0;
}

B32 pWin32FileReadAsync(PWin32File* self, U8* pntr, Int start, Int stop, PWin32AsyncIoQueue* queue, void* ctxt)
{
    PWin32FileRead* result =
        pMemoryPoolReserveOneOf(&queue->pool, PWin32FileRead);

    if (result != NULL) {
        result->self      = self;
        result->pntr      = pntr;
        result->start     = start;
        result->stop      = stop;
        result->ctxt      = ctxt;
        result->overlap   = (OVERLAPPED) {0};
        result->callback  = pWin32FileReadEnd;
        result->list_next = NULL;

        if (pWin32FileReadBegin(result, queue) != 0)
            return pWin32AsyncIoQueueSubmit(queue, (PWin32AsyncIoTask*) result);

        pMemoryPoolRelease(&queue->pool, result);
    }

    return 0;
}

#endif
