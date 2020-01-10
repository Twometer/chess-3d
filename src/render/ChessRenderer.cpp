//
// Created by Twometer on 16/12/2019.
//

#include <glm/gtc/matrix_transform.hpp>
#include "ChessRenderer.h"
#include "../util/Logger.h"
#include "../model/Ruleset.h"
#include "../model/PieceRegistry.h"
#include "Postproc.h"
#include "../util/Loader.h"

glm::vec2 ChessRenderer::viewportSize;
Board *ChessRenderer::board;

ChessRenderer::ChessRenderer(GLFWwindow *window) {
    this->window = window;
}

void ChessRenderer::Initialize() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_TEXTURE_CUBE_MAP);
    glEnable(GL_MULTISAMPLE);
    glCullFace(GL_FRONT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    Logger::Info("Loading models...");
    PieceRegistry::Initialize();
    Postproc::Initialize();

    Logger::Info("Loading ruleset...");
    Ruleset *ruleset = Ruleset::Load("assets/rules.json");

    this->camera = new Camera();
    this->board = new Board(ruleset);
    this->gameState = new GameState();
    this->picker = new PickEngine(board, camera);
    board->Initialize();

    boardShader = new BoardShader();
    pieceShader = new PieceShader();
    copyShader = new CopyShader();
    shadelessShader = new ShadelessShader();
    hGaussShader = new HBlurShader();
    vGaussShader = new VBlurShader();

    skyboxRenderer = new SkyboxRenderer();
    hintModel = Loader::LoadModel("hint.glm");
    boardModel = Loader::LoadModel("board.glm");
    boardBodyModel = Loader::LoadModel("board.body.glm");

    guiRenderer = new GuiRenderer(gameState);
}

void ChessRenderer::RenderFrame() {
    glViewport(0, 0, viewportSize.x, viewportSize.y);
    glClearColor(0.8f, 0.8f, 0.8f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glm::mat4 cameraMat = camera->CalculateMatrix(viewportSize);

    boardShader->Bind();
    boardShader->SetCameraMatrix(cameraMat);
    boardModel->Render();

    pieceShader->Bind();
    pieceShader->SetCameraMatrix(cameraMat);
    pieceShader->SetCameraPos(camera->GetEyePosition());
    pieceShader->SetModelMatrix(glm::mat4(1.0f));
    pieceShader->SetPosition(glm::vec2());
    pieceShader->SetEnvironFac(1.0f);
    pieceShader->SetDiffuseFac(0.8f);
    pieceShader->SetDiffuseColor(glm::vec3(0.75f, 0.75f, 0.75f));
    boardBodyModel->Render();

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxRenderer->GetTexture());

    for (int x = 0; x < 8; x++)
        for (int y = 0; y < 8; y++) {
            Piece *piece = board->GetPiece(glm::vec2(x, y));
            if (piece == nullptr || piece == selectedPiece)
                continue;

            pieceShader->SetModelMatrix(GetModelMatrix(piece));
            DrawPiece(piece);
        }
    glDisable(GL_CULL_FACE);
    skyboxRenderer->Render(camera);

    if (gameState->runState == RunState::Running) {
        glEnable(GL_CULL_FACE);
        shadelessShader->Bind();
        shadelessShader->SetCameraMatrix(cameraMat);
        DrawCheck(Team::White);
        DrawCheck(Team::Black);
        DrawHints();
        DrawSelection(cameraMat);
    }

    guiRenderer->Render();

    glEnable(GL_CULL_FACE);
    HandleInput();
}

