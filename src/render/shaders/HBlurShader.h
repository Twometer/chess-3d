//
// Created by Twometer on 20/12/2019.
//

#ifndef CHESS_3D_HBLURSHADER_H
#define CHESS_3D_HBLURSHADER_H

#include "IShader.h"

class HBlurShader : public IShader {

private:
    GLuint loc_targetWidth;

public:
    HBlurShader() {
        Initialize("hblur", "blur");
    }

    void BindUniforms() override {
        loc_targetWidth = glGetUniformLocation(id, "targetWidth");
    }

    void SetTargetWidth(float targetWidth) {
        glUniform1f(loc_targetWidth, targetWidth);
    }

};

#endif //CHESS_3D_HBLURSHADER_H
