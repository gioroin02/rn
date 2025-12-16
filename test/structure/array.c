#include "../../src/structure/export.h"

#include <stdio.h>

typedef PxArray(u32) PxArrayU32;

int
main(int argc, char** argv)
{
    u8 memory[256] = {0};

    PxMemoryArena arena = pxMemoryArenaMake(memory, sizeof(memory));

    PxArrayU32 array = {0};

    printf("reserve = %lu\n", pxArrayCreate(&array, &arena, 17));

    ssize index = 0;

    index += pxArrayInsert(&array, index, 156);
    index += pxArrayInsert(&array, index, 222);
    index += pxArrayInsert(&array, index, 9);
    index += pxArrayInsert(&array, index, 453);
    index += pxArrayInsert(&array, index, 333);

    u32   temp  = 0;
    ssize state = pxArrayRemove(&array, 0, &temp);

    printf("remove (0, &x) -> (x = %lu, %s)\n", temp, state ? "SUCC" : "FAIL");
    printf("remove (2)     -> (%s)\n", pxArrayRemove(&array, 2, 0) ? "SUCC" : "FAIL");

    for (ssize i = 0; i < pxArrayCount(&array); i += 1)
        printf("#%03lli %lu\n", i, *pxArrayGetPtr(&array, i));
}
