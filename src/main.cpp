#include "./manger/window.h"
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <filesystem>
#include <iostream>
#include <vector>

// Include your tiny_obj_loader here
#define TINYOBJLOADER_IMPLEMENTATION
#include "./include/tiny_obj_loader.h"

int main(int argc, char *argv[]) {
  Window masterWindow;
  if (masterWindow.init() == 1) {
    std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError()
              << std::endl;
    return 1;
  }

  // 6. Initialize GLEW
  glewExperimental = GL_TRUE;
  if (glewInit() != GLEW_OK) {
    std::cerr << "Failed to initialize GLEW" << std::endl;
    return 1;
  }

  // 7. Load OBJ
  std::string inputfile = "../resource/cube.obj";
  tinyobj::ObjReader reader;
  if (!reader.ParseFromFile(inputfile)) {
    std::cerr << "TinyObj Error: " << reader.Error();
    return 1;
  }

  auto &attrib = reader.GetAttrib();
  auto &shapes = reader.GetShapes();
  std::vector<float> vertex_data;

  for (const auto &shape : shapes) {
    for (const auto &index : shape.mesh.indices) {
      vertex_data.push_back(attrib.vertices[3 * index.vertex_index + 0]);
      vertex_data.push_back(attrib.vertices[3 * index.vertex_index + 1]);
      vertex_data.push_back(attrib.vertices[3 * index.vertex_index + 2]);
    }
  }

  // 8. VBO Setup
  GLuint vbo;
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, vertex_data.size() * sizeof(float),
               vertex_data.data(), GL_STATIC_DRAW);

  // 10. Main Loop
  bool quit = false;
  SDL_Event e;
  float rotation = 0.0f;

  std::cout << "Rendering started. Using XWayland bridge on Hyprland."
            << std::endl;

  while (!quit) {
    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT)
        quit = true;
    }

    masterWindow.renderStart();

    // Simple Perspective: FOV 45deg, Aspect 4/3, Near 0.1, Far 100
    float aspect = 800.0f / 600.0f;
    float fov = 45.0f;
    float zNear = 0.1f;
    float zFar = 100.0f;
    float f = 1.0f / tan(fov * (M_PI / 360.0f));
    float projMat[16] = {f / aspect,
                         0,
                         0,
                         0,
                         0,
                         f,
                         0,
                         0,
                         0,
                         0,
                         (zFar + zNear) / (zNear - zFar),
                         -1,
                         0,
                         0,
                         (2.0f * zFar * zNear) / (zNear - zFar),
                         0};
    glMultMatrixf(projMat);

    // --- SETUP MODELVIEW (The "Object Position") ---
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -5.0f);              // Move cube 5 units away
    glRotatef(rotation, 0.0f, 1.0f, 0.0f);        // Spin on Y axis
    glRotatef(rotation * 0.5f, 1.0f, 0.0f, 0.0f); // Spin on X axis
    rotation += 0.5f;

    // --- DRAW CUBE ---
    glColor3f(1.0f, 0.5f, 0.0f); // Oarchy Orange color
    glEnableClientState(GL_VERTEX_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexPointer(3, GL_FLOAT, 0, 0);

    glDrawArrays(GL_TRIANGLES, 0, vertex_data.size() / 3);

    glDisableClientState(GL_VERTEX_ARRAY);

    masterWindow.renderEnd();
  }

  // Cleanup
  glDeleteBuffers(1, &vbo);
  masterWindow.cleanup();

  return 0;
}
