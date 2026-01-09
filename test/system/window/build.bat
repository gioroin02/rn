@echo off

set "compiler=zig cc"

set "impl=%impl% src\base\export.c"
set "impl=%impl% src\base\memory\export.c"
set "impl=%impl% src\string\export.c"
set "impl=%impl% src\system\memory\export.c"
set "impl=%impl% src\system\window\export.c"

set "test_popup=test\system\window\gradient.c"

%compiler% --std=c89 %impl% %test_popup% -lgdi32 -o bin\system_window_gradient.exe
