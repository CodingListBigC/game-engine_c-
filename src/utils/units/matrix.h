#ifndef MATRIX_HEADER
#define MATRIX_HEADER

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

/**
 * Cleaned up Transform function.
 * Note: GLM matrices are Column-Major by default, which matches OpenGL.
 */
inline glm::mat4 calculateTransform(glm::vec3 position, glm::vec3 rotationEuler,
                                    glm::vec3 scale) {
  // 1. Start with an Identity Matrix
  glm::mat4 model = glm::mat4(1.0f);

  // 2. Translate (Move)
  model = glm::translate(model, position);

  // 3. Rotate (Order: Y -> X -> Z is common to avoid Gimbal Lock,
  // but X -> Y -> Z is fine for basic needs)
  model = glm::rotate(model, glm::radians(rotationEuler.x),
                      glm::vec3(1.0f, 0.0f, 0.0f));
  model = glm::rotate(model, glm::radians(rotationEuler.y),
                      glm::vec3(0.0f, 1.0f, 0.0f));
  model = glm::rotate(model, glm::radians(rotationEuler.z),
                      glm::vec3(0.0f, 0.0f, 1.0f));

  // 4. Scale
  model = glm::scale(model, scale);

  return model;
}

#endif
