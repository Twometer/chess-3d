//
// Created by Twometer on 15/12/2019.
//

#include "Mesh.h"

void Mesh::AddVertex(glm::vec3 vertex) {
    vertices.push_back(vertex.x);
    vertices.push_back(vertex.y);
    vertices.push_back(vertex.z);
}

void Mesh::AddNormal(glm::vec3 normal) {
    normals.push_back(normal.x);
    normals.push_back(normal.y);
    normals.push_back(normal.z);
}

Model *Mesh::CreateModel() {
    return Model::Create(this);
}
