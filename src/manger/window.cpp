#include "window.h"
#include "../utils/const/const.h"
#include <GL/glew.h> // Ensure GLEW is included here
#include <SDL2/SDL.h>
#include <iostream>

Window::Window() : window(nullptr), glContext(nullptr) {};

int Window::init() {
  std::cout << "Initializing SDL..." << std::endl;
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    return 1;
  }

  // 1. Setup OpenGL Attributes
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

  std::cout << "Creating Window..." << std::endl;
  // 2. Added SDL_WINDOW_OPENGL flag
  this->window = SDL_CreateWindow("3D Cube Test", SDL_WINDOWPOS_CENTERED,
                                  SDL_WINDOWPOS_CENTERED, Window_Const::width,
                                  Window_Const::height,
                                  SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

  if (!window) {
    std::cerr << "Window Failed: " << SDL_GetError() << std::endl;
    return 1;
  }

  // 3. Create and store the OpenGL Context
  this->glContext = SDL_GL_CreateContext(window);
  if (this->glContext) {
    SDL_GL_MakeCurrent(window, this->glContext); // Add this!
  } else {
    std::cerr << "OpenGL Context Failed: " << SDL_GetError() << std::endl;
    return 1;
  }

  // 4. Important: glViewport tells OpenGL the size of the window
  glViewport(0, 0, Window_Const::width, Window_Const::height);
  glEnable(GL_DEPTH_TEST); // Needed so the cube doesn't look inside-out

  return 0;
}

void Window::renderStart() {
  // Use OpenGL clear color instead of SDL_Renderer
  glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::renderEnd() {
  // This is the OpenGL version of SDL_RenderPresent
  SDL_GL_SwapWindow(window);
}

void Window::cleanup() {
  if (glContext)
    SDL_GL_DeleteContext(glContext);
  if (window)
    SDL_DestroyWindow(window);
}
