#include "defualtItemManger.h"
#include <iostream>
#include <stdexcept>

template <typename T> Default_Item_Manager<T>::Default_Item_Manager() {
  // Constructor logic
}

template <typename T> Default_Item_Manager<T>::~Default_Item_Manager() {
  // Destructor logic
}

// Checkers
template <typename T>
bool Default_Item_Manager<T>::checkCollison(
    const Hit_Box &hitbox); // TODO: Add logic for checkCollison

template <typename T> bool Default_Item_Manager<T>::checkIndex(int index) {
  if (index < 0 || index >= this->objectList.size())
    return false;
  return true;
};
// Adders
template <typename T>
void Default_Item_Manager<T>::addItem(My_Obj_Loader &newItem) {
  this->objectList.push_back(newItem);
};
// Getters
template <typename T> Hit_Box &Default_Item_Manager<T>::getHitBox(int index) {
  if (this->checkIndex(index)) {
    throw std::out_of_range("Model index is out of bounds");
  }
  return this->objectList[index].getDefaultHitBox();
};
template <typename T>
My_Obj_Loader &Default_Item_Manager<T>::getModel(int index) {
  if (this->checkIndex(index)) {
    throw std::out_of_range("Model index is out of bounds");
  }
  return this->objectList[index];
};

// Destorys
template <typename T> void Default_Item_Manager::destryItme(int index) {
  if (this->checkIndex(index)) {
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
