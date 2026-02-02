#include "../../../src/rho-base/memory/export.h"

#include <stdio.h>

int main(int argc, char** argv)
{
    RUint8 memory[256] = {0};

    RMemoryArena arena = rho_memory_arena_make(memory, sizeof memory);

    void* mark = rho_memory_arena_tell(&arena);
    RInt  size = 8;

    RUint8* pntr0 = rho_memory_arena_reserve(&arena, size, sizeof *pntr0);
    RUint8* pntr1 = rho_memory_arena_reserve(&arena, size, sizeof *pntr1);

    if (pntr0 != NULL) rho_memory_set(pntr0, size, 0x00);
    if (pntr1 != NULL) rho_memory_set(pntr1, size, 0x00);

    printf("pntr0 = 0x%012llX, ", ((RUint) pntr0));

    for (RInt i = 0; i < size; i += 1)
        printf("0x%02X ", pntr0 != NULL ? pntr0[i] : 0);
    printf("\n");

    printf("pntr1 = 0x%012llX, ", ((RUint) pntr1));

    for (RInt i = 0; i < size; i += 1)
        printf("0x%02X ", pntr1 != NULL ? pntr1[i] : 0);
    printf("\n");

    rho_memory_arena_release(&arena, pntr0);

    pntr0 = rho_memory_arena_reserve(&arena, size, sizeof *pntr0);

    if (pntr0 != NULL) rho_memory_set(pntr0, size, 0x00);

    printf("pntr0 = 0x%012llX, ", ((RUint) pntr0));

    for (RInt i = 0; i < size; i += 1)
        printf("0x%02X ", pntr0 != NULL ? pntr0[i] : 0);
    printf("\n");

    printf("pntr1 = 0x%012llX, ", ((RUint) pntr1));

    for (RInt i = 0; i < size; i += 1)
        printf("0x%02X ", pntr1 != NULL ? pntr1[i] : 0);
    printf("\n");

    rho_memory_arena_rewind(&arena, mark);

    pntr0 = rho_memory_arena_reserve(&arena, size, sizeof *pntr0);

    if (pntr0 != NULL) rho_memory_set(pntr0, size, 0x00);

    printf("pntr0 = 0x%012llX, ", ((RUint) pntr0));

    for (RInt i = 0; i < size; i += 1)
        printf("0x%02X ", pntr0 != NULL ? pntr0[i] : 0);
    printf("\n");

    printf("pntr1 = 0x%012llX, ", ((RUint) pntr1));

    for (RInt i = 0; i < size; i += 1)
        printf("0x%02X ", pntr1 != NULL ? pntr1[i] : 0);
    printf("\n");
}
