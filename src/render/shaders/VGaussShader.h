//
// Created by Twometer on 20/12/2019.
//

#ifndef CHESS_3D_VGAUSSSHADER_H
#define CHESS_3D_VGAUSSSHADER_H

#include "IShader.h"

class VGaussShader : public IShader {

private:
    GLuint loc_targetHeight;

public:
    VGaussShader() {
        Initialize("vgauss");
    }

    void BindUniforms() override {
        loc_targetHeight = glGetUniformLocation(id, "targetHeight");
    }

    void SetTargetHeight(float targetHeight) {
        glUniform1f(loc_targetHeight, targetHeight);
    }

};

#endif //CHESS_3D_HGAUSSSHADER_H
