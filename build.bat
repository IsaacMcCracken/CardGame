rem Once other people start working this project we will migrate to makefiles 

@echo off

if not exist out mkdir out





pushd out
rem cl /EHsc /Femeta.exe /I ../include ../meta/meta.c ../meta/main.c
rem meta

@REM Meta programming stuff we might not use
rem echo MetaProgram
rem cl /Zi /EHsc /Femeta.exe ../meta/meta_main.c
rem meta ../generation/entity.mdesk

cl /Zi /EHsc /Fegame.exe /I ../include ../src/main.c ../src/world.c ../src/card.c ../src/card_types.c ../src/agent.c ../src/entity.c ../src/rayutil.c  ../src/arena.c /I.\raylib\include -MD /link /LIBPATH:"..\lib" raylib.lib kernel32.lib opengl32.lib shell32.lib winmm.lib user32.lib gdi32.lib
popd