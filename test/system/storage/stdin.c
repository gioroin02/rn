#include "../../../src/system/memory/export.h"
#include "../../../src/system/storage/export.h"

#include <stdio.h>

int main(int argc, char** argv)
{
    PMemoryArena arena = pSystemMemoryReserve(pMemoryMIB(2));

    PFile* file = pFileReserve(&arena);

    pFileConsoleInput(file);

    U8 buffer[256];

    pMemorySet(buffer, sizeof buffer, 0x00);

    Int size = pFileRead(file, buffer, 0, sizeof buffer);

    printf("%.*s\n", (int) size, buffer);

    pFileDestroy(file);
}
