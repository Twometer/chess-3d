//
// Created by Twometer on 21/12/2019.
//

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
    return glm::vec3(-vec.y, vec.x, vec.z);
}