#include "regularItemManager.h"
#include <iostream>
#include <stdexcept>

Default_Item_Manager::Default_Item_Manager() {
  // Constructor logic
}

Default_Item_Manager::~Default_Item_Manager() {
  // Destructor logic
}

// Checkers
bool Default_Item_Manager::checkCollison(
    const Hit_Box &hitbox); // TODO: Add logic for checkCollison

bool Default_Item_Manager::checkIndex(int index) {
  if (index < 0 || index >= this->objectList.size())
    return false;
  return true;
};
// Adders
void Default_Item_Manager::addItem(My_Obj_Loader &newItem) {
  this->objectList.push_back(newItem);
};
// Getters
Hit_Box &Default_Item_Manager::getHitBox(int index) {
  if (this->checkIndex(index)) {
    throw std::out_of_range("Model index is out of bounds");
  }
  return this->objectList[index].getDefaultHitBox();
};
My_Obj_Loader &Default_Item_Manager::getModel(int index) {
  if (this->checkIndex(index)) {
    throw std::out_of_range("Model index is out of bounds");
  }
  return this->objectList[index];
};

// Destorys
void Default_Item_Manager::destryItme(int index) {
  if (this->checkIndex(index)) {
    throw std::out_of_range("Model index is out of bounds");
  }
  this->objectList.erase(this->objectList.begin() + index);
};
