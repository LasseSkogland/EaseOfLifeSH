@echo off
gcc src/*.c src/engine/*.c -O3 -s -o gltest -lmingw32 -lSDLmain -lSDL -lopengl32 -lglu32 -Wl,--subsystem,windows
IF ERRORLEVEL 1 pause
