#include "modelMangerMaster.h"
#include "../../utils/object/hitBox.h"
#include <iostream>

Model_Manger_Master::Model_Manger_Master() {
  // Constructor logic
}

Model_Manger_Master::~Model_Manger_Master() {
  // Destructor logic
}

// Checkers
bool Model_Manger_Master::checkCollison(const Hit_Box &hitBox) {
  if (!regularItemManager.checkCollison(hitBox))
    return false;

  return true;
}

// Render

void Model_Manger_Master::renderAll() { regularItemManager.renderAll(); };
