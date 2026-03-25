#include "window.h"
#include "../utils/const/const.h"
#include <GL/glew.h> // Ensure GLEW is included here
#include <SDL2/SDL.h>
#include <iostream>

Window::Window() : window(nullptr), glContext(nullptr) {};

int Window::init() {
  // 1. Hyprland/Wayland Compatibility Fix
  setenv("SDL_VIDEODRIVER", "x11", 0);

  // 2. Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError()
              << std::endl;
    return 1;
  }

  // 3. Set OpenGL Attributes (Compatibility mode for Legacy GL)
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
                      SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

  // 4. Create Window
  window = SDL_CreateWindow("Arch Hyprland Cube", SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED, 800, 600,
                            SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

  // --- MISSING PIECE START ---
  glContext = SDL_GL_CreateContext(window);
  if (!glContext) {
    std::cerr << "GL Context could not be created!" << std::endl;
    return 1;
  }
  // 9. Global GL States
  glEnable(GL_DEPTH_TEST);
  glClearColor(0.1f, 0.1f, 0.15f, 1.0f); // "Oarchy" Dark Blue-Grey background

  return 0;
}

void Window::renderStart() {
  // --- RENDER START ---
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // --- SETUP PROJECTION (The "Camera Lens") ---
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
}

void Window::renderEnd() {
  // Render of render
  SDL_GL_SwapWindow(window);
}

void Window::cleanup() {
  if (glContext)
    SDL_GL_DeleteContext(glContext);
  if (window)
    SDL_DestroyWindow(window);

  SDL_Quit();
}
