compiler="gcc --debug"

impl="$impl src/base/export.c"
impl="$impl src/base/memory/export.c"
impl="$impl src/base/string/export.c"
impl="$impl src/system/memory/export.c"
impl="$impl src/system/storage/export.c"

test_reading="test/system/storage/reading.c"

$compiler --std=c99 $impl $test_reading -o bin/system_storage_reading.exe
