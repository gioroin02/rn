@echo off

set "compiler=zig cc"

set "impl=%impl% src\base\export.c"
set "impl=%impl% src\base\memory\export.c"
set "impl=%impl% src\string\export.c"
set "impl=%impl% src\system\memory\export.c"
set "impl=%impl% src\system\time\export.c"
set "impl=%impl% src\system\window\export.c"

set "impl=%impl% test\system\window\vector\export.c"

set "test_rectangle=test\system\window\rectangle.c"

%compiler% --std=c89 %impl% %test_rectangle% -lgdi32 -o bin\system_window_rectangle.exe
