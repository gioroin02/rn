#ifndef P_SYSTEM_STORAGE_FILE_H
#define P_SYSTEM_STORAGE_FILE_H

#include "import.h"

typedef struct PFile { U8 __private__; } PFile;

PFile* pFileReserve(PMemoryArena* arena);

void pFileDestroy(PFile* self);

Int pFileWrite(PFile* self, U8* pntr, Int start, Int stop);

Int pFileRead(PFile* self, U8* pntr, Int start, Int stop);

#endif
