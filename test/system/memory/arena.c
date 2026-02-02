#include "../../../src/rho-system/memory/export.h"

#include <stdio.h>

int main(int argc, char** argv)
{
    RMemoryArena arena = rho_system_memory_reserve(16);

    printf("0x%llx, %lli\n",
        (RUint) rho_memory_arena_pntr(&arena), rho_memory_arena_size(&arena));
}
