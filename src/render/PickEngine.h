//
// Created by Twometer on 18/12/2019.
//

#ifndef CHESS_3D_PICKENGINE_H
#define CHESS_3D_PICKENGINE_H

#include "../gl/Fbo.h"
#include "Camera.h"
#include "../model/Board.h"
#include "../model/Piece.h"
#include "shaders/PickShader.h"

class PickEngine {

private:
    Board *board;

    Camera *camera;

    Fbo *fbo;

    PickShader *shader;

public:
    PickEngine(Board *board, Camera *camera);

    void Resize(int width, int height);

    Piece *Pick(int x, int y);


};


#endif //CHESS_3D_PICKENGINE_H
