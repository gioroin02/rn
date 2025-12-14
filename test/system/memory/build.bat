@echo off

set "compiler=zig cc"

set "impl=%impl% src\base\export.c"
set "impl=%impl% src\base\memory\export.c"
set "impl=%impl% src\system\memory\export.c"

set "impl=%base% %base_memory% %system_memory%"

set "test_arena=test\system\memory\arena.c"

%compiler% --std=c99 %impl% %test_arena% -o bin\system_memory_arena.exe
