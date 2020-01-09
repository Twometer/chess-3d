//
// Created by Twometer on 09/01/2020.
//

#ifndef CHESS_3D_BOARDSHADER_H
#define CHESS_3D_BOARDSHADER_H

#include "IShader.h"

class BoardShader : public IShader {
private:
    GLuint loc_cameraMatrix;

public:

    BoardShader() {
        Initialize("board");
    }

    void BindUniforms() override {
        loc_cameraMatrix = glGetUniformLocation(id, "cameraMatrix");
    }

    void SetCameraMatrix(glm::mat4 matrix) {
        LoadMatrix(loc_cameraMatrix, matrix);
    }
};

#endif //CHESS_3D_BOARDSHADER_H
