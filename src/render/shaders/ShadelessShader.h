//
// Created by Twometer on 20/12/2019.
//

#ifndef CHESS_3D_SHADELESSSHADER_H
#define CHESS_3D_SHADELESSSHADER_H

#include "IShader.h"

class ShadelessShader : public IShader {

private:
    GLuint loc_cameraMatrix;
    GLuint loc_modelMatrix;
    GLuint loc_position;
    GLuint loc_color;

public:
    ShadelessShader() {
        Initialize("shadeless");
    }

    void BindUniforms() override {
        loc_cameraMatrix = glGetUniformLocation(id, "cameraMatrix");
        loc_modelMatrix = glGetUniformLocation(id, "modelMatrix");
        loc_position = glGetUniformLocation(id, "position");
        loc_color = glGetUniformLocation(id, "modelColor");
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

    void SetColor(glm::vec4 color) {
        LoadVec4(loc_color, color);
    }

};

#endif //CHESS_3D_SHADELESSSHADER_H
