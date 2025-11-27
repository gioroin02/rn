#include "../../src/structure/export.h"

#include <stdio.h>

typedef struct RnArray(u32) RnArrayU32;

int
main(int argc, char** argv)
{
    u32 memory[16] = {0};

    RnArrayU32 array = {.values = memory, .meta = {.size = 16}};

    ssize index = 0;

    index += rnArrayInsert(&array, index, 156);
    index += rnArrayInsert(&array, index, 222);
    index += rnArrayInsert(&array, index, 9);
    index += rnArrayInsert(&array, index, 453);
    index += rnArrayInsert(&array, index, 333);

    u32   temp  = 0;
    ssize state = rnArrayRemove(&array, 0, &temp);

    printf("remove (0, &x) -> (x = %lu, %s)\n", temp, state ? "SUCC" : "FAIL");
    printf("remove (2)     -> (%s)\n", rnArrayRemove(&array, 2, 0) ? "SUCC" : "FAIL");

    for (ssize i = 0; i < rnArrayCount(&array); i += 1)
        printf("#%03lli %lu\n", i, *rnArrayGetRef(&array, i));
}
