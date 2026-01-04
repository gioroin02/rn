#ifndef PX_SYSTEM_STORAGE_FILE_H
#define PX_SYSTEM_STORAGE_FILE_H

#include "import.h"

typedef void PxFile;

PxFile*
pxFileReserve(PxMemoryArena* arena);

b32
pxFileDefaultInput(PxFile* self);

b32
pxFileDefaultOutput(PxFile* self);

b32
pxFileDefaultError(PxFile* self);

void
pxFileDestroy(PxFile* self);

ssize
pxFileWrite(PxFile* self, u8* values, ssize start, ssize stop);

ssize
pxFileRead(PxFile* self, u8* values, ssize start, ssize stop);

#endif // PX_SYSTEM_STORAGE_FILE_H
