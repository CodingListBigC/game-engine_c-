CXX = g++
CXXFLAGS = -Wall -g $(shell sdl2-config --cflags)
LDFLAGS = $(shell sdl2-config --libs)

FILENAME = src/main.cpp

PROGRAM_OUTPUT_NAME = main
PROGRAM_OUTPUT_DIR = ./.build
PROGRAM_OUTPUT_FULL_NAME = $(PROGRAM_OUTPUT_DIR)/$(PROGRAM_OUTPUT_NAME)

# Default target: just typing 'make' will now trigger 'run'
all: run

# This rule creates the directory, then compiles the code
make_program: $(FILENAME)
	mkdir -p $(PROGRAM_OUTPUT_DIR)
	$(CXX) $(CXXFLAGS) $(FILENAME) -o $(PROGRAM_OUTPUT_FULL_NAME) $(LDFLAGS)

# This rule depends on make_program, then executes the result
run: make_program
	$(PROGRAM_OUTPUT_FULL_NAME)

# Cleans up the build directory entirely
clean:
	rm -rf $(PROGRAM_OUTPUT_DIR)
