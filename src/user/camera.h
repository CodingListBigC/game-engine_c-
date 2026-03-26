#ifndef USER_CAMERA_H
#define USER_CAMERA_H

#include <cmath>
#include <istream>
class User_Camera {
private:
  float aspect = 800.0f / 600.0f;
  float fov = 45.0f;
  float zNear = 0.1f;
  float zFar = 100.0f;
  float f = 1.0f / tan(fov * M_PI / 360.0f);
  float matrix[16];

public:
  User_Camera();
  float *getDefaultProjectionMatrix();
};

#endif
