#include "player.h"
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

void Player::changePosition(glm::vec3 changePosition) {
  this->position.x += changePosition.x;
  this->position.y += changePosition.y;
  this->position.z += changePosition.z;
};
