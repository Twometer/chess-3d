//
// Created by Twometer on 20/12/2019.
//

#ifndef CHESS_3D_SELECTIONSHADER_H
#define CHESS_3D_SELECTIONSHADER_H

#include "IShader.h"

class SelectionShader : public IShader {

private:
    GLuint loc_cameraMatrix;
    GLuint loc_modelMatrix;
    GLuint loc_position;

public:
    SelectionShader() {
        Initialize("selection");
    }

    void BindUniforms() override {
        loc_cameraMatrix = glGetUniformLocation(id, "cameraMatrix");
        loc_modelMatrix = glGetUniformLocation(id, "modelMatrix");
        loc_position = glGetUniformLocation(id, "position");
    }

    void SetPosition(glm::vec2 position) {
        LoadVec2(loc_position, position);
    }

    void SetCameraMatrix(glm::mat4 matrix) {
        LoadMatrix(loc_cameraMatrix, matrix);
    }

    void SetModelMatrix(glm::mat4 matrix) {
        LoadMatrix(loc_modelMatrix, matrix);
    }

};

#endif //CHESS_3D_SELECTIONSHADER_H
