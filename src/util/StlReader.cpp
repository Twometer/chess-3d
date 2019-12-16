//
// Created by Twometer on 16/12/2019.
//

#include "../gl/Mesh.h"
#include "Buffer.h"
#include "StlReader.h"

constexpr int STL_HEADER_SIZE = 80;

Model *StlReader::Load(uint8_t *buf) {
    Mesh mesh;
    Buffer buffer(buf);
    buffer.Skip(STL_HEADER_SIZE);

    int triangles = buffer.Read<uint32_t>();
    for (int i = 0; i < triangles; i++) {
        glm::vec3 normal = ReadVec3(buffer);

        for (int j = 0; j < 3; j++) {
            glm::vec3 vertex = ReadVec3(buffer);
            mesh.AddNormal(normal);
            mesh.AddVertex(vertex);
        }

        // Skip the "attribute byte count"
        buffer.Skip(2);
    }
    return mesh.CreateModel();
}

glm::vec3 StlReader::ReadVec3(Buffer &buf) {
    return glm::vec3(buf.Read<float>(), buf.Read<float>(), buf.Read<float>());
}
