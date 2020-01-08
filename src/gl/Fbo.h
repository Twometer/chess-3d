//
// Created by Twometer on 18/12/2019.
//

#ifndef CHESS_3D_FBO_H
#define CHESS_3D_FBO_H

#include <glad/glad.h>

enum class DepthBufferType {
    None,
    DepthTex,
    DepthRbuf
};

class Fbo {
private:
    int width;
    int height;

    GLuint frameBuffer = 0;
    GLuint depthBuffer = 0;
    GLuint colorBuffer = 0;

    GLuint depthTexture = 0;
    GLuint colorTexture = 0;

public:
    Fbo(int width, int height, DepthBufferType type);

    ~Fbo();

    void Bind();

    void Unbind();

    GLuint GetColorTexture();

    GLuint GetDepthTexture();

    int GetWidth() { return width; }

    int GetHeight() { return height; }

private:
    void Initialize(DepthBufferType depthBufferType);

    void CreateFramebuffer();

    void CreateTextureAttachment();

    void CreateDepthBufferAttachment();

    void CreateDepthTextureAttachment();
};


#endif //CHESS_3D_FBO_H
