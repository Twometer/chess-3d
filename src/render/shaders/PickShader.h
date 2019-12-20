//
// Created by Twometer on 20/12/2019.
//

#ifndef CHESS_3D_PICKSHADER_H
#define CHESS_3D_PICKSHADER_H

#include "IShader.h"

class PickShader : public IShader {

private:
    GLuint loc_mvpMatrix;
    GLuint loc_position;

public:
    PickShader() {
        Initialize("pick");
    }

    void BindUniforms() override {
        loc_mvpMatrix = glGetUniformLocation(id, "mvpMatrix");
        loc_position = glGetUniformLocation(id, "position");
    }

    void SetPosition(glm::vec2 position) {
        LoadVec2(loc_position, position);
    }

    void SetMvpMatrix(glm::mat4 matrix) {
        LoadMatrix(loc_mvpMatrix, matrix);
    }

};

#endif //CHESS_3D_PICKSHADER_H
