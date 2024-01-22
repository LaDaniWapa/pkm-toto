# Compiler and flags
CC = g++
CFLAGS = -std=c++11 -g -I include -o main

# Source and object files
SRC_DIRS = src screens
SRCS = $(wildcard $(addsuffix /*.cpp,$(SRC_DIRS)))
OBJS = $(patsubst %.cpp,build/%.o,$(SRCS))

# Raylib libraries
RAYLIB_LIBS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -fdiagnostics-color

# Default target
all: build bin/pokemonToto

# Build target
build:
	@mkdir -p build/screens build/src bin

# Compile object files
build/%.o: %.cpp | build
	$(CC) $(CFLAGS) -c $< -o $@

# Build main executable
bin/pokemonToto: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(RAYLIB_LIBS) -o bin/pokemonToto

# Clean up object files and the executable
clean:
	rm -rf build bin

run: bin/pokemonToto
	@./bin/pokemonToto

re: clean run