set files=src\glad.c src\main.c
set libs=..\lib\SDL2main.lib ..\lib\SDL2.lib ..\lib\freetype.lib

@echo Make sure you run vcvars32.bat first so that you get all the standard files for c like stdio.

CL /Zi /I ..\include %files% /link %libs%  /OUT:game.exe
