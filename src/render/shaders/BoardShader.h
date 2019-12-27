//
// Created by Twometer on 20/12/2019.
//

#ifndef CHESS_3D_BOARDSHADER_H
#define CHESS_3D_BOARDSHADER_H

#include "IShader.h"

class BoardShader : public IShader {

private:
    GLuint loc_mvpMatrix;
    GLuint loc_position;
    GLuint loc_cameraPos;
    GLuint loc_environFac;
    GLuint loc_diffuseFac;

public:
    BoardShader() {
        Initialize("board");
    }

    void BindUniforms() override {
        loc_mvpMatrix = glGetUniformLocation(id, "mvpMatrix");
        loc_position = glGetUniformLocation(id, "position");
        loc_cameraPos = glGetUniformLocation(id, "cameraPos");
        loc_environFac = glGetUniformLocation(id, "environFac");
        loc_diffuseFac = glGetUniformLocation(id, "diffuseFac");
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

    void SetMvpMatrix(glm::mat4 matrix) {
        LoadMatrix(loc_mvpMatrix, matrix);
    }

};

#endif //CHESS_3D_BOARDSHADER_H
