#ifndef PLAYER_H
#define PLAYER_H
#include "../utils/color/rgb_control.h"
#include <glm/ext/vector_float3.hpp>
#include <glm/vec3.hpp>

class Player {
public:
  // Constustor
  Player(std::string _username);
  Player(std::string _username, RGB_Control &_defaultColor);
  ~Player();

  // Getters
  std::string getUsername() const { return this->username; };
  glm::vec3 getPosition() const { return this->position; };
  glm::vec3 getRotation() const { return this->rotation; };
  void changePosition(glm::vec3 changePos);
  void changeRotation(glm::vec3 changeRot);

private:
  std::string username = "testDummy";
  std::string password = "22002";
  RGB_Control defaultColor{0, 0, 0};
  glm::vec3 position{0, 0, 0};
  glm::vec3 rotation{0, 0, 0};
};

#endif
