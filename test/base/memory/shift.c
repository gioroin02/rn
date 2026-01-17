#include "../../../src/base/memory/export.h"

#include <stdio.h>

int main(int argc, char** argv)
{
    U8 memory[32];

    Int index = 0;

    for (index = 0; index < sizeof memory; index += 1)
        memory[index] = (U8) index;

    for (index = 0; index < sizeof memory; index += 1) {
        printf("%2X ", memory[index]);

        if ((index + 1) % 16 == 0)
            printf("\n");
    }

    pMemoryShiftForw(memory, sizeof memory, 8, 0xAB);

    printf("\n");

    for (index = 0; index < sizeof memory; index += 1) {
        printf("%2X ", memory[index]);

        if ((index + 1) % 16 == 0)
            printf("\n");
    }

    pMemoryShiftBack(memory, sizeof memory, 8, 0xAB);

    printf("\n");

    for (index = 0; index < sizeof memory; index += 1) {
        printf("%2X ", memory[index]);

        if ((index + 1) % 16 == 0)
            printf("\n");
    }
}
