#include <cmath>
#include <iostream>

struct Vector3 {
  float x, y, z;

  // Constructors
  Vector3() : x(0), y(0), z(0) {}
  Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
  Vector3(const Vector3 &other) {
    x = other.x;
    y = other.y;
    z = other.z;
  }

  // Operator Overloading: Addition
  Vector3 operator+(const Vector3 &other) const {
    return Vector3(x + other.x, y + other.y, z + other.z);
  }

  // Operator Overloading: Scalar Multiplication
  Vector3 operator*(float scalar) const {
    return Vector3(x * scalar, y * scalar, z * scalar);
  }

  // Method to calculate Magnitude (Length)
  float magnitude() const { return std::sqrt(x * x + y * y + z * z); }

  // Helper to print values
  void print() const {
    std::cout << "Vector3(" << x << ", " << y << ", " << z << ")" << std::endl;
  }
};
