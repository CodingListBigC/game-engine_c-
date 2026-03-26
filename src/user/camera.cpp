#include "camera.h"
User_Camera::User_Camera() {}
float *User_Camera::getDefaultProjectionMatrix() {
  float f = 1.0f / std::tan(fov * (float)M_PI / 360.0f);

  // Fill the matrix array (Column-Major Order)
  matrix[0] = f / aspect;
  matrix[1] = 0;
  matrix[2] = 0;
  matrix[3] = 0;
  matrix[4] = 0;
  matrix[5] = f;
  matrix[6] = 0;
  matrix[7] = 0;
  matrix[8] = 0;
  matrix[9] = 0;
  matrix[10] = (zFar + zNear) / (zNear - zFar);
  matrix[11] = -1;
  matrix[12] = 0;
  matrix[13] = 0;
  matrix[14] = (2 * zFar * zNear) / (zNear - zFar);
  matrix[15] = 0;

  return matrix;
}
