#!/bin/bash

# Move into build directory
cd build || exit

# Run CMake
cmake ..

# Run make and ONLY run the engine if make succeeds
make && SDL_VIDEODRIVER=x11 ./bin/game_engine

# Go back to the root directory
cd ..
