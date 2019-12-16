//
// Created by Twometer on 16/12/2019.
//

#ifndef CHESS_3D_CHESSRENDERER_H
#define CHESS_3D_CHESSRENDERER_H

#include "../model/Board.h"
#include "../gl/Model.h"
#include "Camera.h"
#include <GLFW/glfw3.h>

class ChessRenderer {
private:
    GLFWwindow *window;

    Board *board;

    Camera *camera;

    glm::vec2 viewportSize;

    void HandleInput();

public:
    explicit ChessRenderer(GLFWwindow *window);

    void Initialize();

    void RenderFrame();

    void OnViewportSizeChanged(glm::vec2 viewportSize) {
        this->viewportSize = viewportSize;
    }
};


#endif //CHESS_3D_CHESSRENDERER_H
