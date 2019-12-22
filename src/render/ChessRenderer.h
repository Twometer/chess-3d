//
// Created by Twometer on 16/12/2019.
//

#ifndef CHESS_3D_CHESSRENDERER_H
#define CHESS_3D_CHESSRENDERER_H

#include "../model/Board.h"
#include "../gl/Model.h"
#include "PickEngine.h"
#include "Camera.h"
#include "shaders/BoardShader.h"
#include "shaders/CopyShader.h"
#include "shaders/SelectionShader.h"
#include "shaders/HBlurShader.h"
#include "shaders/VBlurShader.h"
#include "SkyboxRenderer.h"
#include <GLFW/glfw3.h>

class ChessRenderer {
private:
    GLFWwindow *window;

    Board *board;

    Camera *camera;
    BoardShader *boardShader;
    CopyShader *copyShader;
    SelectionShader *selectionShader;
    HBlurShader *hGaussShader;
    VBlurShader *vGaussShader;

    PickEngine *picker;
    Piece *selectedPiece = nullptr;
    Fbo *fbo = nullptr;
    Fbo *fbo2 = nullptr;
    Fbo *fbo3 = nullptr;

    SkyboxRenderer *skyboxRenderer;
    Model *bottomModel;

    static glm::vec2 viewportSize;
    glm::vec2 windowSize;

    void HandleInput();

    void DrawSelection(glm::mat4 mat, glm::vec2 position);

public:
    explicit ChessRenderer(GLFWwindow *window);

    void Initialize();

    void RenderFrame();

    void OnScroll(glm::vec2 scrollVector);

    void OnWindowSizeChanged(glm::vec2 windowSize);

    void OnViewportSizeChanged(glm::vec2 viewportSize);

    void OnClick();

    static inline glm::vec2 GetViewportSize() {
        return viewportSize;
    }
};


#endif //CHESS_3D_CHESSRENDERER_H
