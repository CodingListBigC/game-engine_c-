#ifndef NUMBER_LIMITS
#define NUMBER_LIMITS

#include <charconv>
class Number_Limits {
private:
  bool infiniteMin = false;
  bool infiniteMax = false;
  float min = 0;
  float max = 0;
  float currentValue;

public:
  Number_Limits(int min, int max);
  Number_Limits(int min, int max, int currentValue);
  // Setters
  void setMin(float inputMin);
  void setMax(float inputMax);
  void setCurrentValue(float value) {
    this->currentValue = value;
    checkLimits();
  }

  // Getters
  float getCurrentValue() const { return currentValue; };

  // Values Edits
  void addValue(float value);
  void subtractValue(float value);
  void roundValue();
  void checkLimits();
  void checkInfinite();
};

#endif
