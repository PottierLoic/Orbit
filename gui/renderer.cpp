#include "renderer.hpp"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

Renderer::Renderer(const std::string& vert_path, const std::string& frag_path) {
    GLuint _vertex_shader = compile_shader(vert_path, GL_VERTEX_SHADER);
    GLuint _fragment_shader = compile_shader(frag_path, GL_FRAGMENT_SHADER);

    _shader_program = glCreateProgram();
    glAttachShader(_shader_program, _vertex_shader);
    glAttachShader(_shader_program, _fragment_shader);
    glLinkProgram(_shader_program);
    glDeleteShader(_vertex_shader);
    glDeleteShader(_fragment_shader);

    float vertices[] = {
            -1.0f, 1.0f, 0.0f, 1.0f,
            1.0f, 1.0f, 1.0f, 1.0f,
            -1.0f, -1.0f, 0.0f, 0.0f,
            1.0f, -1.0f, 1.0f, 0.0f,
    };

    glGenVertexArrays(1, &_vao);
    glGenBuffers(1, &_vbo);
    glBindVertexArray(_vao);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glGenTextures(1, &_texture);
    glBindTexture(GL_TEXTURE_2D, _texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}

Renderer::~Renderer() {
    glDeleteVertexArrays(1, &_vao);
    glDeleteBuffers(1, &_vbo);
    glDeleteTextures(1, &_texture);
    glDeleteProgram(_shader_program);
}

void Renderer::upload(const std::vector<RGBA>& pixels, uint32_t width, uint32_t height) {
    glBindTexture(GL_TEXTURE_2D, _texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels.data());
}

void Renderer::draw() {
    glUseProgram(_shader_program);
    glBindTexture(GL_TEXTURE_2D, _texture);
    glBindVertexArray(_vao);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

GLuint Renderer::compile_shader(const std::string& path, GLenum type) {
    std::string source = load_file(path);
    const char* source_c_str = source.c_str();
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source_c_str, nullptr);
    glCompileShader(shader);
    return shader;
}

std::string Renderer::load_file(const std::string& path) {
    std::string shader_code;
    std::ifstream shader_file;
    try {
        shader_file.open(path);
        std::stringstream shader_stream;
        shader_stream << shader_file.rdbuf();
        shader_file.close();

        shader_code = shader_stream.str();
    } catch (std::ifstream::failure& e) {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << e.what() << std::endl;
    }
    return shader_code;
}