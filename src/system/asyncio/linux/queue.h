#ifndef P_SYSTEM_LINUX_ASYNCIO_QUEUE_H
#define P_SYSTEM_LINUX_ASYNCIO_QUEUE_H

#include "import.h"

#define _DEFAULT_SOURCE

#include <unistd.h>
#include <errno.h>

#include <sys/epoll.h>

typedef struct epoll_event PEpollEvent;

#define __PLinuxAsyncIoTaskTag__ struct { \
    Int   handle;                         \
    void* callback;                       \
                                          \
    PLinuxAsyncIoTask* list_next;         \
}

typedef struct PLinuxAsyncIoTask
{
    Int   handle;
    void* callback;

    struct PLinuxAsyncIoTask* list_next;
}
PLinuxAsyncIoTask;

typedef struct PLinuxAsyncIoQueue
{
    Int handle;

    PMemoryPool pool;

    PLinuxAsyncIoTask* list_front;
    PLinuxAsyncIoTask* list_back;
}
PLinuxAsyncIoQueue;

typedef PAsyncIoEventKind (PLinuxAsyncIoProc) (void*, PMemoryArena*, PAsyncIoEvent** event);

PLinuxAsyncIoQueue* pLinuxAsyncIoQueueReserve(PMemoryArena* arena);

B32 pLinuxAsyncIoQueueCreate(PLinuxAsyncIoQueue* self, PMemoryPool pool);

void pLinuxAsyncIoQueueDestroy(PLinuxAsyncIoQueue* self);

PAsyncIoEventKind pLinuxAsyncIoQueuePollEvent(PLinuxAsyncIoQueue* self, Int timeout, PMemoryArena* arena, PAsyncIoEvent** event);

B32 pLinuxAsyncIoQueueSubmit(PLinuxAsyncIoQueue* self, PLinuxAsyncIoTask* value);

#endif
