#include "../../../src/system/memory/export.h"

#include <stdio.h>

int main(int argc, char** argv)
{
    PMemoryArena arena = pSystemMemoryReserve(16);

    printf("0x%llx, %lli\n",
        (Uint) pMemoryArenaPntr(&arena), pMemoryArenaSize(&arena));
}
