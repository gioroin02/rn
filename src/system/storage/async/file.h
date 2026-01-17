#ifndef P_SYSTEM_STORAGE_ASYNC_FILE_H
#define P_SYSTEM_STORAGE_ASYNC_FILE_H

#include "import.h"

typedef void (PFileWriteProc) (void*, PFile*, U8*, Int, Int, Int);
typedef void (PFileReadProc)  (void*, PFile*, U8*, Int, Int, Int);

Bool pFileWriteAsync(PFile* self, U8* pntr, Int start, Int stop, PAsyncIoQueue* queue, void* ctxt, void* proc);

Bool pFileReadAsync(PFile* self, U8* pntr, Int start, Int stop, PAsyncIoQueue* queue, void* ctxt, void* proc);

#endif // P_SYSTEM_STORAGE_ASYNC_FILE_H
