#ifndef RHO_SYSTEM_WIN32_STORAGE_ASYNC_FILE_H
#define RHO_SYSTEM_WIN32_STORAGE_ASYNC_FILE_H

#include "import.h"

typedef struct RWin32FileWrite
{
    __RWin32IoTaskTag__;

    RWin32File* self;
    void*       ctxt;

    RUint8* pntr;
    RInt    start;
    RInt    stop;
}
RWin32FileWrite;

typedef struct RWin32FileRead
{
    __RWin32IoTaskTag__;

    RWin32File* self;
    void*       ctxt;

    RUint8* pntr;
    RInt    start;
    RInt    stop;
}
RWin32FileRead;

RBool32 rho_win32_file_async_write(RWin32File* self, RUint8* pntr, RInt start, RInt stop, RWin32IoQueue* queue, void* ctxt);

RBool32 rho_win32_file_async_read(RWin32File* self, RUint8* pntr, RInt start, RInt stop, RWin32IoQueue* queue, void* ctxt);

#endif
