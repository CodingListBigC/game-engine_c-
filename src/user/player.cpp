#include "player.h"
#include <algorithm>
#include <cmath>
#include <glm/ext/vector_float3.hpp>
#include <iostream>
#include <utility>

Player::Player(const std::string _username) : username(std::move(_username)) {}
Player::Player(std::string _username, RGB_Control &_defaultColor)
    : username(std::move(_username)), defaultColor(_defaultColor) {}

Player::~Player() {
  username = "testDummy";
  defaultColor = {0, 0, 0};
  // Destructor logic
}
float wrapAngle(float angle) {
  // fmod handles floating point numbers
  float result = fmod(angle, 360.0f);
  if (result < 0)
    result += 360.0f;
  return result;
}

void Player::changePosition(glm::vec3 changePosition) {
  this->position.x += changePosition.x;
  this->position.y += changePosition.y;
  this->position.z += changePosition.z;
};
void Player::changeRotation(glm::vec3 changeRotation) {
  this->rotation.x += changeRotation.x;
  this->rotation.y += changeRotation.y;
  this->rotation.z += changeRotation.z;

  float headTurnAmount = 50.0f;
  this->rotation.x =
      std::clamp(this->rotation.x, -headTurnAmount / 2, headTurnAmount / 2);
  this->rotation.y = wrapAngle(this->rotation.y);
  this->rotation.z = wrapAngle(this->rotation.z);

  std::cout << "x: " << this->rotation.x << "\n";
  std::cout << "y: " << this->rotation.y << "\n";
  std::cout << "z: " << this->rotation.z << "\n";
};
