@echo off

set "compiler=zig cc"

set "base=src\base\export.c"
set "base_memory=src\base\memory\export.c"
set "system_memory=src\system\memory\export.c"

set "impl=%base% %base_memory% %system_memory%"

set "test_arena=test\system\memory\arena.c"

%compiler% --std=c99 %impl% %test_arena% -o bin\system_memory_arena.exe
