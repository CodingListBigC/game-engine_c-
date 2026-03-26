cd build
rm -rf * # Wipe the build folder clean
cmake ..
make
SDL_VIDEODRIVER=x11 ./bin/game_engine
cd ..
