#include "../utils/color/rgb_control.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <cwchar>
#include <iostream>
#ifndef WINDOW_H
#define WINDOW_H

class Window {

public:
  Window();
  int init();

  void renderAll();
  void renderStart();
  void renderEnd();

  void cleanup();
  SDL_Window *getWindow() { return this->window; };

private:
  // Main SDL window
  SDL_Window *window;
  SDL_Renderer *renderer;

  RGB_Control color{0, 255, 0};
};

#endif
