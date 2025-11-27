@echo off

set "base=src\base\export.c"
set "base_memory=src\base\memory\export.c"
set "system_memory=src\system\memory\export.c"

set "test_arena=test\system\memory\arena.c"

zig cc --std=c99 %base% %base_memory% %system_memory% %test_arena% ^
    -o bin\system_memory_arena.exe
