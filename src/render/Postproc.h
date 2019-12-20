//
// Created by Twometer on 20/12/2019.
//

#ifndef CHESS_3D_POSTPROC_H
#define CHESS_3D_POSTPROC_H


#include "../gl/Fbo.h"

class Postproc {
private:
    static GLuint vao;

public:
    static void Initialize();

    static void Start();

    static void Stop();

    static void Copy(Fbo *src, Fbo *dst);
};


#endif //CHESS_3D_POSTPROC_H
