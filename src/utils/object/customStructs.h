#ifndef CUSTOM_STRUCTS_H
#define CUSTOM_STRUCTS_H

#include <GL/glew.h>
#include <vector>
struct MeshData {
  std::vector<float> vertices;
  std::vector<float> texCoords;
  GLuint textureID = 0;
};

struct HitBox {
  float minX;
  float maxX;
  float minY;
  float maxY;
  float minZ;
  float maxZ;
};

#endif //  CUSTOM_STRUCTS_H
