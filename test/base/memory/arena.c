#include "../../../src/base/memory/export.h"

#include <stdio.h>

int main(int argc, char** argv)
{
    U8 memory[256];

    PMemoryArena arena = pMemoryArenaMake(memory, sizeof memory);

    Int size = 8;

    U8* pntr0 = pMemoryArenaReserve(&arena, size, sizeof *pntr0);
    U8* pntr1 = pMemoryArenaReserve(&arena, size, sizeof *pntr1);

    if (pntr0 != NULL) pMemorySet(pntr0, size, 0x00);
    if (pntr1 != NULL) pMemorySet(pntr1, size, 0x00);

    printf("pntr0 = 0x%012llX, ", ((Uint) pntr0));

    for (Int i = 0; i < size; i += 1)
        printf("0x%X ", pntr0 != NULL ? pntr0[i] : 0);
    printf("\n");

    printf("pntr1 = 0x%012llX, ", ((Uint) pntr1));

    for (Int i = 0; i < size; i += 1)
        printf("0x%X ", pntr1 != NULL ? pntr1[i] : 0);
    printf("\n");

    pMemoryArenaRelease(&arena, pntr0);

    pntr0 = pMemoryArenaReserve(&arena, size, sizeof *pntr0);

    if (pntr0 != NULL) pMemorySet(pntr0, size, 0x00);

    printf("pntr0 = 0x%012llX, ", ((Uint) pntr0));

    for (Int i = 0; i < size; i += 1)
        printf("0x%X ", pntr0 != NULL ? pntr0[i] : 0);
    printf("\n");

    printf("pntr1 = 0x%012llX, ", ((Uint) pntr1));

    for (Int i = 0; i < size; i += 1)
        printf("0x%X ", pntr1 != NULL ? pntr1[i] : 0);
    printf("\n");
}
