
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <filesystem>
#include <glm/ext/vector_float3.hpp>
#include <iostream>
#include <vector>
// Own Libs
#include "./manger/ui/font/FontRenderer.h"
#include "./manger/ui/shape/rectangle.h"
#include "./manger/window.h"
#include "./models/obj_loader.h"
#include "./user/camera.h"
#include "./user/player.h"
#include "./utils/string.h"

// Include your tiny_obj_loader here
#define TINYOBJLOADER_IMPLEMENTATION

int main(int argc, char *argv[]) {
  Window masterWindow;
  User_Camera userCamera{};
  FontRenderer fontRenderer{};
  Player player{"Hello"};

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
  fontRenderer.init(
      "../resource/font/jetBrainsMono/JetBrainsMonoNerdFontMono-Regular.ttf",
      24);

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
    glm::vec3 playerPos = player.getPosition();
    glTranslatef(playerPos.x, playerPos.y, playerPos.z);
    glTranslatef(0.0f, 0.0f, -5.0f);                 // Move cube 5 units away
    glRotatef(rotation * 0.5, rotation, 1.0f, 0.0f); // Spin on Y axis
    // glRotatef(rotation * 0.5f, 1.0f, 0.0f, 0.0f); // Spin on X axis
    rotation += 0.5f;
    model.renderModel();

    glDisable(GL_DEPTH_TEST); // UI shouldn't hide behind 3D objects

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0, 800, 900, 0, -1, 1); // Top-left is (0,0)

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    // Draw Text and Icons
    // Note: \uf007 = 
    fontRenderer.renderText(U"\uf007 User: " + to_utf32(player.getUsername()),
                            20.0f, 40.0f, 1.0f, glm::vec3(1.0f, 0.5f, 0.0f));
    fontRenderer.renderText(U"FPS: 60", 20.0f, 80.0f, 0.8f, glm::vec3(1.0f));

    glColor3f(0.2f, 0.6f, 1.0f); // Set color to a nice blue
    drawFilledRoundedRect(50, 100, 200, 200, 20, 16);

    // Restore Matrix State
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    glEnable(GL_DEPTH_TEST);

    masterWindow.renderEnd();
  }

  // Cleanup
  masterWindow.cleanup();
  model.cleanup();

  return 0;
}
