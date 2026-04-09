#define STB_IMAGE_IMPLEMENTATION
#include "textureLoader.h"
#include "../../include/stb_image.h"
#include <iostream>
#include <map>
#include <string>

// A global or class-level map to store paths and their corresponding IDs
std::map<std::string, GLuint> textureCache;

GLuint loadTextureCached(const char *path) {
  // 1. Check if we already loaded this exact path
  if (textureCache.find(path) != textureCache.end()) {
    return textureCache[path]; // Return the existing ID!
  }

  // 2. If not found, do the actual loading work
  GLuint newID = loadTexture(path); // Call your existing function

  // 3. Store it for next time
  if (newID != 0) {
    textureCache[path] = newID;
  }

  return newID;
}

GLuint loadTexture(const char *path) {
  GLuint textureID;
  glGenTextures(1, &textureID);

  int width, height, nrComponents;
  // Standard practice: flip the image on load because OpenGL
  // expects the 0,0 coordinate to be the bottom left.
  stbi_set_flip_vertically_on_load(true);

  unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);

  if (data == nullptr) {
    std::cerr << "SEGFAULT PREVENTED: Image not found at " << path << std::endl;
    return 0;
  }

  if (data) {
    GLenum format = GL_RGB;
    if (nrComponents == 1)
      format = GL_RED;
    else if (nrComponents == 3)
      format = GL_RGB;
    else if (nrComponents == 4)
      format = GL_RGBA;

    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format,
                 GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    // Texture Parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                    GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_image_free(data);
    // std::cout << "Successfully loaded texture: " << path << std::endl;
  } else {
    std::cerr << "Texture failed to load at path: " << path << std::endl;
    stbi_image_free(data);
    return 0; // Return 0 (id for no texture) on failure
  }

  return textureID;
}
