#!/bin/bash
# needs the compiled libraries from raylib releases "raylib-5.0_win64_mingw-64"
x86_64-w64-mingw32-g++ -I include -o pokemonToto.exe src/*.cpp screens/*.cpp -I/home/daniela/Desktop/raylib/src -L/home/daniela/Desktop/raylib-5.0_win64_mingw-w64/lib -lraylib -lopengl32 -lgdi32 -lkernel32 -luser32 -lshell32 -lwinmm -static-libgcc -static-libstdc++

