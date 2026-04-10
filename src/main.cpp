#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <filesystem>
#include <glm/ext/vector_float3.hpp>
#include <glm/gtc/matrix_transform.hpp> // Added for rotate/translate
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <json/json.h>
#include <vector>

// Own Libs
#include "./manger/inputs/inputMaster.h"
#include "./manger/ui/font/FontRenderer.h"
#include "./manger/ui/shape/rectangle.h"
#include "./manger/window.h"
#include "./models/myObjLoader.h"
#include "./user/camera.h"
#include "./user/player.h"
#include "./utils/fileLoad/readJson.h"
#include "./utils/string.h"

// Renamed to applyCamera to better reflect its purpose
void applyCamera(const Player &player) {
  const float PLAYER_HEIGHT = 2.0f;
  float eyeHeight = PLAYER_HEIGHT * 0.85f;

  glm::vec3 pos = player.getPosition();
  glm::vec3 rot = player.getRotation();

  // 1. Start with an Identity Matrix
  glm::mat4 view = glm::mat4(1.0f);

  // 2. Rotate Pitch (X-axis) - Negative for standard FPS look
  view = glm::rotate(view, glm::radians(-rot.x), glm::vec3(1, 0, 0));

  // 3. Rotate Yaw (Y-axis)
  view = glm::rotate(view, glm::radians(rot.y), glm::vec3(0, 1, 0));

  // 4. Translate the world opposite to player position
  view = glm::translate(view, glm::vec3(-pos.x, -(pos.y + eyeHeight), -pos.z));

  // 5. Apply to OpenGL MODELVIEW
  glMatrixMode(GL_MODELVIEW);
  glLoadMatrixf(glm::value_ptr(view));
}

int main(int argc, char *argv[]) {
  Window masterWindow;

  // 1. Initialize Window First
  if (masterWindow.init() != 0) { // Assuming 0 is success
    std::cerr << "Window could not be created!" << std::endl;
    return 1;
  }

  // 2. Initialize GLEW immediately after context creation
  glewExperimental = GL_TRUE;
  if (glewInit() != GLEW_OK) {
    std::cerr << "Failed to initialize GLEW" << std::endl;
    return 1;
  }

  // 3. Now initialize objects that use OpenGL
  User_Camera userCamera{};
  FontRenderer fontRenderer{};
  fontRenderer.init(
      "../resource/font/jetBrainsMono/JetBrainsMonoNerdFontMono-Regular.ttf",
      24);

  Json::Value playerData = getJsonData("../resource/user/mainUser.json");
  Player player{playerData["username"].asString()};
  Input_Master inputMaster{};

  My_Obj_Loader model{"../resource/model/cube/cube.obj",
                      "../resource/model/cube/Cube.png"};

  bool quit = false;
  SDL_Event e;

  std::cout << "Rendering started. Using XWayland bridge on Hyprland."
            << std::endl;

  while (!quit) {
    // --- INPUT HANDLING ---
    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT)
        quit = true;
      inputMaster.setInput(e);
    }

    inputMaster.update(); // Update timers/deltas
    inputMaster.checkInputs(player.getRotation());

    player.changePosition(inputMaster.getPlayerMoveAmount());
    player.changeRotation(inputMaster.getPlayerRotationAmount());

    // --- RENDER 3D ---
    masterWindow.renderStart();
    glEnable(GL_DEPTH_TEST);

    // Set Projection Matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMultMatrixf(userCamera.getDefaultProjectionMatrix());

    // Setup View (Camera)
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glPushMatrix(); // Save identity
    applyCamera(player);
    model.renderObject(); // Cube is rendered relative to camera
    glPopMatrix();        // Restore identity

    // --- RENDER 2D UI ---
    glDisable(GL_DEPTH_TEST);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0, 800, 600, 0, -1, 1); // Standard 800x600 UI space

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    fontRenderer.renderText(U"\uf007 User: " + to_utf32(player.getUsername()),
                            20.0f, 40.0f, 1.0f, glm::vec3(1.0f, 0.5f, 0.0f));
    fontRenderer.renderText(U"FPS: 60", 20.0f, 80.0f, 0.8f, glm::vec3(1.0f));

    glColor3f(0.2f, 0.6f, 1.0f);
    drawFilledRoundedRect(50, 120, 200, 100, 20, 16);
    glPopMatrix();

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    masterWindow.renderEnd();
  }

  masterWindow.cleanup();
  return 0;
}
