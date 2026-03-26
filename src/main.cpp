#include "./manger/window.h"
#include "./models/obj_loader.h"
#include "./user/camera.h"
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <filesystem>
#include <iostream>
#include <vector>

// Include your tiny_obj_loader here
#define TINYOBJLOADER_IMPLEMENTATION

int main(int argc, char *argv[]) {
  Window masterWindow;
  User_Camera userCamera{};
  if (masterWindow.init() == 1) {
    std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError()
              << std::endl;
    return 1;
  }

  // 6. Initialize GLEW
  glewExperimental = GL_TRUE;
  if (glewInit() != GLEW_OK) {
    std::cerr << "Failed to initialize GLEW" << std::endl;
    return 1;
  }

  Model_Loader model{"../resource/", "cube.obj"};
  model.loadModel();
  model.vboSetup();

  // 10. Main Loop
  bool quit = false;
  SDL_Event e;
  float rotation = 0.0f;

  std::cout << "Rendering started. Using XWayland bridge on Hyprland."
            << std::endl;

  while (!quit) {
    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT)
        quit = true;
    }

    masterWindow.renderStart();
    // Set Project Matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMultMatrixf(userCamera.getDefaultProjectionMatrix());
    // Setup matrix for cube:while
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -5.0f);                 // Move cube 5 units away
    glRotatef(rotation * 0.5, rotation, 1.0f, 0.0f); // Spin on Y axis
    // glRotatef(rotation * 0.5f, 1.0f, 0.0f, 0.0f); // Spin on X axis
    rotation += 0.5f;
    model.renderModel();

    masterWindow.renderEnd();
  }

  // Cleanup
  masterWindow.cleanup();
  model.cleanup();

  return 0;
}
