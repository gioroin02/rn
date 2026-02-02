#include "../../../src/rho-system/memory/export.h"
#include "../../../src/rho-system/storage/export.h"

#include <stdio.h>

int main(int argc, char** argv)
{
    RMemoryArena arena = rho_system_memory_reserve(rho_memory_mib(2));

    RFile* file = rho_file_reserve(&arena);

    RString8     name    = rho_string8("README.md");
    RFileAttribs attribs = {0};

    if (argc >= 2) {
        name.values = (RChar8*) argv[1];
        name.size   = 0;

        for (RInt i = 0; i < 4096 && name.size == 0; i += 1) {
            if (name.values[i] == 0)
                name.size = i + 1;
        }
    }

    rho_file_find(name, &attribs);

    printf("Reading file '%.*s' (%lli bytes):\n",
        (int) name.size, name.values, attribs.size);

    rho_file_open(file, name, RFileMode_Read);

    RUint8* buffer = rho_memory_arena_reserve_of(&arena, RUint8, attribs.size + 1);

    RInt size = rho_file_read(file, buffer, 0, attribs.size);

    for (RInt i = size; i > 0; i -= 1) {
        if (buffer[i] != 0 && buffer[i] != 10 && buffer[i] != 13)
            break;

        buffer[i] = 0;
    }

    printf("%.*s", (int) size, buffer);

    rho_file_close(file);
}
