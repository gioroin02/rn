#include "../../src/base/export.h"
#include "../../src/structure/export.h"

#include <stdio.h>

typedef PxArray(u32) PxU32Array;

int
main(int argc, char** argv)
{
    u8 memory[256] = {0};

    PxMemoryArena arena = pxMemoryArenaMake(memory, sizeof(memory));

    PxU32Array array;

    printf("reserve = %lu\n", pxArrayCreate(&array, &arena, 17));

    ssize index = 0;

    index += pxArrayInsert(&array, index, 156);
    index += pxArrayInsert(&array, index, 222);
    index += pxArrayInsert(&array, index, 9);
    index += pxArrayInsert(&array, index, 453);
    index += pxArrayInsert(&array, index, 333);

    u32   temp  = 0;
    ssize state = pxArrayRemove(&array, 0, &temp);

    printf("remove (0,   &x) -> (x = %4lu, %s)\n", temp, state ? "SUCC" : "FAIL");

    temp  = 0;
    state = pxArrayRemove(&array, 2, PX_NULL);

    printf("remove (2, null) -> (x = %4lu, %s)\n", temp, state ? "SUCC" : "FAIL");

    for (index = 0; index < pxArrayCount(&array); index += 1)
        printf("#%03lli %4lu\n", index, *pxArrayGetPtr(&array, index));
}
