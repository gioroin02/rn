#include "../../../src/base/memory/export.h"

#include <stdio.h>

int main(int argc, char** argv)
{
    RUint8 memory[256] = {0};

    RMemoryPool pool = rho_memory_pool_make(memory, sizeof memory, 8);

    RInt size = 8;

    RUint8* pntr0 = rho_memory_pool_reserve(&pool, size, sizeof *pntr0);
    RUint8* pntr1 = rho_memory_pool_reserve(&pool, size, sizeof *pntr1);

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

    rho_memory_pool_release(&pool, pntr0);

    pntr0 = rho_memory_pool_reserve(&pool, size, sizeof *pntr0);

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
