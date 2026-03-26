#ifndef TRANSFORM_OBJECT_H
#define TRANSFORM_OBJECT_H

#include "../units/vector/vector3f.h"

class Transform {
private:
  Vector3 position;
  Vector3 rotation;
  float m_scale;

  bool isDirty;

public:
  Transform()
      : position{0, 0, 0}, rotation{0, 0, 0}, m_scale(1.0f), isDirty(true) {}
  Transform(Vector3 _position, Vector3 _rotation)
      : position{_position}, rotation{_rotation}, m_scale(1.0f), isDirty(true) {
  }

  Transform(const Transform &other) {
    position = other.position;
    rotation = other.rotation;
    m_scale = other.m_scale;
    isDirty = other.isDirty;
  }

  // Method to modify data safely
  void setPosition(float x, float y, float z) {
    position = {x, y, z};
    isDirty = true; // Mark for GPU update
  }

  // Read-only access to the data
  Vector3 getPosition() const { return position; }

  void translate(Vector3 offset) {
    position = position + offset;
    isDirty = true; // Mark for GPU update
  }

  Transform createCopyOnHeap() { return new Transform(*this); }
};

#endif
