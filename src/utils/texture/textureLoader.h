#ifndef TEXTURE_LOADER_H
#define TEXTURE_LOADER_H

#include <GL/glew.h> // Or your specific OpenGL loader
#include <string>

GLuint loadTextureCached(const char *path);
inline GLuint loadTexture(const char *path);

#endif // TEXTURE_LOADER_H
