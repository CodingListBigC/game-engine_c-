
#ifndef MY_OBJ_LOADER_H
#define MY_OBJ_LOADER_H
#include <istream>
#pragma once

#include "../utils/object/transform.h"
#include <vector>

#include <string>

// Simple struct to hold only what we need for rendering
struct MeshData {
  std::vector<float> vertices;
};
class My_Obj_Loader {
public:
  My_Obj_Loader();
  My_Obj_Loader(std::string _filePath);

  ~My_Obj_Loader();
  void init();
  void renderObject();
  void drawInternal();

private:
  Transform objectTransform{};
  bool loadout;
  std::string filePath = "./resource/cube.obj";
  std::vector<MeshData> meshes;
};

#endif // MY_OBJ_LOADER_H
