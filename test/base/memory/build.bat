@echo off

set "compiler=zig cc"

set "impl=%impl% src\base\export.c"
set "impl=%impl% src\base\memory\export.c"

set "test_slice=test\base\memory\slice.c"
set "test_order=test\base\memory\order.c"

%compiler% --std=c99 %impl% %test_slice% -o bin\base_memory_slice.exe
%compiler% --std=c99 %impl% %test_order% -o bin\base_memory_order.exe
