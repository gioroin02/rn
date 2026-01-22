@echo off

set "compiler=zig cc"

set "impl=%impl% src\base\export.c"
set "impl=%impl% src\base\memory\export.c"

set "impl=%impl% src\string\export.c"

set "impl=%impl% src\graphics\opengl\export.c"

set "impl=%impl% src\system\memory\export.c"
set "impl=%impl% src\system\time\export.c"
set "impl=%impl% src\system\window\export.c"
set "impl=%impl% src\system\window\opengl\export.c"

set "test_opengl=%test_opengl% test\system\window\renderer\export.c"
set "test_opengl=%test_opengl% test\system\window\opengl.c"

%compiler% --std=c89 %impl% %test_opengl% -lgdi32 -lopengl32 -lm -o bin\system_window_opengl.exe
