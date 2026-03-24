#include "window.h"
#include "../utils/const/windowConst.h"
#include <SDL2/SDL.h>
#include <iostream>

Window::Window() {};

int Window::init() {
  std::cout << "Initializing SDL..." << std::endl;
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL Init Failed: " << SDL_GetError() << std::endl;
    return 1;
  }

  std::cout << "Creating Window..." << std::endl;
  this->window = SDL_CreateWindow("Test", SDL_WINDOWPOS_CENTERED,
                                  SDL_WINDOWPOS_CENTERED, Window_Const::width,
                                  Window_Const::height, SDL_WINDOW_SHOWN);
  if (!window) {
    std::cerr << "Window Failed: " << SDL_GetError() << std::endl;
    return 1;
  }

  std::cout << "Creating Renderer..." << std::endl;
  this->renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  return 0;
}

void Window::renderAll() {
  renderStart();
  renderEnd();
};
void Window::renderStart() {
  SDL_SetRenderDrawColor(renderer, color.getRedValue(), color.getGreenValue(),
                         color.getBlueValue(), 255); // Red screen
  SDL_RenderClear(renderer);
  SDL_RenderPresent(renderer);
};
void Window::renderEnd() {};
void Window::cleanup() {}
