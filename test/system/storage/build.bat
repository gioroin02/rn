@echo off

set "compiler=zig cc"

set "impl=%impl% src\base\export.c"
set "impl=%impl% src\base\memory\export.c"
set "impl=%impl% src\system\memory\export.c"
set "impl=%impl% src\system\storage\export.c"

set "test_stdin=test\system\storage\stdin.c"

%compiler% --std=c89 %impl% %test_stdin% -o bin\system_storage_stdin.exe
