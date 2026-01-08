#include "../../../src/string/export.h"
#include "../../../src/system/memory/export.h"
#include "../../../src/system/window/export.h"

#define WIN32_LEAN_AND_MEAN

#include <stdio.h>
#include <windows.h>

int main(int argc, char** argv)
{
    PxMemoryArena arena = pxSystemMemoryReserve(pxMebi(2));

    PxWindow* window = pxWindowReserve(&arena);

    pxWindowCreate(window, pxStr8("PAX"), 800, 600);
    pxWindowVisibilitySet(window, PxWindowVisibility_Show);

    Sleep(1000);

    pxWindowDestroy(window);
}
