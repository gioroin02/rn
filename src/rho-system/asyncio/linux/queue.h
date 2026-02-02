#ifndef RHO_SYSTEM_ASYNCIO_LINUX_QUEUE_H
#define RHO_SYSTEM_ASYNCIO_LINUX_QUEUE_H

#include "import.h"

#ifndef _DEFAULT_SOURCE

    #define _DEFAULT_SOURCE

#endif

#include <unistd.h>
#include <errno.h>

#include <sys/epoll.h>

typedef struct epoll_event RLinuxEpollEvent;

#define __RLinuxIoTaskTag__ struct { \
    RInt  handle;                    \
    void* callback;                  \
                                     \
    RLinuxIoTask* list_next;         \
}

typedef struct RLinuxIoTask RLinuxIoTask;

typedef struct RLinuxIoTask
{
    RInt  handle;
    void* callback;

    RLinuxIoTask* list_next;
}
RLinuxIoTask;

typedef struct RLinuxIoQueue
{
    RInt handle;

    RMemoryPool pool;

    RLinuxIoTask* list_front;
    RLinuxIoTask* list_back;
}
RLinuxIoQueue;

typedef RIoEvent* (RLinuxIoProc) (void*, RMemoryArena*);

RLinuxIoQueue* rho_linux_io_queue_reserve(RMemoryArena* arena);

RBool32 rho_linux_io_queue_create(RLinuxIoQueue* self, RMemoryPool pool);

void rho_linux_io_queue_destroy(RLinuxIoQueue* self);

RIoEvent* rho_linux_io_queue_poll_event(RLinuxIoQueue* self, RInt timeout, RMemoryArena* arena);

RBool32 rho_linux_io_queue_submit(RLinuxIoQueue* self, RLinuxIoTask* value);

#endif
