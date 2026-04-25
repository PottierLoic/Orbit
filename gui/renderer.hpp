#pragma once

#include <string>
#include <vector>
#include <cstdint>

#include "color/rgba.hpp"
#include "glad/glad.h"

class Renderer {
public:
    Renderer() = default;
    Renderer(const std::string& vert_path, const std::string& frag_path);
    ~Renderer();

    void upload(const std::vector<RGBA>& pixels, uint32_t width, uint32_t height);
    void draw();

private:
    GLuint _shader_program;
    GLuint _vao;
    GLuint _vbo;
    GLuint _texture;

    GLuint compile_shader(const std::string& path, GLenum type);
    std::string load_file(const std::string& path);
};