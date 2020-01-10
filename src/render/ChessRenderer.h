//
// Created by Twometer on 16/12/2019.
//

#ifndef CHESS_3D_CHESSRENDERER_H
#define CHESS_3D_CHESSRENDERER_H

#include "../model/Board.h"
#include "../gl/Model.h"
#include "PickEngine.h"
#include "Camera.h"
#include "../anim/Timer.h"
#include "shaders/BoardShader.h"
#include "shaders/PieceShader.h"
#include "shaders/CopyShader.h"
#include "shaders/ShadelessShader.h"
#include "shaders/HBlurShader.h"
#include "shaders/VBlurShader.h"
#include "SkyboxRenderer.h"
#include "../gui/GuiRenderer.h"
#include <GLFW/glfw3.h>

class ChessRenderer {
private:
    GLFWwindow *window;
    static glm::vec2 viewportSize;

    static Board *board;
    GameState *gameState;
    Piece *selectedPiece = nullptr;

    Camera *camera;
    SkyboxRenderer *skyboxRenderer;
    GuiRenderer *guiRenderer;
    PickEngine *picker;
    Timer *timer;

    BoardShader *boardShader;
    PieceShader *pieceShader;
    CopyShader *copyShader;
    ShadelessShader *shadelessShader;
    HBlurShader *hGaussShader;
    VBlurShader *vGaussShader;

    Fbo *fbo = nullptr;
    Fbo *fbo2 = nullptr;
    Fbo *fbo3 = nullptr;

    Model *hintModel;
    Model *boardModel;
    Model *boardBodyModel;


    void HandleInput();

    glm::mat4 GetModelMatrix(Piece *piece);

    void DrawPiece(Piece *piece);

    void DrawSelection(glm::mat4 mat);

    void DrawHints();

    void DrawCheck(Team team);

    void DrawCaptured(Team team);

    void SelectPiece(Piece *piece);

    void MovePiece(Piece *piece, glm::vec2 dst);

public:
    explicit ChessRenderer(GLFWwindow *window);

    void Initialize();

    void RenderFrame();

    void OnScroll(glm::vec2 scrollVector);

    void OnViewportSizeChanged(glm::vec2 viewportSize);

    void OnKeyPressed(int key);

    void OnClick();

    void OnTick();

    static inline glm::vec2 GetViewportSize() {
        return viewportSize;
    }

    static inline Board *GetBoard() {
        return board;
    }
};


#endif //CHESS_3D_CHESSRENDERER_H
