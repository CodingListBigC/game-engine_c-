#include "inputPlayer.h"
#include "keyboard.h"
#include <SDL2/SDL_keycode.h>
#include <cstdarg>
#include <iostream>

Input_Player::Input_Player() {
  // Constructor logic
}

Input_Player::~Input_Player() {
  // Destructor logic
}

void Input_Player::checkKeyboardInput(const Keyboard &keyboard) {
  this->checkMoveAmount(keyboard);
  this->checkRotationAmount(keyboard);
}

void Input_Player::checkMoveAmount(const Keyboard &keyboard) {
  if (keyboard.isKeyDown(SDLK_LCTRL)) {
    movePlayerAmount *= 10;
  }

  if (keyboard.isKeyDown(SDLK_w)) {
    this->moveAmount.z -= movePlayerAmount;
  }
  if (keyboard.isKeyDown(SDLK_s)) {
    this->moveAmount.z += movePlayerAmount;
  }
  if (keyboard.isKeyDown(SDLK_a)) {
    this->moveAmount.x -= movePlayerAmount;
  }
  if (keyboard.isKeyDown(SDLK_d)) {
    this->moveAmount.x += movePlayerAmount;
  }
  if (keyboard.isKeyDown(SDLK_LSHIFT)) {
    this->moveAmount.y -= movePlayerAmount;
  }
  if (keyboard.isKeyDown(SDLK_SPACE)) {
    this->moveAmount.y += movePlayerAmount;
  }
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
