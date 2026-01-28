@echo off

set "compiler=zig cc"

set "impl=%impl% src\base\export.c"
set "impl=%impl% src\base\memory\export.c"
set "impl=%impl% src\base\string\export.c"
set "impl=%impl% src\system\memory\export.c"
set "impl=%impl% src\system\asyncio\export.c"
set "impl=%impl% src\system\storage\export.c"
set "impl=%impl% src\system\storage\async\export.c"

set "test_reading=test\system\storage\async\reading.c"

%compiler% --std=c99 %impl% %test_reading% -lws2_32 -o bin\system_storage_async_reading.exe
