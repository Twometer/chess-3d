//
// Created by Twometer on 21/12/2019.
//

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "GlmReader.h"

constexpr int GLM_HEADER_SIZE = 4;

Model *GlmReader::Load(uint8_t *buf) {
    Mesh mesh;
    Buffer buffer(buf);
    buffer.Skip(GLM_HEADER_SIZE);

    int vertices = buffer.Read<uint32_t>();

    for (int j = 0; j < vertices; j++) {
        glm::vec3 vertex = ReadVec3(buffer);
        glm::vec3 normal = ReadVec3(buffer);
        mesh.AddVertex(vertex);
        mesh.AddNormal(normal);
    }
    return mesh.CreateModel();
}

glm::vec3 GlmReader::ReadVec3(Buffer &buf) {
    glm::vec3 vec = glm::vec3(buf.Read<float>(), buf.Read<float>(), buf.Read<float>());
    glm::mat4 matrix = glm::rotate(glm::mat4(1.0), (float) glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));

    return glm::vec3(matrix * glm::vec4(vec, 1.0f));
}