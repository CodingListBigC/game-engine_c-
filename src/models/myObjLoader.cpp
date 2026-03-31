#include "myObjLoader.h"
#include <GL/glew.h>
#include <iostream>

#include "../include/OBJ_Loader.h"
#include <glm/gtc/type_ptr.hpp>

My_Obj_Loader::My_Obj_Loader(std::string _filePath) : filePath(_filePath) {
  this->init();
}

My_Obj_Loader::~My_Obj_Loader() { this->init(); }

void My_Obj_Loader::init() {
  std::cout << "Attempting to load: " << this->filePath << std::endl;

  objl::Loader loader;
  this->loadout = loader.LoadFile(this->filePath);

  if (this->loadout) {
    // Accessing the data
    for (auto mesh : loader.LoadedMeshes) {
      MeshData data;
      for (auto &vert : mesh.Vertices) {
        data.vertices.push_back(vert.Position.X);
        data.vertices.push_back(vert.Position.Y);
        data.vertices.push_back(vert.Position.Z);
      }
      this->meshes.push_back(data);
    }
  } else {
    std::cerr << "Failed to load model.\n";
  }

  // Setting Object Location
  this->objectTransform.setPosition(0.0f, 0.0f, -10.0f);
  this->objectTransform.debug();
}
void My_Obj_Loader::renderObject() {

  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glMultMatrixf(glm::value_ptr(this->objectTransform.getModelMatrix()));
  glPopMatrix();
}

void My_Obj_Loader::drawInternal() {
  glBegin(GL_TRIANGLES);
  for (auto &mesh : meshes) {
    for (size_t i = 0; i < mesh.vertices.size(); i += 3) {
      glVertex3f(mesh.vertices[i], mesh.vertices[i + 1], mesh.vertices[i + 2]);
    }
  }
  glEnd();
}
