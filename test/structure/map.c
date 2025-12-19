#include "../../src/base/export.h"
#include "../../src/structure/export.h"

#include <stdio.h>

typedef PxMap(PxStr8, u32) PxString8U32Map;

ssize
pxString8Hash(PxStr8* key)
{
    ssize result = 0;
    ssize index  = 0;

    for (index = 0; index < key->size; index += 1)
        result += ((ssize) key->values[index]);

    return result;
}

b32
pxString8IsEqual(PxStr8* key, PxStr8* other)
{
    ssize index = 0;

    if (key->size != other->size) return 0;

    for (index = 0; index < key->size; index += 1) {
        if (key->values[index] != other->values[index])
            return 0;
    }

    return 1;
}

void
showPairs(PxString8U32Map* self, PxStr8* keys, ssize size)
{
    ssize index = 0;

    for (index = 0; index < size; index += 1) {
        u32* value = pxMapGetPtr(self, keys[index]);

        printf("map(%s) -> ", keys[index].values);

        if (value != 0)
            printf("%lu\n", *value);
        else
            printf("null\n");
    }
}

void
showLists(PxString8U32Map* self)
{
    ssize index = 0;

    for (index = 0; index < pxMapCount(self); index += 1) {
        PxStr8 key   = self->keys[index];
        u32    value = self->values[index];

        printf("map(%lli) -> %s, %lu\n",
            index, key.values, value);
    }
}

int
main(int argc, char** argv)
{
    u8 memory[1024] = {0};

    PxMemoryArena arena = pxMemoryArenaMake(memory, sizeof(memory));

    PxString8U32Map map = {0};

    pxMapCreate(&map, &arena, 16, &pxString8Hash, &pxString8IsEqual);

    PxStr8 keys[] = {
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
