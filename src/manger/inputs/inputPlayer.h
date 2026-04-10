#ifndef INPUT_PLAYER_H
#define INPUT_PLAYER_H

#include "keyboard.h"
#include <glm/detail/qualifier.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/vec3.hpp>

class Input_Player {
public:
  // Constuctor
  Input_Player();
  ~Input_Player();
  // Check inputs
  void checkKeyboardInput(const Keyboard &keyboard, glm::vec3 currentRotation);
  // Reset values
  void resetValues();
  // Get Values
  glm::vec3 getMoveAmount() { return this->moveAmount; };
  glm::vec3 getRotationAmount() { return this->rotationAmount; };

private:
  glm::vec3 moveAmount{0, 0, 0};
  const float moveDefualtPlayerAmount = 0.05;
  float movePlayerAmount = moveDefualtPlayerAmount;
  glm::vec3 rotationAmount{0, 0, 0};
  const float rotationDefualtPlayerAmount = 1;
  float rotationPlayerAmount = rotationDefualtPlayerAmount;

  void checkMoveAmount(const Keyboard &keyboard, glm::vec3 currentRotation);
  void checkRotationAmount(const Keyboard &keyboard);
};

#endif // INPUT_PLAYER_H
