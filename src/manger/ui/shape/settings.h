#include "../../../utils/color/rgb_control.h"
#ifndef SETTING_H
#define SETTING_H

class ItemDefaultSetting {
private:
  float x;
  float y;
  float width;
  float height;
  RGB_Control backgroundColor{0, 0, 0};
  RGB_Control outlineColor{0, 0, 0};
  RGB_Control textColor{0, 0, 0};

public:
  ItemDefaultSetting(float xInput, float yInput, float widthInput,
                     float heightInput);

  // Shape Sizes
  //		Getters
  float getXValue() { return this->x; };
  float getYValue() { return this->y; };
  float getWidthValue() { return this->width; };
  float getHeightValue() { return this->height; };
  //		Setters
  void setPosition(float xInput, float yInput);
  void setSize(float widthInput, float heightInput);

  // Color Getters
  RGB_Control getBackgroundColor() { return this->backgroundColor; };
  RGB_Control getOutlineColor() { return this->outlineColor; };
  RGB_Control getTextColor() { return this->textColor; };
};

#endif
