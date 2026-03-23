#include <SDL2/SDL.h>
#include <iostream>

int main(int argc, char *argv[]) {
  std::cout << "Initializing SDL..." << std::endl;
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL Init Failed: " << SDL_GetError() << std::endl;
    return 1;
  }

  std::cout << "Creating Window..." << std::endl;
  SDL_Window *window =
      SDL_CreateWindow("Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                       800, 600, SDL_WINDOW_SHOWN);
  if (!window) {
    std::cerr << "Window Failed: " << SDL_GetError() << std::endl;
    return 1;
  }

  std::cout << "Creating Renderer..." << std::endl;
  SDL_Renderer *renderer =
      SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  std::cout << "Entering Loop (Window should be visible now)..." << std::endl;
  bool quit = false;
  SDL_Event e;
  while (!quit) {
    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT)
        quit = true;
    }
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red screen
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
  }

  std::cout << "Cleaning up..." << std::endl;
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
