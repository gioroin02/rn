@echo off

set "compiler=zig cc"

set "impl=%impl% src\rho-base\export.c"
set "impl=%impl% src\rho-base\memory\export.c"
set "impl=%impl% src\rho-base\string\export.c"

set "impl=%impl% src\rho-graphics\opengl\export.c"

set "impl=%impl% src\rho-system\memory\export.c"
set "impl=%impl% src\rho-system\window\export.c"
set "impl=%impl% src\rho-system\window\opengl\export.c"
set "impl=%impl% src\rho-system\time\export.c"

set "test_opengl=%test_opengl% test\system\window\opengl.c"

%compiler% --std=c99 %impl% %test_opengl% -lgdi32 -lopengl32 -lm -o bin\system_window_opengl.exe
