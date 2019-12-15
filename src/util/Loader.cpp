//
// Created by Twometer on 13/12/2019.
//

#include "Loader.h"
#include "Logger.h"
#include "Buffer.h"
#include "../gl/Mesh.h"
#include <fstream>
#include <glm/vec3.hpp>

constexpr int STL_HEADER_SIZE = 80;

std::string Loader::LoadFromFile(const std::string &path) {
    std::ifstream stream(path);
    std::string content((std::istreambuf_iterator<char>(stream)), std::istreambuf_iterator<char>());
    return content;
}

GLuint Loader::LoadShader(const std::string &name) {
    const char *vertSource = LoadFromFile("assets/" + name + ".v.glsl").c_str();
    const char *fragSource = LoadFromFile("assets/" + name + ".f.glsl").c_str();

    GLuint program = glCreateProgram();

    GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertShader, 1, &vertSource, nullptr);
    glCompileShader(vertShader);

    GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragShader, 1, &fragSource, nullptr);
    glCompileShader(fragShader);

    glAttachShader(program, vertShader);
    glAttachShader(program, fragShader);

    glLinkProgram(program);

    glDetachShader(program, vertShader);
    glDetachShader(program, fragShader);

    glDeleteShader(vertShader);
    glDeleteShader(fragShader);

    Logger::Info("Loaded shader " + name);

    return program;
}

Model *Loader::LoadModel(const std::string &name) {
    const char *path = ("assets/models/" + name + ".stl").c_str();
    FILE* file = fopen(path, "r");
    long size = ftell(file);
    auto* buf = new uint8_t[size];
    fread(buf, sizeof(uint8_t), size, file);
    fclose(file);

    Mesh mesh;
    Buffer buffer(buf);
    buffer.Skip(STL_HEADER_SIZE);

    int triangles = buffer.ReadUINT32();
    for (int i = 0; i < triangles; i++){
        uint16_t attrCount = buffer.ReadUINT16();
        if (attrCount != 0)
            throw std::runtime_error("Unsupported STL format");
    }

    delete[] buf;
    return mesh.CreateModel();
}

