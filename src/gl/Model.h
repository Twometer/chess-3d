//
// Created by Twometer on 15/12/2019.
//

#ifndef CHESS_3D_MODEL_H
#define CHESS_3D_MODEL_H

#include <glad/glad.h>
#include "Mesh.h"

class Mesh;

class Model {

private:
    GLuint vaoId;

    int vertices;

public:
    static Model *Create(Mesh *mesh);

    void Render();

};


#endif //CHESS_3D_MODEL_H
