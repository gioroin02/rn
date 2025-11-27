#include "../../../src/system/memory/export.h"

#include <stdio.h>

int
main(int argc, char** argv)
{
    RnMemoryArena arena = rnSystemMemoryReserve(16);

    printf("0x%llx, %lli\n",
        ((usize) arena.values), arena.size);
}
