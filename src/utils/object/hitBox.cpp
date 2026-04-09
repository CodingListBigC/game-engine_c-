#include "hitBox.h"
#include "../../models/myObjLoader.h"
#include <algorithm>
#include <iostream>

bool debugStatus = false;

void Hit_Box::updateHitBox(std::vector<MeshData> &meshData) {
  updateLastHitBox();

  float minX = 0;
  float maxX = 0;
  float minY = 0;
  float maxY = 0;
  float minZ = 0;
  float maxZ = 0;
  for (auto &mesh : meshData) {

    for (size_t i = 0; i < mesh.vertices.size() / 3; i++) {
      if (debugStatus) {
        std::cout << "Vertex: " << std::endl;
        std::cout << "	X: " << mesh.vertices[i * 3 + 0] << std::endl;
        std::cout << "	Y: " << mesh.vertices[i * 3 + 1] << std::endl;
        std::cout << "	Z: " << mesh.vertices[i * 3 + 2] << std::endl;
      }
      float x = mesh.vertices[i * 3];
      float y = mesh.vertices[i * 3 + 1];
      float z = mesh.vertices[i * 3 + 2];
      // Get Min Values
      minX = std::min(x, minX);
      minY = std::min(y, minY);
      minZ = std::min(z, minZ);

      // Get Max Values
      maxX = std::max(x, maxX);
      maxY = std::max(y, maxY);
      maxZ = std::max(z, maxZ);
    }
  }
  this->currentHitBox[0] = minX;
  this->currentHitBox[1] = minY;
  this->currentHitBox[2] = minZ;
  this->currentHitBox[3] = maxX;
  this->currentHitBox[4] = maxY;
  this->currentHitBox[5] = maxZ;
  if (debugStatus) {
    debug();
  }
};
void Hit_Box::updateLastHitBox() {
  for (int i = 0; i < 6; i++) {
    this->lastHitBox[i] = this->currentHitBox[i];
  }
};
void Hit_Box::deletePartOfHitBox(std::vector<MeshData> &vertex_data) {};
void Hit_Box::addPartOfHitBox(std::vector<MeshData> &vertex_data) {};

Hit_Box::Hit_Box(std::vector<MeshData> &meshData) { updateHitBox(meshData); }
Hit_Box::~Hit_Box() {
  // Destructor logic
}

void Hit_Box::debug() {
  std::cout << "Current Hit Box:" << std::endl;
  std::cout << "	Min X: " << this->currentHitBox[0] << std::endl;
  std::cout << "	Min Y: " << this->currentHitBox[1] << std::endl;
  std::cout << "	Min Z: " << this->currentHitBox[2] << std::endl;
  std::cout << "	Max X: " << this->currentHitBox[3] << std::endl;
  std::cout << "	Max Y: " << this->currentHitBox[4] << std::endl;
  std::cout << "	Max Z: " << this->currentHitBox[5] << std::endl;
}
