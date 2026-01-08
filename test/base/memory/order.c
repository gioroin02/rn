#include "../../../src/base/memory/export.h"

#include <stdio.h>

int main(int argc, char** argv)
{
    if (pxHostByteOrderIsNetwork() != 0)
        printf("network\n");
    else
        printf("reverse\n");
}
