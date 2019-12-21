//
// Created by Twometer on 20/12/2019.
//

#include "Postproc.h"

GLuint Postproc::vao = 0;

GLfloat POSITIONS[] = {-1, 1, -1, -1, 1, 1, 1, -1};
const int AMOUNT = 8;

void Postproc::Initialize() {
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * AMOUNT, POSITIONS, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, false, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}

void Postproc::Start() {
    glBindVertexArray(vao);
    glEnableVertexAttribArray(0);
}

void Postproc::Stop() {
    glDisableVertexAttribArray(0);
    glBindVertexArray(0);
}

void Postproc::Copy(Fbo *src, Fbo *dst) {
    if (dst != nullptr) {
        dst->Bind();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, src->GetColorTexture());
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    if (dst != nullptr) dst->Unbind();
}
