#ifndef DEFAULT_ITEM_MANAGER_H
#define DEFAULT_ITEM_MANAGER_H

#include "../../models/myObjLoader.h"
#include "../../utils/object/hitBox.h"
#include <vector>

template <typename T>

class Default_Item_Manager {
public:
  Default_Item_Manager();
  ~Default_Item_Manager();
  // Checkers
  bool checkCollison(const Hit_Box &hitbox);
  bool checkIndex(int index);

  // Adders
  void addItem(T &newItem);
  // Getters
  Hit_Box &getHitBox(int index);
  My_Obj_Loader &getModel(int index);

  // Destorys
  void destryItme(int index);

  // Render
  void renderAll();

private:
  std::vector<T> objectList;
};
template <typename T> Default_Item_Manager<T>::Default_Item_Manager() {
  // Constructor logic
}

template <typename T> Default_Item_Manager<T>::~Default_Item_Manager() {
  // Destructor logic
}

// Checkers
template <typename T>
bool Default_Item_Manager<T>::checkCollison(const Hit_Box &hitbox) {
  return true;
}; // TODO: Add logic for checkCollison

template <typename T> bool Default_Item_Manager<T>::checkIndex(int index) {
  if (index < 0 || index >= this->objectList.size())
    return false;
  return true;
};
// Adders
template <typename T> void Default_Item_Manager<T>::addItem(T &newItem) {
  this->objectList.push_back(newItem);
};
// Getters
template <typename T> Hit_Box &Default_Item_Manager<T>::getHitBox(int index) {
  if (!this->checkIndex(index)) {
    throw std::out_of_range("Model index is out of bounds");
  }
  return this->objectList[index].getDefaultHitBox();
};
template <typename T>
My_Obj_Loader &Default_Item_Manager<T>::getModel(int index) {
  if (!this->checkIndex(index)) {
    throw std::out_of_range("Model index is out of bounds");
  }
  return this->objectList[index];
};

// Destorys
template <typename T> void Default_Item_Manager<T>::destryItme(int index) {
  if (!this->checkIndex(index)) {
    throw std::out_of_range("Model index is out of bounds");
  }
  this->objectList.erase(this->objectList.begin() + index);
};

// Render

template <typename T> void Default_Item_Manager<T>::renderAll() {
  for (int i = 0; this->objectList.size() > i; i++) {
    this->objectList[i].render();
  }
};

#endif // DEFAULT_ITEM_MANAGER_H
