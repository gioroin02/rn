compiler="gcc --debug"

impl="$impl src/base/export.c"
impl="$impl src/base/memory/export.c"
impl="$impl src/base/string/export.c"
impl="$impl src/system/memory/export.c"
impl="$impl src/system/asyncio/export.c"
impl="$impl src/system/storage/export.c"
impl="$impl src/system/storage/async/export.c"

test_reading="test/system/storage/async/reading.c"

$compiler --std=c99 $impl $test_reading -o bin/system_storage_async_reading.exe
