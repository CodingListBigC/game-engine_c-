#ifndef OBJ_LOADER_H
#define OBJ_LOADER_H

#include "../manger/ui/shape/settings.h"
#include "../utils/color/rgb_control.h"
#include <GL/glew.h>
#include <string>
#include <vector>
class Model_Loader {
private:
  // Add model data settings
  std::string mainFolder = "../resource/";
  std::string objFileName = "cube.obj";
  std::vector<float> vertex_data;
  GLuint vbo;

public:
  Model_Loader(std::string mainFolderInput, std::string objFileNameInput);

  void loadModel();
  // Vbo Functions
  void vboSetup();
  void renderModel();

  // Clean up model data
  void cleanup();
};

#endif
