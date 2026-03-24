#include "settings.h"

Setting::Setting(float xInput, float yInput, float widthInput,
                 float heightInput)
    : x(xInput), y(yInput), width(widthInput), height(heightInput) {};

void Setting::setPosition(float xInput, float yInput) {
  this->x = xInput;
  this->y = yInput;
};
void Setting::setSize(float widthInput, float heightInput) {
  this->width = widthInput;
  this->height = heightInput;
};
