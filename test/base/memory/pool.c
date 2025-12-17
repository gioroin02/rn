#include "../../../src/base/export.h"

#include <stdio.h>

int
main(int argc, char** argv)
{
    u8 buff[256] = {0};

    PxMemoryPool pool = pxMemoryPoolMake(buff, sizeof buff, 8);

    ssize index = 0;
    ssize size  = 8;

    u8* pntr0 = pxMemoryPoolReserve(&pool, size, sizeof *pntr0);
    u8* pntr1 = pxMemoryPoolReserve(&pool, size, sizeof *pntr1);

    if (pntr0 != PX_NULL) pxMemorySet(pntr0, size, 0x00);
    if (pntr1 != PX_NULL) pxMemorySet(pntr1, size, 0x00);

    printf("pntr0 = 0x%012llX, ", ((usize) pntr0));

    for (index = 0; index < size; index += 1)
        printf("0x%X ", pntr0 != PX_NULL ? pntr0[index] : 0);
    printf("\n");

    printf("pntr1 = 0x%012llX, ", ((usize) pntr1));

    for (index = 0; index < size; index += 1)
        printf("0x%X ", pntr1 != PX_NULL ? pntr1[index] : 0);
    printf("\n");

    pxMemoryPoolRelease(&pool, pntr0);

    pntr0 = pxMemoryPoolReserve(&pool, size, sizeof *pntr0);

    if (pntr0 != PX_NULL) pxMemorySet(pntr0, size, 0x00);

    printf("pntr0 = 0x%012llX, ", ((usize) pntr0));

    for (index = 0; index < size; index += 1)
        printf("0x%X ", pntr0 != PX_NULL ? pntr0[index] : 0);
    printf("\n");

    printf("pntr1 = 0x%012llX, ", ((usize) pntr1));

    for (index = 0; index < size; index += 1)
        printf("0x%X ", pntr1 != PX_NULL ? pntr1[index] : 0);
    printf("\n");
}
