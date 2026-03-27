#include "keyboard.h"
#include <iostream>

std::unordered_map<int, bool> Keyboard::currentKeys;
std::unordered_map<int, bool> Keyboard::previousKeys;

void Keyboard::update() {
  // Move current states to previous before the next poll
  previousKeys = currentKeys;
}

void Keyboard::setKeyState(int keyCode, bool pressed) {
  currentKeys[keyCode] = pressed;
}

bool Keyboard::isKeyDown(int keyCode) { return currentKeys[keyCode]; }

bool Keyboard::isKeyPressed(int keyCode) {
  return currentKeys[keyCode] && !previousKeys[keyCode];
}

bool Keyboard::isKeyReleased(int keyCode) {
  return !currentKeys[keyCode] && previousKeys[keyCode];
}
