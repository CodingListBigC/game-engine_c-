#include "player.h"
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
