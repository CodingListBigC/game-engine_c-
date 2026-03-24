#include "../number/number_limits.h"
#include <filesystem>

#ifndef RGB_CONTROL
#define RGB_CONTROL

class RGB_Control {
private:
  Number_Limits redValue{0, 255};
  Number_Limits greenValue{0, 255};
  Number_Limits blueValue{0, 255};

public:
  RGB_Control(int redValue, int greenValue, int blueValue);

  float getRedValue() const { return redValue.getCurrentValue(); };
  float getGreenValue() const { return greenValue.getCurrentValue(); };
  float getBlueValue() const { return blueValue.getCurrentValue(); };

  void editValues(int redAmount, int greenAmount, int blueAmount);
};

#endif
