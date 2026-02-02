@echo off

set "compiler=zig cc"

set "impl=%impl% src\rho-base\export.c"
set "impl=%impl% src\rho-base\memory\export.c"
set "impl=%impl% src\rho-system\memory\export.c"

set "test_arena=test\system\memory\arena.c"

%compiler% --std=c99 %impl% %test_arena% -o bin\system_memory_arena.exe
