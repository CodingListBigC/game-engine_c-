#include "inputMaster.h"
#include "keyboard.h"
#include <SDL2/SDL_events.h>
#include <iostream>

Input_Master::Input_Master() {
  // Constructor logic
}

Input_Master::~Input_Master() {
  // Destructor logic
}

void Input_Master::update() {
  keyboard.update();
  this->inputPlayer.resetValues();
};

void Input_Master::setInput(const SDL_Event &e) {
  switch (e.type) {
  case SDL_KEYDOWN:
    Keyboard::setKeyState(e.key.keysym.sym, true);
    break;
  case SDL_KEYUP:
    Keyboard::setKeyState(e.key.keysym.sym, false);
    break;
  default:
    break;
  }
}

void Input_Master::checkInputs() {
  this->checkKeyboardInput();
  this->checkLeftClick();
  this->checkRightClick();
}
void Input_Master::checkKeyboardInput() {
  this->inputPlayer.checkKeyboardInput(keyboard);
};
void Input_Master::checkLeftClick() {};
void Input_Master::checkRightClick() {};
