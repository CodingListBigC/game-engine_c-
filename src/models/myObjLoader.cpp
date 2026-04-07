#include "myObjLoader.h"
#include <GL/glew.h>
#include <iostream>

#include "../include/OBJ_Loader.h"
#include "../utils/texture/textureLoader.h"
#include <glm/gtc/type_ptr.hpp>
#include <ostream>

My_Obj_Loader::My_Obj_Loader(std::string _filePath, std::string _imagePath)
    : filePath(_filePath), imagePath(_imagePath) {
  this->init();
}

My_Obj_Loader::~My_Obj_Loader() {}

void My_Obj_Loader::init() {
  this->initModel();
  this->initTexture();
}

void My_Obj_Loader::initModel() {
  objl::Loader loader;
  this->loadout = loader.LoadFile(this->filePath);

  if (this->loadout) {
    for (auto &mesh : loader.LoadedMeshes) {
      MeshData data;
      // We loop through Indices (36 for a cube) not Vertices (8)
      for (unsigned int i = 0; i < mesh.Indices.size(); i++) {
        unsigned int index = mesh.Indices[i];
        objl::Vertex vertex = mesh.Vertices[index];

        // Position (x, y, z)
        data.vertices.push_back(vertex.Position.X);
        data.vertices.push_back(vertex.Position.Y);
        data.vertices.push_back(vertex.Position.Z);

        // UV (u, v) - Now perfectly aligned 1-to-1 with position
        data.texCoords.push_back(vertex.TextureCoordinate.X);
        data.texCoords.push_back(vertex.TextureCoordinate.Y);
      }
      this->meshes.push_back(data);
    }
  }

  this->objectTransform.setPosition(0.0f, 0.0f, -10.0f);
}

void My_Obj_Loader::initTexture() {
  if (!this->loadout) {
    return;
  }
  GLuint texID = loadTextureCached(this->imagePath.c_str());
  for (auto &mesh : this->meshes) {
    mesh.textureID = texID;
  }
}

void My_Obj_Loader::renderObject() {

  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glMultMatrixf(glm::value_ptr(this->objectTransform.getModelMatrix()));
  this->drawInternal();
  glPopMatrix();
}

void My_Obj_Loader::drawInternal() {
  glEnable(GL_TEXTURE_2D); // 1. Tell OpenGL to use 2D textures

  for (auto &mesh : meshes) {
    if (mesh.vertices.empty())
      continue;
    glBindTexture(GL_TEXTURE_2D, mesh.textureID); // 2. Select the image

    glBegin(GL_TRIANGLES);
    for (size_t i = 0; i < mesh.vertices.size() / 3; i++) {
      // 3. Set the UV (Where on the image?)
      // We use i * 2 because UVs are pairs (u, v)
      glTexCoord2f(mesh.texCoords[i * 2], mesh.texCoords[i * 2 + 1]);

      // 4. Set the Vertex (Where in the world?)
      glVertex3f(mesh.vertices[i * 3], mesh.vertices[i * 3 + 1],
                 mesh.vertices[i * 3 + 2]);
    }
    glEnd();
  }

  glDisable(GL_TEXTURE_2D); // Clean up
}
