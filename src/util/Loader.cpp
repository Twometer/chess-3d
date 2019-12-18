//
// Created by Twometer on 13/12/2019.
//

#include "Loader.h"
#include "Logger.h"
#include "StlReader.h"
#include "../gl/Mesh.h"
#include <fstream>
#include <cstring>
#include <iostream>

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
    Logger::Info("Loading shader " + name);
    std::string vertSource = ReadAllText("assets/shaders/" + name + ".v.glsl");
    std::string fragSource = ReadAllText("assets/shaders/" + name + ".f.glsl");

    if (vertSource.length() == 0 || fragSource.length() == 0) {
        Logger::Error("Shader " + name + " is empty");
        return 0;
    }


    GLuint program = glCreateProgram();

    GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
    const char *vs = vertSource.c_str();
    glShaderSource(vertShader, 1, &vs, nullptr);
    glCompileShader(vertShader);
    CheckShader("Vertex", vertShader);

    GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    const char *fs = fragSource.c_str();
    glShaderSource(fragShader, 1, &fs, nullptr);
    glCompileShader(fragShader);
    CheckShader("Fragment", fragShader);

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

void Loader::CheckShader(const std::string &name, GLuint shader) {
    int infoLogLength;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);
    if (infoLogLength > 0) {
        std::vector<char> errorMsg(infoLogLength + 1);
        glGetShaderInfoLog(shader, infoLogLength, nullptr, &errorMsg[0]);
        Logger::Error("[" + name + "] " + std::string(&errorMsg[0]));
    }
}

