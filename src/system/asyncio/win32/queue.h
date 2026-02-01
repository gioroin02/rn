#ifndef RHO_SYSTEM_ASYNCIO_WIN32_QUEUE_H
#define RHO_SYSTEM_ASYNCIO_WIN32_QUEUE_H

#include "import.h"

#define WIN32_LEAN_AND_MEAN
#define NOGDI

#include <windows.h>

// TODO(Gio): OBJECT POOL. In the future replace the linked list and the memory pool with an array of blocks of constant size,
// the array would have an implicit free list to get a new block in constant time but still access active ones by index.
// This removes the need for an explicity memory pool (and 16 bytes of header per node) and a linear time search through the list.

#define __RWin32IoTaskTag__ struct { \
    OVERLAPPED overlap;              \
    void*      callback;             \
                                     \
    RWin32IoTask* list_next;         \
}

typedef struct RWin32IoTask RWin32IoTask;

struct RWin32IoTask
{
    OVERLAPPED overlap;
    void*      callback;

    RWin32IoTask* list_next;
};

typedef struct RWin32IoQueue
{
    HANDLE handle;

    RMemoryPool pool;

    RWin32IoTask* list_front;
    RWin32IoTask* list_back;
}
RWin32IoQueue;

typedef RIoEvent* (RWin32IoProc) (void*, RInt, RMemoryArena*);

RWin32IoQueue* rho_win32_io_queue_reserve(RMemoryArena* arena);

RBool32 rho_win32_io_queue_create(RWin32IoQueue* self, RMemoryPool pool);

void rho_win32_io_queue_destroy(RWin32IoQueue* self);

RIoEvent* rho_win32_io_queue_poll_event(RWin32IoQueue* self, RInt timeout, RMemoryArena* arena);

RBool32 rho_win32_io_queue_submit(RWin32IoQueue* self, RWin32IoTask* value);

#endif
