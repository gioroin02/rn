#include "../../src/base/export.h"
#include "../../src/base/memory/export.h"
#include "../../src/base/string/export.h"

#include "../../src/structure/export.h"

#include <stdio.h>

typedef PxMap(PxString8, u32) PxMapString8ToU32;

ssize
pxString8Hash(PxString8* key)
{
    ssize result = 0;

    for (ssize i = 0; i < key->size; i += 1)
        result += ((ssize) key->values[i]);

    return result;
}

b32
pxString8IsEqual(PxString8* key, PxString8* other)
{
    if (key->size != other->size) return 0;

    for (ssize i = 0; i < key->size; i += 1) {
        if (key->values[i] != other->values[i])
            return 0;
    }

    return 1;
}

void
showPairs(PxMapString8ToU32* self, PxString8* keys, ssize size)
{
    for (ssize i = 0; i < size; i += 1) {
        u32* value = pxMapGetPtr(self, keys[i]);

        printf("map(%s) -> ", keys[i].values);

        if (value != 0)
            printf("%lu\n", *value);
        else
            printf("null\n");
    }
}

void
showLists(PxMapString8ToU32* self)
{
    for (ssize i = 0; i < pxMapCount(self); i += 1)
        printf("map(%lli) -> %s, %lu\n", i, self->keys[i].values, self->values[i]);
}

int
main(int argc, char** argv)
{
    u8 memory[1024] = {0};

    PxMemoryArena arena = pxMemoryArenaMake(memory, sizeof(memory));

    PxMapString8ToU32 map = {0};

    pxMapCreate(&map, &arena, 16, &pxString8Hash, &pxString8IsEqual);

    PxString8 keys[] = {
        pxStr8("Filiberto"),
        pxStr8("Astronfo"),
        pxStr8("Roboldofo"),
    };

    pxMapInsert(&map, keys[0], 10);
    pxMapInsert(&map, keys[1], 20);
    pxMapInsert(&map, keys[2], 30);

    showPairs(&map, keys, 3);
    showLists(&map);

    pxMapClear(&map);

    printf("\n");

    showPairs(&map, keys, 3);
    showLists(&map);
}
