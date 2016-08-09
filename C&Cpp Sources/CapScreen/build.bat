@echo off
gcc -s -w -o CapScreen CapScreen.c -lmingw32 -lSDLmain -luser32 -lgdi32 -lSDL.dll
