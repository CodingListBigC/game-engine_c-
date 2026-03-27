#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <iostream>
#include <unordered_map>

class Keyboard {
public:
  // Update should be called once per frame at the start of your loop
  static void update();

  // Key State Functions
  static bool isKeyDown(int keyCode);     // Is it currently pressed?
  static bool isKeyPressed(int keyCode);  // Was it JUST pressed this frame?
  static bool isKeyReleased(int keyCode); // Was it JUST released this frame?

  // Called by your windowing library (GLFW, SDL, etc.)
  static void setKeyState(int keyCode, bool pressed);

  static std::unordered_map<int, bool> currentKeys;
  static std::unordered_map<int, bool> previousKeys;

private:
};

#endif // KEYBOARD_H
