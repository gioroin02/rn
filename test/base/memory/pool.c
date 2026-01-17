#include "../../../src/base/memory/export.h"

#include <stdio.h>

int main(int argc, char** argv)
{
    U8 memory[256];

    PMemoryPool pool = pMemoryPoolMake(memory, sizeof memory, 8);

    Int index = 0;
    Int size  = 8;

    U8* pntr0 = pMemoryPoolReserve(&pool, size, sizeof *pntr0);
    U8* pntr1 = pMemoryPoolReserve(&pool, size, sizeof *pntr1);

    if (pntr0 != NULL) pMemorySet(pntr0, size, 0x00);
    if (pntr1 != NULL) pMemorySet(pntr1, size, 0x00);

    printf("pntr0 = 0x%012llX, ", ((Uint) pntr0));

    for (index = 0; index < size; index += 1)
        printf("0x%X ", pntr0 != NULL ? pntr0[index] : 0);
    printf("\n");

    printf("pntr1 = 0x%012llX, ", ((Uint) pntr1));

    for (index = 0; index < size; index += 1)
        printf("0x%X ", pntr1 != NULL ? pntr1[index] : 0);
    printf("\n");

    pMemoryPoolRelease(&pool, pntr0);

    pntr0 = pMemoryPoolReserve(&pool, size, sizeof *pntr0);

    if (pntr0 != NULL) pMemorySet(pntr0, size, 0x00);

    printf("pntr0 = 0x%012llX, ", ((Uint) pntr0));

    for (index = 0; index < size; index += 1)
        printf("0x%X ", pntr0 != NULL ? pntr0[index] : 0);
    printf("\n");

    printf("pntr1 = 0x%012llX, ", ((Uint) pntr1));

    for (index = 0; index < size; index += 1)
        printf("0x%X ", pntr1 != NULL ? pntr1[index] : 0);
    printf("\n");
}
