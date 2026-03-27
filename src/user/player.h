#ifndef PLAYER_H
#define PLAYER_H
#include "../utils/color/rgb_control.h"
#include <glm/ext/vector_float3.hpp>
#include <glm/vec3.hpp>

class Player {
public:
  Player(std::string _username);
  Player(std::string _username, RGB_Control &_defaultColor);
  ~Player();

private:
  std::string username = "testDummy";
  std::string password = "22002";
  RGB_Control defaultColor{0, 0, 0};
  glm::vec3 position{0, 0, 0};
};
