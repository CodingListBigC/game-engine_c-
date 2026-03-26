#ifndef TRANSFORM_OBJECT_H
#define TRANSFORM_OBJECT_H

#include <glm/ext/vector_float3.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
// Assuming your Vector3 is compatible or convertible to glm::vec3
#include "../units/vector/vector3f.h"

class Transform {
private:
  glm::vec3 position;
  glm::vec3 rotation;
  float m_scale;
  bool m_isDirty;
  glm::mat4 cachedMatrix;

  // Helper to convert your custom Vector3 to glm::vec3 for math
  glm::vec3 toGlm(Vector3 v) const { return glm::vec3(v.x, v.y, v.z); }

public:
  // Constructors
  Transform()
      : position{0, 0, 0}, rotation{0, 0, 0}, m_scale(1.0f), m_isDirty(true) {}

  Transform(glm::vec3 _position, glm::vec3 _rotation)
      : position{_position}, rotation{_rotation}, m_scale(1.0f),
        m_isDirty(true) {}

  // Copy Constructor
  Transform(const Transform &other)
      : position(other.position), rotation(other.rotation),
        m_scale(other.m_scale), m_isDirty(true) {
    // We set isDirty to true so the new copy generates its own matrix
  }

  // Setters
  void setPosition(float x, float y, float z) {
    position = {x, y, z};
    m_isDirty = true;
  }

  void translate(glm::vec3 offset) {
    position = position + offset;
    m_isDirty = true;
  }

  // Getters
  glm::vec3 getPosition() const { return position; }

  // FIXED: Return type must be Transform* if using 'new'
  Transform *createCopyOnHeap() { return new Transform(*this); }

  glm::mat4 getModelMatrix() {
    if (m_isDirty) {
      // 1. Identity
      glm::mat4 model = glm::mat4(1.0f);

      // 2. Translate
      model = glm::translate(model, position);

      // 3. Rotate (Example: Euler angles)
      model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1, 0, 0));
      model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0, 1, 0));
      model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0, 0, 1));

      // 4. Scale
      model = glm::scale(model, glm::vec3(m_scale));

      cachedMatrix = model;
      m_isDirty = false;
    }
    return cachedMatrix;
  }
};

#endif
