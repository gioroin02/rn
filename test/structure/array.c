#include "../../src/structure/export.h"

#include <stdio.h>

typedef RArray(RUint32) RUint32Array;

int  main(int argc, char** argv)
{
    RUint8 memory[256] = {0};

    RMemoryArena arena = rho_memory_arena_make(memory, sizeof memory);

    RUint32Array array = {0};

    printf("reserve = %lu\n", rho_array_create(&array, &arena, 17));

    rho_array_insert_back(&array, 156);
    rho_array_insert_back(&array, 222);
    rho_array_insert_back(&array, 9);
    rho_array_insert_back(&array, 453);
    rho_array_insert_back(&array, 333);

    RUint32 temp   = 0;
    RBool32 status = rho_array_remove(&array, 0, &temp);

    printf("remove (0) -> (x = %4lu, %s)\n", temp, status ? "SUCC" : "FAIL");

    temp   = 0;
    status = rho_array_remove(&array, 2, &temp);

    printf("remove (2) -> (x = %4lu, %s)\n", temp, status ? "SUCC" : "FAIL");

    for (RInt i = 0; i < rho_array_count(&array); i += 1)
        printf("#%03lli %4lu\n", i, *rho_array_get_pntr(&array, i));

    status = rho_array_drop_back(&array);

    printf("drop (back) -> (%s)\n", status ? "SUCC" : "FAIL");

    for (RInt i = 0; i < rho_array_count(&array); i += 1)
        printf("#%03lli %4lu\n", i, *rho_array_get_pntr(&array, i));

    rho_array_destroy(&array);
}
