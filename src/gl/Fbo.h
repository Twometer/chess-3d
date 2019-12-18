//
// Created by Twometer on 18/12/2019.
//

#ifndef CHESS_3D_FBO_H
#define CHESS_3D_FBO_H

#include <glad/glad.h>

enum DepthBufferType {
    NONE,
    DEPTH_TEX,
    DEPTH_RBUF
};

class Fbo {
private:
    int width;
    int height;

    GLuint frameBuffer;
    GLuint depthBuffer;
    GLuint colorBuffer;

    GLuint depthTexture;
    GLuint colorTexture;

public:
    Fbo(int width, int height, DepthBufferType type);

    ~Fbo();

    void Bind();

    void Unbind();

    GLuint GetColorTexture();

    GLuint GetDepthTexture();

private:
    void Initialize(DepthBufferType depthBufferType);

    void CreateFramebuffer();

    void CreateTextureAttachment();

    void CreateDepthBufferAttachment();

    void CreateDepthTextureAttachment();
};


#endif //CHESS_3D_FBO_H
