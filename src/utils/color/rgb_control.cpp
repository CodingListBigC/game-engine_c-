#include "rgb_control.h"

RGB_Control::RGB_Control(int red, int green, int blue) {
  this->redValue.setCurrentValue(red);
  this->greenValue.setCurrentValue(green);
  this->blueValue.setCurrentValue(blue);
}

void RGB_Control::editValues(int redAmount, int greenAmount, int blueAmount) {
  redValue.addValue(redAmount);
  greenValue.addValue(greenAmount);
  blueValue.addValue(blueAmount);
}
