#ifndef MESH_DATA_H
#define MESH_DATA_H

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

#endif
