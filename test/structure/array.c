#include "../../src/structure/export.h"

#include <stdio.h>

typedef PxArray(u32) PxArrayU32;

int  main(int argc, char** argv)
{
    u8 memory[256];

    PxMemoryArena arena = pxMemoryArenaMake(memory, sizeof memory);

    PxArrayU32 array;

    printf("reserve = %lu\n", pxArrayCreate(&array, &arena, 17));

    pxArrayInsertBack(&array, 156);
    pxArrayInsertBack(&array, 222);
    pxArrayInsertBack(&array, 9);
    pxArrayInsertBack(&array, 453);
    pxArrayInsertBack(&array, 333);

    u32   temp  = 0;
    ssize state = pxArrayRemove(&array, 0, &temp);

    printf("remove (0,   &x) -> (x = %4lu, %s)\n", temp, state ? "SUCC" : "FAIL");

    temp  = 0;
    state = pxArrayRemove(&array, 2, PX_NULL);

    printf("remove (2, null) -> (x = %4lu, %s)\n", temp, state ? "SUCC" : "FAIL");

    ssize index = 0;

    for (index = 0; index < pxArrayCount(&array); index += 1)
        printf("#%03lli %4lu\n", index, *pxArrayGetPntr(&array, index));
}
