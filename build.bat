@echo off

if not exist out mkdir out



pushd out
rem cl /EHsc /Femeta.exe /I ../include ../meta/meta.c ../meta/main.c
rem meta

cl /Zi /EHsc /Fegame.exe /I ../include ../src/main.c ../src/card.c ../src/arena.c /I.\raylib\include -MD /link /LIBPATH:"..\lib" raylib.lib kernel32.lib opengl32.lib shell32.lib winmm.lib user32.lib gdi32.lib
popd