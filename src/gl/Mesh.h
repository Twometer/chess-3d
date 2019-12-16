//
// Created by Twometer on 15/12/2019.
//

#ifndef CHESS_3D_MESH_H
#define CHESS_3D_MESH_H

#include <glad/glad.h>
#include <vector>
#include <glm/vec3.hpp>
#include "Model.h"

class Model;
class Mesh {
private:
    std::vector<GLfloat> vertices;

    std::vector<GLfloat> normals;

public:
    void AddVertex(glm::vec3 vertex);

    std::vector<GLfloat> &GetVertices() {
        return vertices;
    }

    int GetVertexCount() {
        return vertices.size() / 3;
    }

    void AddNormal(glm::vec3 normal);

    int GetNormalCount() {
        return normals.size() / 3;
    }

    std::vector<GLfloat> &GetNormals() {
        return normals;
    }

    Model* CreateModel();

};


#endif //CHESS_3D_MESH_H
