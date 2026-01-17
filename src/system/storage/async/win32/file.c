#ifndef P_SYSTEM_WIN32_STORAGE_ASYNC_FILE_C
#define P_SYSTEM_WIN32_STORAGE_ASYNC_FILE_C

#include "file.h"

static Bool pWin32AsyncIoQueueBindFile(PWin32AsyncIoQueue* queue, PWin32File* file)
{
    HANDLE handle = file->handle;
    HANDLE result = CreateIoCompletionPort(handle, queue->handle, 0, 0);

    return result != NULL ? 1 : 0;
}

static Bool pWin32FileWriteBegin(PWin32FileWrite* task, PWin32AsyncIoQueue* queue)
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

static void pWin32FileWriteEnd(PWin32FileWrite* task, Int bytes)
{
    PWin32File* self  = task->self;
    U8*         pntr  = task->pntr;
    Int         start = task->start;
    Int         stop  = task->stop;

    if (task->pntr_proc != NULL) {
        ((PFileWriteProc*) task->pntr_proc)(task->pntr_ctxt,
            (PFile*) self, pntr, start, stop, bytes);
    }
}

static Bool pWin32FileReadBegin(PWin32FileRead* task, PWin32AsyncIoQueue* queue)
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

static void pWin32FileReadEnd(PWin32FileRead* task, Int bytes)
{
    PWin32File* self  = task->self;
    U8*         pntr  = task->pntr;
    Int         start = task->start;
    Int         stop  = task->stop;

    if (task->pntr_proc != NULL) {
        ((PFileReadProc*) task->pntr_proc)(task->pntr_ctxt,
            (PFile*) self, pntr, start, stop, bytes);
    }
}

Bool pWin32FileWriteAsync(PWin32File* self, U8* pntr, Int start, Int stop, PWin32AsyncIoQueue* queue, void* ctxt, void* proc)
{
    PWin32FileWrite* result =
        pMemoryPoolReserveOneOf(&queue->pool, PWin32FileWrite);

    if (result != NULL) {
        pMemorySet(&result->overlap, sizeof result->overlap, 0x00);

        result->self      = self;
        result->pntr      = pntr;
        result->start     = start;
        result->stop      = stop;
        result->pntr_ctxt = ctxt;
        result->pntr_proc = proc;
        result->callback  = pWin32FileWriteEnd;
        result->list_next = NULL;

        if (pWin32FileWriteBegin(result, queue) != 0)
            return pWin32AsyncIoQueueSubmit(queue, (PWin32AsyncIoTask*) result);

        pMemoryPoolRelease(&queue->pool, result);
    }

    return 0;
}

Bool pWin32FileReadAsync(PWin32File* self, U8* pntr, Int start, Int stop, PWin32AsyncIoQueue* queue, void* ctxt, void* proc)
{
    PWin32FileRead* result =
        pMemoryPoolReserveOneOf(&queue->pool, PWin32FileRead);

    if (result != NULL) {
        pMemorySet(&result->overlap, sizeof result->overlap, 0x00);

        result->self      = self;
        result->pntr      = pntr;
        result->start     = start;
        result->stop      = stop;
        result->pntr_ctxt = ctxt;
        result->pntr_proc = proc;
        result->callback  = pWin32FileReadEnd;
        result->list_next = NULL;

        if (pWin32FileReadBegin(result, queue) != 0)
            return pWin32AsyncIoQueueSubmit(queue, (PWin32AsyncIoTask*) result);

        pMemoryPoolRelease(&queue->pool, result);
    }

    return 0;
}

#endif // P_SYSTEM_WIN32_STORAGE_ASYNC_FILE_C
