#include "../../../src/base/export.h"

#include <stdio.h>

int
main(int argc, char** argv)
{
    u8    buff[256] = {0};
    ssize index     = 0;

    for (index = 0; index < sizeof buff; index += 1)
        buff[index] = (u8) index;

    for (index = 0; index < sizeof buff; index += 1) {
        printf("%2X ", buff[index]);

        if ((index + 1) % 16 == 0)
            printf("\n");
    }

    pxMemoryShiftForw(buff, sizeof buff, 16, 0xAB);

    printf("\n");

    for (index = 0; index < sizeof buff; index += 1) {
        printf("%2X ", buff[index]);

        if ((index + 1) % 16 == 0)
            printf("\n");
    }

    pxMemoryShiftBack(buff, sizeof buff, 16, 0xAB);

    printf("\n");

    for (index = 0; index < sizeof buff; index += 1) {
        printf("%2X ", buff[index]);

        if ((index + 1) % 16 == 0)
            printf("\n");
    }
}
