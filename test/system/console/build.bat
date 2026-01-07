@echo off

set "compiler=zig cc"

set "impl=%impl% src\base\export.c"
set "impl=%impl% src\base\memory\export.c"
set "impl=%impl% src\system\memory\export.c"
set "impl=%impl% src\system\console\export.c"

set "test_mode=test\system\console\mode.c"

%compiler% --std=c89 %impl% %test_mode% -lws2_32 -o bin\system_console_mode.exe
