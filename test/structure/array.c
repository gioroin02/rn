#include "../../src/structure/export.h"

#include <stdio.h>

typedef PArray(U32) PArrayU32;

int  main(int argc, char** argv)
{
    U8 memory[256];

    PMemoryArena arena = pMemoryArenaMake(memory, sizeof memory);

    PArrayU32 array;

    printf("reserve = %llu\n", pArrayCreate(&array, &arena, 17));

    pArrayInsertBack(&array, 156);
    pArrayInsertBack(&array, 222);
    pArrayInsertBack(&array, 9);
    pArrayInsertBack(&array, 453);
    pArrayInsertBack(&array, 333);

    U32  temp  = 0;
    Bool state = pArrayRemove(&array, 0, &temp);

    printf("remove (0) -> (x = %4lu, %s)\n", temp, state ? "SUCC" : "FAIL");

    temp  = 0;
    state = pArrayRemove(&array, 2, &temp);

    printf("remove (2) -> (x = %4lu, %s)\n", temp, state ? "SUCC" : "FAIL");

    Int index = 0;

    for (index = 0; index < pArrayCount(&array); index += 1)
        printf("#%03lli %4lu\n", index, *pArrayGetPntr(&array, index));

    state = pArrayDropBack(&array);

    printf("drop (back) -> (%s)\n", state ? "SUCC" : "FAIL");

    for (index = 0; index < pArrayCount(&array); index += 1)
        printf("#%03lli %4lu\n", index, *pArrayGetPntr(&array, index));
}
