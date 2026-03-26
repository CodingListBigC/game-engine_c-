#include "FontRenderer.h"
#include <GL/gl.h>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <string>
void FontRenderer::init(const char *fontPath, int fontSize) {
  FT_Library ft;
  if (FT_Init_FreeType(&ft)) {
    std::cout << "ERROR::FREETYPE: Could not init FreeType Library"
              << std::endl;
    return;
  }

  FT_Face face;
  if (FT_New_Face(ft, fontPath, 0, &face)) {
    std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
    return;
  }

  FT_Set_Pixel_Sizes(face, 0, fontSize);
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

  // --- HELPER TO LOAD GLYPHS ---
  auto loadGlyph = [&](char32_t c) {
    if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
      return; // Skip if glyph doesn't exist in this font
    }

    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, face->glyph->bitmap.width,
                 face->glyph->bitmap.rows, 0, GL_ALPHA, GL_UNSIGNED_BYTE,
                 face->glyph->bitmap.buffer);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    Character character = {
        texture,
        glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
        glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
        static_cast<unsigned int>(face->glyph->advance.x)};
    // Store using char32_t key
    Characters[c] = character;
  };

  // 1. Load Standard ASCII (0-127)
  for (char32_t c = 0; c < 128; c++) {
    loadGlyph(c);
  }

  // 2. Load Nerd Font Icons
  // Add any hex codes you plan to use here!
  char32_t icons[] = {
      0xf007, // User icon
      0xf013, // Gear icon
      0xf060, // Left arrow
      0xe712  // Linux icon
  };

  for (char32_t icon : icons) {
    loadGlyph(icon);
  }

  FT_Done_Face(face);
  FT_Done_FreeType(ft);
}

void FontRenderer::renderText(std::basic_string<char32_t> text, float x,
                              float y, float scale, glm::vec3 color) {
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glColor4f(color.x, color.y, color.z, 1.0f);

  for (char32_t c : text) {
    if (Characters.find(c) == Characters.end())
      continue;

    Character ch = Characters[c];
    float xpos = x + ch.Bearing.x * scale;
    float ypos = y - ch.Bearing.y * scale;
    float w = ch.Size.x * scale;
    float h = ch.Size.y * scale;

    glBindTexture(GL_TEXTURE_2D, ch.TextureID);

    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex2f(xpos, ypos);
    glTexCoord2f(1.0f, 0.0f);
    glVertex2f(xpos + w, ypos);
    glTexCoord2f(1.0f, 1.0f);
    glVertex2f(xpos + w, ypos + h);
    glTexCoord2f(0.0f, 1.0f);
    glVertex2f(xpos, ypos + h);
    glEnd();

    x += (ch.Advance >> 6) * scale;
  }
  glBindTexture(GL_TEXTURE_2D, 0);
  glDisable(GL_BLEND);
  glDisable(GL_TEXTURE_2D);
}
