//
// Created by Twometer on 20/12/2019.
//

#ifndef CHESS_3D_PIECESHADER_H
#define CHESS_3D_PIECESHADER_H

#include "IShader.h"

class PieceShader : public IShader {

private:
    GLuint loc_cameraMatrix;
    GLuint loc_modelMatrix;
    GLuint loc_position;
    GLuint loc_cameraPos;
    GLuint loc_environFac;
    GLuint loc_diffuseFac;
    GLuint loc_diffuseColor;

public:
    PieceShader() {
        Initialize("piece");
    }

    void BindUniforms() override {
        loc_cameraMatrix = glGetUniformLocation(id, "cameraMatrix");
        loc_modelMatrix = glGetUniformLocation(id, "modelMatrix");
        loc_position = glGetUniformLocation(id, "position");
        loc_cameraPos = glGetUniformLocation(id, "cameraPos");
        loc_environFac = glGetUniformLocation(id, "environFac");
        loc_diffuseFac = glGetUniformLocation(id, "diffuseFac");
        loc_diffuseColor = glGetUniformLocation(id, "diffuseColor");
    }

    void SetDiffuseColor(glm::vec3 diffuseColor) {
        LoadVec3(loc_diffuseColor, diffuseColor);
    }

    void SetEnvironFac(float envMix) {
        glUniform1f(loc_environFac, envMix);
    }

    void SetDiffuseFac(float envMix) {
        glUniform1f(loc_diffuseFac, envMix);
    }

    void SetCameraPos(glm::vec3 position) {
        LoadVec3(loc_cameraPos, position);
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

#endif //CHESS_3D_PIECESHADER_H
