//
// Created by Twometer on 16/12/2019.
//

#ifndef CHESS_3D_CHESSRENDERER_H
#define CHESS_3D_CHESSRENDERER_H

#include "../model/Board.h"
#include "../gl/Model.h"
#include "PickEngine.h"
#include "Camera.h"
#include <GLFW/glfw3.h>

class ChessRenderer {
private:
    GLFWwindow *window;

    Board *board;

    Camera *camera;

    PickEngine *picker;
    Piece *selectedPiece;

    glm::vec2 viewportSize;
    glm::vec2 windowSize;

    void HandleInput();

public:
    explicit ChessRenderer(GLFWwindow *window);

    void Initialize();

    void RenderFrame();

    void OnScroll(glm::vec2 scrollVector);

    void OnWindowSizeChanged(glm::vec2 windowSize);

    void OnViewportSizeChanged(glm::vec2 viewportSize);

    void OnClick();
};


#endif //CHESS_3D_CHESSRENDERER_H