void ChessRenderer::DrawHints() {
    if (selectedPiece == nullptr)
        return;

    for (int x = 0; x < 8; x++)
        for (int y = 0; y < 8; y++) {
            MoveResultType type = selectedPiece->rule->TryMove(selectedPiece, glm::vec2(x, y)).resultType;
            shadelessShader->SetPosition(glm::vec2(x, y));

            if (type == MoveResultType::OK) {
                shadelessShader->SetColor(glm::vec4(0, 0.62f, 1.0f, 1.0f));
                shadelessShader->SetModelMatrix(glm::mat4(1.0f));
                hintModel->Render();
            } else if (type == MoveResultType::Hit) {
                shadelessShader->SetColor(glm::vec4(1.0f, 0.38f, 0.0f, 0.5f));
                shadelessShader->SetModelMatrix(glm::scale(glm::mat4(1.0f), glm::vec3(3.0f, 1.0f, 3.0f)));
                hintModel->Render();
            }
        }
}

void ChessRenderer::DrawCheck(Team team) {
    Piece *king = board->FindPiece(PieceType::King, team);
    if (king == nullptr) // If a king is missing, we are in endgame
        return;

    // Flash the king's hitbox when he's in check
    float ftime = static_cast<float>(glfwGetTime());
    float scale = (glm::sin(10.f * ftime) * 0.35f) + 3.25f;

    if (board->IsInCheck(king)) {
        shadelessShader->SetPosition(king->position);
        shadelessShader->SetColor(glm::vec4(1.0f, 0.05f, 0.05f, 1.0f));
        shadelessShader->SetModelMatrix(glm::scale(glm::mat4(1.0f), glm::vec3(scale, 1.0f, scale)));
        hintModel->Render();
    }
}


