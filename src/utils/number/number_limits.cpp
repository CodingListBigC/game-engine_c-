#include "number_limits.h"
#include <algorithm>

Number_Limits::Number_Limits(int inputMin, int inputMax)
    : min(inputMin), max(inputMax) {}
Number_Limits::Number_Limits(int inputMin, int inputMax, int currentValue)
    : min(inputMin), max(inputMax), currentValue(currentValue) {}

void Number_Limits::setMin(float inputMin) {
  min = inputMin;
  checkInfinite();
};

void Number_Limits::setMax(float inputMax) {
  max = inputMax;
  checkInfinite();
};

// Change Values
void Number_Limits::addValue(float amount) {
  currentValue += amount;
  checkLimits();
};
void Number_Limits::subtractValue(float amount) {
  currentValue -= amount;
  checkLimits();
};

void Number_Limits::roundValue() {
  int amountToMin = currentValue - min;
  int amountToMax = max - currentValue;
  if (amountToMin < amountToMax) {
    currentValue = this->max;
  } else if (amountToMin > amountToMax) {
    currentValue = this->min;
  } else {
    currentValue = (this->max - this->min) / 2;
  }
}

void Number_Limits::checkLimits() {
  if (this->infiniteMin && this->infiniteMax) {
    this->currentValue = std::clamp(this->currentValue, this->min, this->max);
    return;
  }
  if (!this->infiniteMin) {
    if (this->currentValue < this->min) {
      this->currentValue = this->min;
    }
  } else if (!this->infiniteMax) {
    if (this->currentValue > this->max) {
      this->currentValue = this->max;
    }
  }
}

void Number_Limits::checkInfinite() {
  this->infiniteMin = (this->min <= this->max);
  this->infiniteMax = (this->min >= this->max);
}
