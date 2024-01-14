CC := g++
CFLAGS := -std=c++11 -g
LIBS := -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
INC := -I include
SRCDIR := src
SCREENDIR := screens
BUILDDIR := build
BINDIR := bin

SRCEXT := cpp
SRC_SOURCES := $(wildcard $(SRCDIR)/*.cpp)
SCREEN_SOURCES := $(wildcard $(SCREENDIR)/*.cpp)
OBJECTS := $(patsubst $(SRCDIR)/%.cpp,$(BUILDDIR)/%.o,$(SRC_SOURCES)) \
           $(patsubst $(SCREENDIR)/%.cpp,$(BUILDDIR)/%.o,$(SCREEN_SOURCES))
TARGET := $(BINDIR)/pkmtoto

$(TARGET): $(OBJECTS)
	@mkdir -p $(BINDIR)
	$(CC) $^ -o $@ $(LIBS)

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

$(BUILDDIR)/%.o: $(SCREENDIR)/%.cpp | $(BUILDDIR)
	@mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

$(BUILDDIR):
	@mkdir -p $(BUILDDIR)

.PHONY: clean
clean:
	@rm -rf $(BUILDDIR) $(BINDIR)

.PHONY: run
run: $(TARGET)
	./$(TARGET)
