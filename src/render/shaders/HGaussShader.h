//
// Created by Twometer on 20/12/2019.
//

#ifndef CHESS_3D_HGAUSSSHADER_H
#define CHESS_3D_HGAUSSSHADER_H

#include "IShader.h"

class HGaussShader : public IShader {

private:
    GLuint loc_targetWidth;

public:
    HGaussShader() {
        Initialize("hgauss");
    }

    void BindUniforms() override {
        loc_targetWidth = glGetUniformLocation(id, "targetWidth");
    }

    void SetTargetWidth(float targetWidth) {
        glUniform1f(loc_targetWidth, targetWidth);
    }

};

#endif //CHESS_3D_HGAUSSSHADER_H
