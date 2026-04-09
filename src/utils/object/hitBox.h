#ifndef HIT_BOX_H
#define HIT_BOX_H

#include "meshData.h"
#include "transform.h"
#include <vector>

class Hit_Box {
public:
  Hit_Box();
  Hit_Box(std::vector<MeshData> &vertex_data);
  ~Hit_Box();
  void updateHitBox(std::vector<MeshData> &vertex_data);
  void updateLastHitBox();
  void deletePartOfHitBox(std::vector<MeshData> &vertex_data);
  void addPartOfHitBox(std::vector<MeshData> &vertex_data);
  void debug();

  HitBox getCurrentHitBox();
  HitBox getCurrentHitBox(Transform &transform);

private:
  HitBox currentHitBox{0, 0, 0, 0, 0, 0};
  HitBox lastHitBox;
};

#endif // HIT_BOX_H
