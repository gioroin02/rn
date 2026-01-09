#include "../../../src/system/memory/export.h"
#include "../../../src/system/storage/export.h"

#include <stdio.h>

int main(int argc, char** argv)
{
    PxMemoryArena arena = pxSystemMemoryReserve(pxMemoryMIB(2));

    PxFile* file = pxFileReserve(&arena);

    pxFileConsoleInput(file);

    u8 buffer[256];

    pxMemorySet(buffer, sizeof buffer, 0x00);

    ssize size = pxFileRead(file, buffer, 0, sizeof buffer);

    printf("%.*s\n", ((int) size), buffer);

    pxFileDestroy(file);
}
