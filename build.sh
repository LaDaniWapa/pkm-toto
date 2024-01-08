#!/bin/bash

# Compile the program
if g++ -std=c++11 -g -I include -o main *.cpp include/*.cpp -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -fdiagnostics-color; then
    # Compilation successful, execute the program
    ./main
else
    # Compilation failed
    echo "Compilation failed. Fix errors before executing the program."
fi