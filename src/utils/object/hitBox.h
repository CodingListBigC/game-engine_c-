#ifndef HIT_BOX_H
#define HIT_BOX_H

#include "../../models/myObjLoader.h"
#include <vector>

class Hit_Box {
public:
  Hit_Box(std::vector<MeshData> &vertex_data);
  ~Hit_Box();
  void updateHitBox(std::vector<MeshData> &vertex_data);
  void updateLastHitBox();
  void deletePartOfHitBox(std::vector<MeshData> &vertex_data);
  void addPartOfHitBox(std::vector<MeshData> &vertex_data);
  void debug();

private:
  float currentHitBox[6] = {0, 0, 0, 0, 0, 0};
  float lastHitBox[6];
};

#endif // HIT_BOX_H
