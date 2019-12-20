//
// Created by Twometer on 20/12/2019.
//

#ifndef CHESS_3D_SIMPLESHADER_H
#define CHESS_3D_SIMPLESHADER_H

#include "IShader.h"

class SimpleShader : public IShader {

private:
    GLuint loc_mvpMatrix;
    GLuint loc_offset;

public:
    SimpleShader() {
        Initialize("simple");
    }

    void BindUniforms() override {
        loc_mvpMatrix = glGetUniformLocation(id, "mvpMatrix");
        loc_offset = glGetUniformLocation(id, "offset");
    }

    void SetOffset(glm::vec3 offset) {
        LoadVec3(loc_offset, offset);
    }

    void SetMvpMatrix(glm::mat4 matrix) {
        LoadMatrix(loc_mvpMatrix, matrix);
    }

};

#endif //CHESS_3D_SIMPLESHADER_H
