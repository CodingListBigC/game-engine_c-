#ifndef MODEL_MANGER_MASTER_H
#define MODEL_MANGER_MASTER_H

#include "../../models/myObjLoader.h"
#include "../../utils/object/hitBox.h"
#include "defualtItemManger.h"

class Model_Manger_Master {
public:
  Model_Manger_Master();
  ~Model_Manger_Master();

  // Checkers
  bool checkCollison(const Hit_Box &hitbox);

  // Adders
  void addItem(My_Obj_Loader &newItem) { regularItemManager.addItem(newItem); };

  // Render
  void renderAll();

private:
  Regular_Item_Manager<My_Obj_Loader> regularItemManager{};
};

#endif // MODEL_MANGER_MASTER_H
