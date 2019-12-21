//
// Created by Twometer on 20/12/2019.
//

#ifndef CHESS_3D_COPYSHADER_H
#define CHESS_3D_COPYSHADER_H

#include "IShader.h"

class CopyShader : public IShader {

private:

public:
    CopyShader() {
        Initialize("copy");
    }

    void BindUniforms() override {

    }

};

#endif //CHESS_3D_SIMPLESHADER_H
