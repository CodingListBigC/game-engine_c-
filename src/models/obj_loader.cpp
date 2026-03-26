#include "obj_loader.h"
#define TINYOBJLOADER_IMPLEMENTATION
#include "../include/tiny_obj_loader.h"
#include <GL/glew.h>
#include <iostream>
#include <vector>

Model_Loader::Model_Loader(std::string mainFolderInput,
                           std::string objFileNameInput)
    : mainFolder(mainFolderInput), objFileName(objFileNameInput) {};

void Model_Loader::loadModel() {
  tinyobj::ObjReader reader;
  std::string inputfile = this->mainFolder + this->objFileName;
  if (!reader.ParseFromFile(inputfile)) {
    std::cerr << "TinyObj Error: " << reader.Error();
    exit(1);
  }

  auto &attrib = reader.GetAttrib();
  auto &shapes = reader.GetShapes();

  for (const auto &shape : shapes) {
    for (const auto &index : shape.mesh.indices) {
      this->vertex_data.push_back(attrib.vertices[3 * index.vertex_index + 0]);
      this->vertex_data.push_back(attrib.vertices[3 * index.vertex_index + 1]);
      this->vertex_data.push_back(attrib.vertices[3 * index.vertex_index + 2]);
    }
  }
}

void Model_Loader::vboSetup() {
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, this->vertex_data.size() * sizeof(float),
               this->vertex_data.data(), GL_STATIC_DRAW);
}

void Model_Loader::renderModel() {
  // TODO: Add model matrix and add location and position
  // --- DRAW CUBE ---
  glColor3f(1.0f, 0.5f, 0.0f); // Oarchy Orange color
  glEnableClientState(GL_VERTEX_ARRAY);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glVertexPointer(3, GL_FLOAT, 0, 0);

  glDrawArrays(GL_TRIANGLES, 0, vertex_data.size() / 3);

  glDisableClientState(GL_VERTEX_ARRAY);
}

void Model_Loader::cleanup() { glDeleteBuffers(1, &vbo); };
