compiler="gcc --debug"

impl="$impl src/rho-base/export.c"
impl="$impl src/rho-base/memory/export.c"
impl="$impl src/rho-base/string/export.c"
impl="$impl src/rho-structure/export.c"

test_array="test/structure/array.c"
test_map="test/structure/map.c"

$compiler --std=c99 $impl $test_array -o bin/structure_array.exe
$compiler --std=c99 $impl $test_map   -o bin/structure_map.exe
