
cd build || exit

make && SDL_VIDEODRIVER=x11 ./bin/game_engine
cd ..
