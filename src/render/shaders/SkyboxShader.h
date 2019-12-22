//
// Created by Twometer on 22/12/2019.
//

#ifndef CHESS_3D_SKYBOXSHADER_H
#define CHESS_3D_SKYBOXSHADER_H

#include "IShader.h"


class SkyboxShader : public IShader {

private:
    GLuint loc_projectionMatrix;
    GLuint loc_viewMatrix;

public:
    SkyboxShader() {
        Initialize("skybox");
    }

    void BindUniforms() override {
        loc_projectionMatrix = glGetUniformLocation(id, "projectionMatrix");
        loc_viewMatrix = glGetUniformLocation(id, "viewMatrix");
    }

    void SetProjectionMatrtix(glm::mat4 projectionMatrix) {
        LoadMatrix(loc_projectionMatrix, projectionMatrix);
    }

    void SetViewMatrix(glm::mat4 viewMatrix) {
        //viewMatrix[3][0] = 0;
        //viewMatrix[3][1] = 0;
        //viewMatrix[3][2] = 0;
        LoadMatrix(loc_viewMatrix, viewMatrix);
    }


};

#endif //CHESS_3D_SKYBOXSHADER_H
