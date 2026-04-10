#ifndef DEFAULT_ITEM_MANAGER_H
#define DEFAULT_ITEM_MANAGER_H

#include "../../models/myObjLoader.h"
#include "../../utils/object/hitBox.h"
#include <vector>

template <typename t>

class Default_Item_Manager {
public:
  Default_Item_Manager();
  ~Default_Item_Manager();
  // Checkers
  bool checkCollison(const Hit_Box &hitbox);
  bool checkIndex(int index);

  // Adders
  void addItem(t &newItem);
  // Getters
  Hit_Box &getHitBox(int index);
  My_Obj_Loader &getModel(int index);

  // Destorys
  void destryItme(int index);

  // Render

private:
  std::vector<t> objectList;
};

#endif // DEFAULT_ITEM_MANAGER_H
