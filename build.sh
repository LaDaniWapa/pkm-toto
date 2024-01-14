#!/bin/bash

if g++ -std=c++11 -g -I include -o main src/*.cpp screens/*.cpp -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -fdiagnostics-color; then
    ./main
else
    echo "Compilation failed. Fix errors before executing the program."
fi