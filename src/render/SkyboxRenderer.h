//
// Created by Twometer on 22/12/2019.
//

#ifndef CHESS_3D_SKYBOXRENDERER_H
#define CHESS_3D_SKYBOXRENDERER_H

#include <vector>
#include "shaders/SkyboxShader.h"
#include "../gl/Model.h"
#include "Camera.h"

class SkyboxRenderer {

private:
    SkyboxShader *shader;

    Model *model;

    GLuint texture;

    static std::vector<std::string> TEXTURE_FILES;

public:
    SkyboxRenderer();

    void Render(Camera *camera);

    GLuint GetTexture();
};


#endif //CHESS_3D_SKYBOXRENDERER_H
