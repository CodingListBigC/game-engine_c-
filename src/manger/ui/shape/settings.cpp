#include "settings.h"

ItemDefaultSetting::ItemDefaultSetting(float xInput, float yInput,
                                       float widthInput, float heightInput)
    : x(xInput), y(yInput), width(widthInput), height(heightInput) {};

void ItemDefaultSetting::setPosition(float xInput, float yInput) {
  this->x = xInput;
  this->y = yInput;
};
void ItemDefaultSetting::setSize(float widthInput, float heightInput) {
  this->width = widthInput;
  this->height = heightInput;
};
