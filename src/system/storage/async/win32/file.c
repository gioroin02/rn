#ifndef RHO_SYSTEM_WIN32_STORAGE_ASYNC_FILE_C
#define RHO_SYSTEM_WIN32_STORAGE_ASYNC_FILE_C

#include "file.h"

static RBool32 rho_win32_io_queue_bind_file(RWin32IoQueue* self, RWin32File* file)
{
    HANDLE handle = file->handle;
    HANDLE result = CreateIoCompletionPort(handle, self->handle, 0, 0);

    return result != NULL ? 1 : 0;
}

static RBool32 rho_win32_file_begin_write(RWin32FileWrite* task, RWin32IoQueue* queue)
{
    RWin32File* self  = task->self;
    RChar8*     pntr  = ((RChar8*) task->pntr) + task->start;
    RInt        size  = task->stop - task->start;
    RInt        bytes = 0;

    rho_win32_io_queue_bind_file(queue, self);

    DWORD offset_low  = 0;
    DWORD offset_high = 0;

    offset_low = SetFilePointer(self->handle,
        0, (LONG*) &offset_high, FILE_CURRENT);

    task->overlap.Offset     = offset_low;
    task->overlap.OffsetHigh = offset_high;

    BOOL status = WriteFile(self->handle, pntr,
        size, (DWORD*) &bytes, &task->overlap);

    if (status != 0) {
        PostQueuedCompletionStatus(queue->handle,
            bytes, 0, &task->overlap);

        return 1;
    }

    if (status == 0 && GetLastError() != ERROR_IO_PENDING)
        return 0;

    return 1;
}

static RIoEvent* rho_win32_file_end_write(RWin32FileWrite* task, RInt bytes, RMemoryArena* arena)
{
    RWin32File* self  = task->self;
    RUint8*     pntr  = task->pntr;
    RInt        start = task->start;
    RInt        stop  = task->stop;

    LARGE_INTEGER advance = {0};

    advance.QuadPart = bytes;

    SetFilePointerEx(self->handle, advance, NULL, FILE_CURRENT);

    RFileEvent* result =
        rho_memory_arena_reserve_of(arena, RFileEvent, 1);

    if (result == NULL) return NULL;

    *result = rho_file_event_write(
        (RFile*) self, pntr, start, stop, bytes, task->ctxt);

    return (RIoEvent*) result;
}

static RBool32 rho_win32_file_begin_read(RWin32FileRead* task, RWin32IoQueue* queue)
{
    RWin32File* self  = task->self;
    RChar8*     pntr  = ((RChar8*) task->pntr) + task->start;
    RInt        size  = task->stop - task->start;
    RInt        bytes = 0;

    rho_win32_io_queue_bind_file(queue, self);

    DWORD offset_low  = 0;
    DWORD offset_high = 0;

    offset_low = SetFilePointer(self->handle,
        0, (LONG*) &offset_high, FILE_CURRENT);

    task->overlap.Offset     = offset_low;
    task->overlap.OffsetHigh = offset_high;

    BOOL status = ReadFile(self->handle, pntr,
        size, (DWORD*) &bytes, &task->overlap);

    if (status != 0) {
        PostQueuedCompletionStatus(queue->handle,
            bytes, 0, &task->overlap);

        return 1;
    }

    if (status == 0 && GetLastError() != ERROR_IO_PENDING)
        return 0;

    return 1;
}

static RIoEvent* rho_win32_file_end_read(RWin32FileRead* task, RInt bytes, RMemoryArena* arena)
{
    RWin32File* self  = task->self;
    RUint8*     pntr  = task->pntr;
    RInt        start = task->start;
    RInt        stop  = task->stop;

    LARGE_INTEGER advance = {0};

    advance.QuadPart = bytes;

    SetFilePointerEx(self->handle, advance, NULL, FILE_CURRENT);

    RFileEvent* result =
        rho_memory_arena_reserve_of(arena, RFileEvent, 1);

    if (result == NULL) return NULL;

    *result = rho_file_event_read(
        (RFile*) self, pntr, start, stop, bytes, task->ctxt);

    return (RIoEvent*) result;
}

RBool32 rho_win32_file_async_write(RWin32File* self, RUint8* pntr, RInt start, RInt stop, RWin32IoQueue* queue, void* ctxt)
{
    RWin32FileWrite* result = rho_memory_pool_reserve_of(
        &queue->pool, RWin32FileWrite, 1);

    if (result != NULL) {
        result->self      = self;
        result->pntr      = pntr;
        result->start     = start;
        result->stop      = stop;
        result->ctxt      = ctxt;
        result->overlap   = (OVERLAPPED) {0};
        result->callback  = rho_win32_file_end_write;
        result->list_next = NULL;

        if (rho_win32_file_begin_write(result, queue) != 0)
            return rho_win32_io_queue_submit(queue, (RWin32IoTask*) result);

        rho_memory_pool_release(&queue->pool, result);
    }

    return 0;
}

RBool32 rho_win32_file_async_read(RWin32File* self, RUint8* pntr, RInt start, RInt stop, RWin32IoQueue* queue, void* ctxt)
{
    RWin32FileRead* result = rho_memory_pool_reserve_of(
        &queue->pool, RWin32FileRead, 1);

    if (result != NULL) {
        result->self      = self;
        result->pntr      = pntr;
        result->start     = start;
        result->stop      = stop;
        result->ctxt      = ctxt;
        result->overlap   = (OVERLAPPED) {0};
        result->callback  = rho_win32_file_end_read;
        result->list_next = NULL;

        if (rho_win32_file_begin_read(result, queue) != 0)
            return rho_win32_io_queue_submit(queue, (RWin32IoTask*) result);

        rho_memory_pool_release(&queue->pool, result);
    }

    return 0;
}

#endif
