//
// Created by Twometer on 16/12/2019.
//

#ifndef CHESS_3D_CHESSRENDERER_H
#define CHESS_3D_CHESSRENDERER_H

#include "../model/Board.h"
#include "../gl/Model.h"
#include "Camera.h"

class ChessRenderer {
private:
    Board *board;

    Camera *camera;

    glm::vec2 viewportSize;

    Model *testModel;
public:
    void Initialize();

    void RenderFrame();

    void OnViewportSizeChanged(glm::vec2 viewportSize) {
        this->viewportSize = viewportSize;
    }
};


#endif //CHESS_3D_CHESSRENDERER_H
