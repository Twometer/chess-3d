//
// Created by Twometer on 18/12/2019.
//

#include "Fbo.h"

Fbo::Fbo(int width, int height, DepthBufferType type) {
    this->width = width;
    this->height = height;
}

Fbo::~Fbo() {
    glDeleteFramebuffers(1, &frameBuffer);
    glDeleteTextures(1, &colorTexture);
    glDeleteTextures(1, &depthTexture);
    glDeleteRenderbuffers(1, &colorBuffer);
    glDeleteRenderbuffers(1, &depthBuffer);
}

void Fbo::Bind() {
    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
    glViewport(0, 0, width, height);
}

void Fbo::Unbind() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

GLuint Fbo::GetColorTexture() {
    return colorTexture;
}

GLuint Fbo::GetDepthTexture() {
    return depthTexture;
}

void Fbo::Initialize(DepthBufferType depthBufferType) {
    CreateFramebuffer();
    CreateTextureAttachment();
    if (depthBufferType == DEPTH_RBUF)
        CreateDepthBufferAttachment();
    else if (depthBufferType == DEPTH_TEX)
        CreateDepthTextureAttachment();
    Unbind();
}

void Fbo::CreateFramebuffer() {
    glGenFramebuffers(1, &frameBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
    glDrawBuffer(GL_COLOR_ATTACHMENT0);
}

void Fbo::CreateTextureAttachment() {
    glGenTextures(1, &colorTexture);
    glBindTexture(GL_TEXTURE_2D, colorTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorTexture, 0);
}

void Fbo::CreateDepthBufferAttachment() {
    glGenRenderbuffers(1, &depthBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, width, height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBuffer);
}

void Fbo::CreateDepthTextureAttachment() {
    glGenTextures(1, &depthTexture);
    glBindTexture(GL_TEXTURE_2D, depthTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTexture, 0);
}
