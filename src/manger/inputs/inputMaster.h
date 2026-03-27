#ifndef INPUT_MASTER_H
#define INPUT_MASTER_H

#include "inputPlayer.h"
#include "keyboard.h"
#include <SDL2/SDL_events.h>
#include <glm/ext/vector_float3.hpp>

class Input_Master {
public:
  // Constuctor
  Input_Master();
  ~Input_Master();
  void update();
  void setInput(const SDL_Event &e);
  void checkInputs();

  // Get values
  glm::vec3 getPlayerMoveAmount() { return inputPlayer.getMoveAmount(); };

private:
  Input_Player inputPlayer{};
  Keyboard keyboard;

  // Private Inputs
  void checkKeyboardInput();
  void checkLeftClick();
  void checkRightClick();
};

#endif // INPUT_MASTER_H
