#include "../../src/base/export.h"
#include "../../src/base/memory/export.h"
#include "../../src/base/string/export.h"

#include "../../src/structure/export.h"

#include <stdio.h>

typedef RnMap(RnString8, u32) RnMapString8ToU32;

ssize
rnString8Hash(RnString8* key)
{
    ssize result = 0;

    for (ssize i = 0; i < key->size; i += 1)
        result += ((ssize) key->values[i]);

    return result;
}

b32
rnString8IsEqual(RnString8* key, RnString8* other)
{
    if (key->size != other->size) return 0;

    for (ssize i = 0; i < key->size; i += 1) {
        if (key->values[i] != other->values[i])
            return 0;
    }

    return 1;
}

void
showPairs(RnMapString8ToU32* self, RnString8* keys, ssize size)
{
    for (ssize i = 0; i < size; i += 1) {
        u32* value = rnMapGetPtr(self, keys[i]);

        printf("map(%s) -> ", keys[i].values);

        if (value != 0)
            printf("%lu\n", *value);
        else
            printf("null\n");
    }
}

void
showLists(RnMapString8ToU32* self)
{
    for (ssize i = 0; i < rnMapCount(self); i += 1)
        printf("map(%lli) -> %s, %lu\n", i, self->keys[i].values, self->values[i]);
}

int
main(int argc, char** argv)
{
    u8 memory[1024] = {0};

    RnMemoryArena arena = rnMemoryArenaMake(memory, sizeof(memory));

    RnMapString8ToU32 map = {0};

    rnMapCreate(&map, &arena, 16, &rnString8Hash, &rnString8IsEqual);

    RnString8 keys[] = {
        rnStr8("Filiberto"),
        rnStr8("Astronfo"),
        rnStr8("Roboldofo"),
    };

    rnMapInsert(&map, keys[0], 10);
    rnMapInsert(&map, keys[1], 20);
    rnMapInsert(&map, keys[2], 30);

    showPairs(&map, keys, 3);
    showLists(&map);

    rnMapClear(&map);

    printf("\n");

    showPairs(&map, keys, 3);
    showLists(&map);
}
