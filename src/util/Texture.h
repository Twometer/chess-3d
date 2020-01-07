//
// Created by Twometer on 07/01/2020.
//

#ifndef CHESS_3D_TEXTURE_H
#define CHESS_3D_TEXTURE_H

#include <glad/glad.h>

struct Texture {
    GLuint id;
    unsigned int width;
    unsigned int height;

    void Bind() {
        glBindTexture(GL_TEXTURE_2D, id);
    }

    void Unbind() {
        glBindTexture(GL_TEXTURE_2D, 0);
    }
};

#endif //CHESS_3D_TEXTURE_H
