#include "inputPlayer.h"
#include "keyboard.h"
#include <SDL2/SDL_keycode.h>
#include <cmath>
#include <glm/detail/qualifier.hpp>
#include <glm/ext/vector_float3.hpp>

Input_Player::Input_Player() {
  // Constructor logic
}

Input_Player::~Input_Player() {
  // Destructor logic
}

void Input_Player::checkKeyboardInput(const Keyboard &keyboard,
                                      glm::vec3 currentRotation) {
  this->checkRotationAmount(keyboard);
  currentRotation.x += this->rotationAmount.x;
  currentRotation.y += this->rotationAmount.y;
  currentRotation.z += this->rotationAmount.z;
  this->checkMoveAmount(keyboard, currentRotation);
}

double toRadians(double degree) {
  const double pi = std::acos(-1.0);
  return degree * (pi / 180.0);
}

void Input_Player::checkMoveAmount(const Keyboard &keyboard,
                                   glm::vec3 currentRotation) {
  float pitch = currentRotation.x;
  float yaw = currentRotation.y;
  // Increase speed
  if (keyboard.isKeyDown(SDLK_LCTRL)) {
    movePlayerAmount *= 10;
  }

  // Change Values
  float dx = 0;
  float dy = 0;
  float dz = 0;

  // Move plaayer x,z
  if (keyboard.isKeyDown(SDLK_w)) {
    dx += std::sin(toRadians(yaw)) * movePlayerAmount;
    dz -= std::cos(toRadians(yaw)) * movePlayerAmount;
  }
  if (keyboard.isKeyDown(SDLK_s)) {
    dx -= std::sin(toRadians(yaw)) * movePlayerAmount;
    dz += std::cos(toRadians(yaw)) * movePlayerAmount;
  }
  if (keyboard.isKeyDown(SDLK_a)) {
    dx -= std::cos(toRadians(pitch)) * movePlayerAmount;
    dz -= std::sin(toRadians(pitch)) * movePlayerAmount;
  }
  if (keyboard.isKeyDown(SDLK_d)) {
    dx += std::cos(toRadians(pitch)) * movePlayerAmount;
    dz += std::sin(toRadians(pitch)) * movePlayerAmount;
  }
  if (keyboard.isKeyDown(SDLK_LSHIFT)) {
    dy -= movePlayerAmount;
  }
  if (keyboard.isKeyDown(SDLK_SPACE)) {
    dy += movePlayerAmount;
  }

  this->moveAmount.x += dx;
  this->moveAmount.y += dy;
  this->moveAmount.z += dz;
}
void Input_Player::checkRotationAmount(const Keyboard &keyboard) {
  // 1. Up/Down should affect the X-axis (Pitch)
  if (keyboard.isKeyDown(SDLK_UP)) {
    this->rotationAmount.x += rotationPlayerAmount;
  }
  if (keyboard.isKeyDown(SDLK_DOWN)) {
    this->rotationAmount.x -= rotationPlayerAmount;
  }

  // 2. Left/Right should affect the Y-axis (Yaw)
  if (keyboard.isKeyDown(SDLK_LEFT)) {
    this->rotationAmount.y -= rotationPlayerAmount;
  }
  if (keyboard.isKeyDown(SDLK_RIGHT)) {
    this->rotationAmount.y += rotationPlayerAmount;
  }

  this->rotationAmount.y = std::fmod(this->rotationAmount.y, 360.0f);
  if (this->rotationAmount.y < 0)
    this->rotationAmount.y += 360.0f;
}

void Input_Player::resetValues() {
  // Move Reset
  this->moveAmount.x = 0;
  this->moveAmount.y = 0;
  this->moveAmount.z = 0;
  this->movePlayerAmount = moveDefualtPlayerAmount;

  // Rotation Reset
  this->rotationAmount.x = 0;
  this->rotationAmount.y = 0;
  this->rotationAmount.z = 0;
  this->rotationPlayerAmount = rotationDefualtPlayerAmount;
}
