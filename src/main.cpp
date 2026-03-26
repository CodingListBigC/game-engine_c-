#include "./manger/window.h"
#include "./models/obj_loader.h"
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <filesystem>
#include <iostream>
#include <vector>

// Include your tiny_obj_loader here
#define TINYOBJLOADER_IMPLEMENTATION

int main(int argc, char *argv[]) {
  Window masterWindow;
  if (masterWindow.init() == 1) {
    std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError()
              << std::endl;
    return 1;
  }

  Model_Loader model{"../resource/", "cube.obj"};
  model.loadModel();
  model.vboSetup();
  // 6. Initialize GLEW
  glewExperimental = GL_TRUE;
  if (glewInit() != GLEW_OK) {
    std::cerr << "Failed to initialize GLEW" << std::endl;
    return 1;
  }

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

    // Simple Perspective: FOV 45deg, Aspect 4/3, Near 0.1, Far 100
    float aspect = 800.0f / 600.0f;
    float fov = 45.0f;
    float zNear = 0.1f;
    float zFar = 100.0f;
    float f = 1.0f / tan(fov * (M_PI / 360.0f));
    float projMat[16] = {f / aspect,
                         0,
                         0,
                         0,
                         0,
                         f,
                         0,
                         0,
                         0,
                         0,
                         (zFar + zNear) / (zNear - zFar),
                         -1,
                         0,
                         0,
                         (2.0f * zFar * zNear) / (zNear - zFar),
                         0};
    glMultMatrixf(projMat);

    // --- SETUP MODELVIEW (The "Object Position") ---
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -5.0f);              // Move cube 5 units away
    glRotatef(rotation, 0.0f, 1.0f, 0.0f);        // Spin on Y axis
    glRotatef(rotation * 0.5f, 1.0f, 0.0f, 0.0f); // Spin on X axis
    rotation += 0.5f;
    model.renderModel();

    masterWindow.renderEnd();
  }

  // Cleanup
  masterWindow.cleanup();
  model.cleanup();

  return 0;
}
