@echo off
echo compiling using gcc because cl sucks.
@REM note: sdl2.dll is added to the path env so please add it manually.
@REM vcvars32.bat // use this once..
@REM cl /Fea.exe ../sandbox.cpp ../src/engine.cpp ../src/log.cpp /Wall /EHsc /I ../inc/sdl  /I ../inc/engine /link ../lib/SDL2main.lib ../lib/SDL2.lib
echo compiling and linking files
gcc -c -I ../include src/main.c src/glad.c src/engine/global.c src/engine/render/render.c src/engine/input/input.c src/engine/render/render_init.c
echo creating binary
@REM note: sdl works file with the -l in -lSDL2main and the sdl2 one... include -lib in -lSDL2main which makes it -libSDL2main.
gcc main.o glad.o global.o render.o render_init.o input.o -o app.exe -L ../lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image
popd
