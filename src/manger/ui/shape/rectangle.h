#include <GL/gl.h>
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

inline void drawFilledRoundedRect(float x, float y, float width, float height,
                                  float radius, int segments) {
  // 1. Draw the central "cross" (two intersecting rectangles) to fill the
  // interior
  glBegin(GL_QUADS);
  // Vertical rectangle
  glVertex2f(x + radius, y);
  glVertex2f(x + width - radius, y);
  glVertex2f(x + width - radius, y + height);
  glVertex2f(x + radius, y + height);

  // Horizontal rectangle
  glVertex2f(x, y + radius);
  glVertex2f(x + width, y + radius);
  glVertex2f(x + width, y + height - radius);
  glVertex2f(x, y + height - radius);
  glEnd();

  // 2. Helper to draw the four filled corners
  auto drawCorner = [&](float centerX, float centerY, float startAngle) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(centerX, centerY); // Center of the corner arc
    for (int i = 0; i <= segments; i++) {
      float angle = startAngle + (i * (M_PI / 2.0f) / segments);
      glVertex2f(centerX + cos(angle) * radius, centerY + sin(angle) * radius);
    }
    glEnd();
  };

  // Draw each corner
  drawCorner(x + width - radius, y + height - radius, 0.0f); // Top Right
  drawCorner(x + radius, y + height - radius, M_PI / 2.0f);  // Top Left
  drawCorner(x + radius, y + radius, M_PI);                  // Bottom Left
  drawCorner(x + width - radius, y + radius,
             3.0f * M_PI / 2.0f); // Bottom Right
}
