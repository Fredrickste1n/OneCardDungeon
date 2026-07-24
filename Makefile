# Compiler and flags
CXX = clang++
CXXFLAGS = -Wall -std=c++17 -D_DEFAULT_SOURCE -Wno-missing-braces -g -O0 -DPLATFORM_DESKTOP

# Include and library paths
INCLUDES = -I. -Isrc -Isrc/external -I/opt/homebrew/include
LIBS = -L. -L/opt/homebrew/lib -lraylib -framework OpenGL -framework OpenAL -framework Cocoa -framework IOKit

# Source files and output
SRC = $(wildcard src/*.cpp)
TARGET = main

# Default target
all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) -o $(TARGET) $(SRC) $(CXXFLAGS) $(INCLUDES) $(LIBS)

# Clean build artifacts
clean:
	rm -f $(TARGET)

# Run the program after building
run: all
	./$(TARGET)

.PHONY: all clean run