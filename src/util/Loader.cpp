//
// Created by Twometer on 13/12/2019.
//

#include "Loader.h"
#include "Logger.h"
#include "GlmReader.h"
#include "../gl/Mesh.h"
#include "FontReader.h"
#include <fstream>
#include <cstring>
#include <iostream>
#include <lodepng.h>

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
    return LoadShader(name, name);
}

GLuint Loader::LoadShader(const std::string &vname, const std::string &fname) {
    Logger::Info("Loading shader " + vname + "/" + fname);
    std::string vertSource = ReadAllText("assets/shaders/" + vname + ".v.glsl");
    std::string fragSource = ReadAllText("assets/shaders/" + fname + ".f.glsl");

    if (vertSource.length() == 0 || fragSource.length() == 0) {
        Logger::Error("Shader " + vname + "/" + fname + " is empty");
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

    return program;
}

Model *Loader::LoadModel(const std::string &name) {
    uint8_t *buf = ReadAllBytes("assets/models/" + name);
    Model *model = GlmReader::Load(buf);
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

Image Loader::LoadImage(const std::string &path) {
    auto *image = new std::vector<uint8_t>();
    unsigned int width, height;
    unsigned error = lodepng::decode(*image, width, height, path.c_str());
    if (error) Logger::Error("Failed to decode image: " + std::string(lodepng_error_text(error)));
    return {&image->front(), static_cast<unsigned int>(image->size()), width, height};
}

GLuint Loader::LoadCubemap(const std::vector<std::string> &names) {
    GLuint texture;
    glGenTextures(1, &texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, texture);

    for (int i = 0; i < names.size(); i++) {
        Logger::Info("Loading texture " + names[i]);;
        Image img = LoadImage("assets/textures/" + names[i] + ".png");
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, img.width, img.height, 0, GL_RGBA,
                     GL_UNSIGNED_BYTE, img.ptr);
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
    return texture;
}

Font *Loader::LoadFont(const std::string &name) {
    std::string pngPath = "assets/fonts/" + name + ".png";
    std::string fntPath = "assets/fonts/" + name + ".fnt";

    std::ifstream stream(fntPath);
    Font *font = FontReader::ReadFont(stream);
    font->texture = LoadTexture(pngPath);

    return font;
}

Texture Loader::LoadTexture(const std::string &path) {
    Image img = LoadImage(path);

    GLuint texture;
    glGenTextures(1, &texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img.width, img.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, img.ptr);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    return {texture, img.width, img.height};
}
