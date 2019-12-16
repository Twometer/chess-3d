//
// Created by Twometer on 13/12/2019.
//

#include "Loader.h"
#include "Logger.h"
#include "StlReader.h"
#include "../gl/Mesh.h"
#include <fstream>
#include <cstring>

uint8_t *Loader::ReadAllBytes(const std::string &path) {
    std::ifstream file(path);
    file.seekg(0, std::ios::end);
    size_t length = file.tellg();
    file.seekg(0, std::ios::beg);

    auto *buf = new uint8_t[length];
    file.read((char *) buf, length);

    file.close();
    return buf;
}

std::string Loader::ReadAllText(const std::string &path) {
    std::ifstream stream(path);
    std::string content((std::istreambuf_iterator<char>(stream)), std::istreambuf_iterator<char>());
    return content;
}

GLuint Loader::LoadShader(const std::string &name) {
    const char *vertSource = ReadAllText("assets/" + name + ".v.glsl").c_str();
    const char *fragSource = ReadAllText("assets/" + name + ".f.glsl").c_str();

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
    uint8_t *buf = ReadAllBytes("assets/models/" + name);
    Model *model = StlReader::Load(buf);
    delete[] buf;
    return model;
}

