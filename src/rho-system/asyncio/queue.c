#ifndef RHO_SYSTEM_ASYNCIO_QUEUE_C
#define RHO_SYSTEM_ASYNCIO_QUEUE_C

#include "queue.h"

#if RHO_SYSTEM == RHO_SYSTEM_WINDOWS

    #include "win32/export.c"

    #define __RIoQueue__ RWin32IoQueue

    #define __rho_io_queue_reserve__    rho_win32_io_queue_reserve
    #define __rho_io_queue_create__     rho_win32_io_queue_create
    #define __rho_io_queue_destroy__    rho_win32_io_queue_destroy
    #define __rho_io_queue_poll_event__ rho_win32_io_queue_poll_event

#elif RHO_SYSTEM == RHO_SYSTEM_LINUX

    #include "linux/export.c"

    #define __RIoQueue__ RLinuxIoQueue

    #define __rho_io_queue_reserve__    rho_linux_io_queue_reserve
    #define __rho_io_queue_create__     rho_linux_io_queue_create
    #define __rho_io_queue_destroy__    rho_linux_io_queue_destroy
    #define __rho_io_queue_poll_event__ rho_linux_io_queue_poll_event


#else

    #error "Unknown platform"

#endif

RIoQueue* rho_io_queue_reserve(RMemoryArena* arena)
{
    return (RIoQueue*) __rho_io_queue_reserve__(arena);
}

RBool32 rho_io_queue_create(RIoQueue* self, RMemoryPool pool)
{
    return __rho_io_queue_create__((__RIoQueue__*) self, pool);
}

void rho_io_queue_destroy(RIoQueue* self)
{
    return __rho_io_queue_destroy__((__RIoQueue__*) self);
}

RIoEvent* rho_io_queue_poll_event(RIoQueue* self, RInt timeout, RMemoryArena* arena)
{
    return __rho_io_queue_poll_event__((__RIoQueue__*) self, timeout, arena);
}

#endif
