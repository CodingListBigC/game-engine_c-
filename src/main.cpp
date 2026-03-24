#include "./manger/window.h"
#include <SDL2/SDL.h>
#include <iostream>

int main(int argc, char *argv[]) {
  Window newWindow;

  int windowStatus = newWindow.init();
  if (windowStatus != 0) {
    return 1;
  };

  std::cout << "Entering Loop (Window should be visible now)..." << std::endl;
  bool quit = false;
  SDL_Event e;
  while (!quit) {
    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT)
        quit = true;
    }
    newWindow.renderAll();
  }

  std::cout << "Cleaning up..." << std::endl;
  SDL_DestroyWindow(newWindow.getWindow());
  SDL_Quit();
  return 0;
}
