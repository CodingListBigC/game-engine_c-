
#ifndef MY_OBJ_LOADER_H
#define MY_OBJ_LOADER_H

#include "../utils/object/customStructs.h"
#include "../utils/object/hitBox.h"
#include "../utils/object/transform.h"
#include <GL/glew.h>
#include <istream>
#include <string>
#include <vector>
#pragma once

// Class is mange a obj model and all of it properitys.
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

  std::vector<MeshData> getMeshData() { return this->meshes; };

  HitBox getDefaultHitBox();

private:
  Transform objectTransform{};
  bool loadout;
  std::string filePath = "";
  std::string imagePath = "";
  std::vector<MeshData> meshes;

  Hit_Box modelHitBox{};
};

#endif // MY_OBJ_LOADER_H
