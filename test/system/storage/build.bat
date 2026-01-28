@echo off

set "compiler=zig cc"

set "impl=%impl% src\base\export.c"
set "impl=%impl% src\base\memory\export.c"
set "impl=%impl% src\base\string\export.c"
set "impl=%impl% src\system\memory\export.c"
set "impl=%impl% src\system\storage\export.c"

set "test_reading=test\system\storage\reading.c"

%compiler% --std=c99 %impl% %test_reading% -o bin\system_storage_reading.exe