void ChessRenderer::DrawSelection(glm::mat4 mat) {
    if (selectedPiece == nullptr)
        return;

    // Draw selected model
    glm::vec2 position = selectedPiece->position;

    // Outline pass
    fbo->Bind();
    glClearColor(0, 0.62f, 1.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    shadelessShader->Bind();
    shadelessShader->SetColor(glm::vec4(0, 0.62f, 1.0f, 1.0f));
    shadelessShader->SetCameraMatrix(mat);
    shadelessShader->SetModelMatrix(GetModelMatrix(selectedPiece));
    shadelessShader->SetPosition(position);
    PieceRegistry::GetModel(selectedPiece->type)->Render();
    fbo->Unbind();

    // Non-Outline Pass
    fbo2->Bind();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    pieceShader->Bind();
    pieceShader->SetCameraMatrix(mat);
    pieceShader->SetModelMatrix(GetModelMatrix(selectedPiece));
    DrawPiece(selectedPiece);
    fbo2->Unbind();

    glDisable(GL_CULL_FACE);
    glDepthMask(false);

    Postproc::Start();

    hGaussShader->Bind();
    hGaussShader->SetTargetWidth(fbo3->GetWidth());
    Postproc::Copy(fbo, fbo3);

    vGaussShader->Bind();
    vGaussShader->SetTargetHeight(viewportSize.y);
    for (int i = 0; i < 5; i++)
        Postproc::Copy(fbo3, nullptr);

    copyShader->Bind();
    Postproc::Copy(fbo2, nullptr);
    glDepthMask(true);

    Postproc::Stop();

    glEnable(GL_CULL_FACE);
}


void ChessRenderer::DrawPiece(Piece *piece) {
    // Goal: White is reflective, black is glassy

    pieceShader->SetDiffuseColor(
            piece->team == Team::White ? glm::vec3(1.0f, 1.0f, 1.0f) : glm::vec3(0.15f, 0.15f, 0.15f));

    // Environment blending factor. 0 means full reflection, 1 means full refraction
    float envFac = piece->team == Team::White ? 0.0f : 0.95f;
    pieceShader->SetEnvironFac(envFac);

    // Diffuse blending factor. 0 means full diffuse, 1 means full environment
    float difFac = piece->team == Team::White ? 0.75f : 0.92f;
    pieceShader->SetDiffuseFac(difFac);

    pieceShader->SetPosition(piece->position);
    PieceRegistry::GetModel(piece->type)->Render();
}

glm::mat4 ChessRenderer::GetModelMatrix(Piece *piece) {
    if (piece->type == PieceType::Knight || piece->type == PieceType::King) {
        float rot = glm::radians(piece->team == Team::White ? -90.f : 90.f);
        return glm::rotate(glm::mat4(1.0f), rot, glm::vec3(0, 1, 0));
    }
    return glm::mat4(1.0); // Identity
}

void ChessRenderer::HandleInput() {
    bool focused = glfwGetWindowAttrib(window, GLFW_FOCUSED) == GLFW_TRUE;
    if (!focused) return;

    double mouseX, mouseY;
    glfwGetCursorPos(window, &mouseX, &mouseY);

    static double mouseXLast, mouseYLast;

    if ((mouseXLast != mouseX || mouseYLast != mouseY) &&
        glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
        camera->rotation.x -= 0.2 * (mouseX - mouseXLast);
        camera->rotation.y += 0.2 * (mouseY - mouseYLast);

        camera->rotation.y = glm::clamp(camera->rotation.y, -170.f, -90.f);
    }

    mouseXLast = mouseX;
    mouseYLast = mouseY;

    camera->position.x = 7;
    camera->position.z = 7;
}

void ChessRenderer::OnScroll(glm::vec2 scrollVector) {
    camera->zoom -= scrollVector.y;
    camera->zoom = glm::clamp(camera->zoom, 1.f, 25.0f);
}

void ChessRenderer::OnViewportSizeChanged(glm::vec2 viewportSize) {
    this->viewportSize = viewportSize;
    this->picker->Resize(viewportSize.x, viewportSize.y);

    delete this->fbo;
    this->fbo = new Fbo(viewportSize.x, viewportSize.y, DepthBufferType::DepthRbuf);

    delete this->fbo2;
    this->fbo2 = new Fbo(viewportSize.x, viewportSize.y, DepthBufferType::DepthRbuf);

    delete this->fbo3;
    this->fbo3 = new Fbo(viewportSize.x, viewportSize.y, DepthBufferType::None);
}

void ChessRenderer::OnClick() {
    if (gameState->runState == RunState::Ended)
        return;

    double mouseX, mouseY;
    glfwGetCursorPos(window, &mouseX, &mouseY);

    PickResult pickResult = picker->Pick((int) mouseX, (int) mouseY);
    glm::vec2 vec = pickResult.boardPos;

    switch (pickResult.type) {
        case PickResultType::Piece:
            if (selectedPiece != nullptr && pickResult.piece->team != selectedPiece->team)
                MovePiece(selectedPiece, pickResult.piece->position);
            else
                SelectPiece(pickResult.piece);
            break;

        case PickResultType::Board:
            if (!board->CheckPosition(vec)) {
                selectedPiece = nullptr;
            } else {
                if (selectedPiece == nullptr)
                    SelectPiece(board->GetPiece(vec));
                else
                    MovePiece(selectedPiece, vec);
            }
            break;

        case PickResultType::Miss:
            selectedPiece = nullptr;
            break;
    }
}

void ChessRenderer::OnKeyPressed(int key) {
    if (key == GLFW_KEY_F3)
        guiRenderer->showDebug = !guiRenderer->showDebug;
}

void ChessRenderer::SelectPiece(Piece *piece) {
    if (piece == nullptr || piece->team == gameState->currentTeam)
        selectedPiece = piece;

    if (selectedPiece != nullptr && gameState->runState == RunState::NotStarted)
        gameState->StartGame();
}

void ChessRenderer::MovePiece(Piece *piece, glm::vec2 dst) {
    MoveResult result = board->Move(piece->position, dst);

    switch (result.resultType) {
        case MoveResultType::Hit:
            if (result.pieceHit == PieceType::King) {
                selectedPiece = nullptr;
                gameState->StopGame();
                break;
            }
        case MoveResultType::OK:
            selectedPiece = nullptr;
            gameState->SwitchTeam();
            break;

        case MoveResultType::Invalid:
            // Do nothing
            break;
    }
}
