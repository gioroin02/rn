compiler="gcc"

impl="$impl src/base/export.c"
impl="$impl src/base/memory/export.c"
impl="$impl src/string/export.c"
impl="$impl src/structure/export.c"

test_array="test/structure/array.c"
test_map="test/structure/map.c"

$compiler --std=c99 $impl $test_array -o bin/structure_array.exe
$compiler --std=c99 $impl $test_map   -o bin/structure_map.exe
