#ifndef FONT_RENDERER_H
#define FONT_RENDERER_H

#include <ft2build.h>
#include FT_FREETYPE_H
#include <glm/glm.hpp>
#include <map>
#include <string>

struct Character {
  unsigned int TextureID; // ID handle of the glyph texture
  glm::ivec2 Size;        // Size of glyph
  glm::ivec2 Bearing;     // Offset from baseline to left/top of glyph
  unsigned int Advance;   // Offset to advance to next glyph
};

class FontRenderer {
public:
  std::map<char32_t, Character> Characters;
  void init(const char *fontPath, int fontSize);
  void renderText(std::u32string text, float x, float y, float scale,
                  glm::vec3 color);
};

#endif
