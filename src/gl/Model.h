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

public:
    static Model *Create(Mesh *mesh);

    void Draw();

};


#endif //CHESS_3D_MODEL_H
