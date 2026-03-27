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
  if (keyboard.isKeyDown(SDLK_w)) {
    this->moveAmount.z += movePlayerAmount;
  }
  if (keyboard.isKeyDown(SDLK_s)) {
    this->moveAmount.z -= movePlayerAmount;
  }
  if (keyboard.isKeyDown(SDLK_a)) {
    this->moveAmount.x += movePlayerAmount;
  }
  if (keyboard.isKeyDown(SDLK_d)) {
    this->moveAmount.x -= movePlayerAmount;
  }
  if (keyboard.isKeyDown(SDLK_LSHIFT)) {
    this->moveAmount.y += movePlayerAmount;
  }
  if (keyboard.isKeyDown(SDLK_SPACE)) {
    this->moveAmount.y -= movePlayerAmount;
  }
}

void Input_Player::resetValues() {
  this->moveAmount.x = 0;
  this->moveAmount.y = 0;
  this->moveAmount.z = 0;
  this->movePlayerAmount = moveDefualtPlayerAmount;
}
