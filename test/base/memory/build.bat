@echo off

set "compiler=zig cc"

set "impl=%impl% src\base\export.c"

set "test_order=test\base\memory\order.c"
set "test_arena=test\base\memory\arena.c"
set "test_pool=test\base\memory\pool.c"
set "test_shift=test\base\memory\shift.c"

%compiler% --std=c89 %impl% %test_order% -o bin\base_memory_order.exe
%compiler% --std=c89 %impl% %test_arena% -o bin\base_memory_arena.exe
%compiler% --std=c89 %impl% %test_pool%  -o bin\base_memory_pool.exe
%compiler% --std=c89 %impl% %test_shift% -o bin\base_memory_shift.exe
