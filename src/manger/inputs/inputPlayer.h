#ifndef INPUT_PLAYER_H
#define INPUT_PLAYER_H

#include "keyboard.h"
#include <glm/vec3.hpp>

class Input_Player {
public:
  // Constuctor
  Input_Player();
  ~Input_Player();
  // Check inputs
  void checkKeyboardInput(const Keyboard &keyboard);
  // Reset values
  void resetValues();
  // Get Values
  glm::vec3 getMoveAmount() { return this->moveAmount; };

private:
  glm::vec3 moveAmount{0, 0, 0};
  const float moveDefualtPlayerAmount = 0.05;
  float movePlayerAmount = moveDefualtPlayerAmount;
};

#endif // INPUT_PLAYER_H
