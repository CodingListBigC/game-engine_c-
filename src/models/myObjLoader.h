
#ifndef MY_OBJ_LOADER_H
#define MY_OBJ_LOADER_H
#include <istream>
#pragma once

#include "../utils/object/transform.h"
#include <GL/glew.h>
#include <vector>

#include <string>

// Simple struct to hold only what we need for rendering
struct MeshData {
  std::vector<float> vertices;
  std::vector<float> texCoords;
  GLuint textureID = 0;
};
class My_Obj_Loader {
public:
  My_Obj_Loader();
  My_Obj_Loader(std::string _filePath, std::string _imagePath);

  ~My_Obj_Loader();
  void init();
  void initModel();
  void initTexture();
  void renderObject();
  void drawInternal();

private:
  Transform objectTransform{};
  bool loadout;
  std::string filePath = "";
  std::string imagePath = "";
  std::vector<MeshData> meshes;
};

#endif // MY_OBJ_LOADER_H
