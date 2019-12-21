//
// Created by Twometer on 20/12/2019.
//

#ifndef CHESS_3D_VBLURSHADER_H
#define CHESS_3D_VBLURSHADER_H

#include "IShader.h"

class VBlurShader : public IShader {

private:
    GLuint loc_targetHeight;

public:
    VBlurShader() {
        Initialize("vblur", "blur");
    }

    void BindUniforms() override {
        loc_targetHeight = glGetUniformLocation(id, "targetHeight");
    }

    void SetTargetHeight(float targetHeight) {
        glUniform1f(loc_targetHeight, targetHeight);
    }

};

#endif //CHESS_3D_HGAUSSSHADER_H
