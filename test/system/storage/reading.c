#include "../../../src/system/memory/export.h"
#include "../../../src/system/storage/export.h"

#include <stdio.h>

int main(int argc, char** argv)
{
    PMemoryArena arena = pSystemMemoryReserve(pMemoryMIB(2));

    PFile* file = pFileReserve(&arena);

    PString8     name    = pString8("README.md");
    PFileAttribs attribs = {0};

    if (argc >= 2) {
        name.values = (U8*) argv[1];
        name.size   = 0;

        for (Int i = 0; i < 4096 && name.size == 0; i += 1) {
            if (name.values[i] == 0)
                name.size = i + 1;
        }
    }

    pFileAttribs(name, &attribs);

    printf("Reading file '%.*s' (%lli bytes):\n",
        (int) name.size, name.values, attribs.size);

    pFileOpen(file, name, PFileMode_Read);

    U8* buffer = pMemoryArenaReserveManyOf(&arena, U8, attribs.size + 1);

    Int size = pFileRead(file, buffer, 0, attribs.size);

    for (Int i = size; i > 0; i -= 1) {
        if (buffer[i] != 0 && buffer[i] != 10 && buffer[i] != 13)
            break;

        buffer[i] = 0;
    }

    printf("%.*s", (int) size, buffer);

    pFileClose(file);
}
