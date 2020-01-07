//
// Created by Twometer on 07/01/2020.
//

#ifndef CHESS_3D_FONTSHADER_H
#define CHESS_3D_FONTSHADER_H

#include "IShader.h"

class FontShader : public IShader {
private:
    GLuint loc_projectionMatrix;
    GLuint loc_color;

public:
    FontShader() {
        Initialize("font");
    }

    void BindUniforms() override {
        loc_projectionMatrix = glGetUniformLocation(id, "projectionMatrix");
        loc_color = glGetUniformLocation(id, "color");
    }

    void SetProjectionMatrix(glm::mat4 matrix) {
        LoadMatrix(loc_projectionMatrix, matrix);
    }

    void SetColor(glm::vec4 color) {
        LoadVec4(loc_color, color);
    }


};

#endif //CHESS_3D_FONTSHADER_H
