#ifndef RN_WIN32_EVENT_QUEUE_C
#define RN_WIN32_EVENT_QUEUE_C

#include "./queue.h"

#define WIN32_LEAN_AND_MEAN

#include <windows.h>

typedef struct RnWin32EventWatcher
{
    HANDLE            handle;
    RnSystemEventKind eventsWanted;
    RnSystemEventKind eventsPending;
    OVERLAPPED        overlapRead;
    OVERLAPPED        overlapWrite;

    struct RnWin32EventWatcher* next;
}
RnWin32EventWatcher;

struct RnWin32EventQueue
{
    HANDLE           iocp;
    CRITICAL_SECTION lock;

    RnWin32EventWatcher* watchers;

    volatile LONG wakePending;
};

static RnWin32EventWatcher*
rnWin32EventQueueFindWatcher(RnWin32EventQueue* self, HANDLE value)
{
    RnWin32EventWatcher* watcher = self->watchers;

    for (; watcher != 0; watcher = watcher->next) {
        if (watcher->handle == value)
            return watcher;
    }

    return 0;
}

static void
rnWin32EventQueueRequestRead(RnWin32EventQueue* self, RnWin32EventWatcher* watcher)
{
    if ((watcher->eventsPending & RnSystemEvent_Read) != 0) return;

    BOOL status = ReadFile(watcher->handle, 0, 0, 0, &watcher->overlapRead);

    if (status == 0 && GetLastError() != ERROR_IO_PENDING)
        watcher->eventsPending |= RnSystemEvent_Error;
}

static void
rnWin32EventQueueRequestWrite(RnWin32EventQueue* self, RnWin32EventWatcher* watcher)
{
    if ((watcher->eventsPending & RnSystemEvent_Write) != 0) return;

    BOOL status = WriteFile(watcher->handle, 0, 0, 0, &watcher->overlapWrite);

    if (status == 0 && GetLastError() != ERROR_IO_PENDING)
        watcher->eventsPending |= RnSystemEvent_Error;
}

b32
rnWin32EventQueueCreate(RnWin32EventQueue* self)
{
    RnWin32EventQueue result = {0};

    if (self == 0) return 0;

    result.iocp = CreateIOCompletionPort(
        INVALID_HANDLE_VALUE, 0, 0, 0);

    if (result.iocp == 0) return 0;

    InitializeCriticalSection(&result.lock);

    *self = result;

    return 1;
}

void
rnWin32EventQueueDestroy(RnWin32EventQueue* self)
{
    if (self == 0) return;

    RnWin32EventWatcher* watcher = self->watchers;

    for (; watcher != 0; watcher = watcher->next)
        CancelIo(watcher->handle);

    DeleteCriticalSection(&self->lock);

    CloseHandle(self->iocp);
}

void rnWin32EventQueueWake(RnWin32EventQueue* self)
{
    if (InterlockedCompareExchange(&self->wakePending, 1, 0) == 0)
        PostQueuedCompletionStatus(self->iocp, 0, 0, 0);
}

b32
rnWin32EventQueuePoll(RnWin32EventQueue* self, RnSystemEvent* event, ssize timeout)
{
    OVERLAPPED_ENTRY entry = {0};
    ULONG            count = 0;

    BOOL status = GetQueuedCompletionStatusEx(self->iocp, &entry, 1, &count, timeout, 0);

    if (status == 0 || count == 0) {
        if (GetLastError() == WAIT_TIMEOUT) return 0;

        if (event != 0)
            *event = rnSystemEventError();

        return 0;
    }

    if (entry.lpCompletionKey == 0 && entry.lpOverlapped == 0) {
        InterlockedExchange(&self->wakePending, 0);

        return 0;
    }

    OVERLAPPED*          overlap = entry.lpOverlapped;
    RnWin32EventWatcher* watcher = ((RnWin32EventWatcher*) overlap->hEvent);

    if (watcher == 0) return 0;

    RnSystemEventKind pending = 0;
    ssize             size    = entry.dwNumberOfBytesTransferred;

    EnterCriticalSection(&self->lock);

    if (size != 0) {
        if (overlap == &watcher->overlapRead)  pending |= RnSystemEvent_Read;
        if (overlap == &watcher->overlapWrite) pending |= RnSystemEvent_Write;
    }
    else pending |= RnSystemEvent_Close;

    if (pending != 0) {
        RnSystemEvent temp = rnSystemEventMake(pending,
            ((void*) watcher->handle), size);

        if (event != 0) *event = temp;

        watcher->eventsPending &= ~pending;

        if ((pending & RnSystemEvent_Read) != 0)
            rnWin32EventQueueRequestRead(self, watcher);

        if ((pending & RnSystemEvent_Write) != 0)
            rnWin32EventQueueRequestWrite(self, watcher);

        LeaveCriticalSection(&self->lock);

        return 1;
    }

    LeaveCriticalSection(&self->lock);

    return 0;
}

#endif // RN_WIN32_EVENT_QUEUE_C
