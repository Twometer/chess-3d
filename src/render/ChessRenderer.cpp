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

ChessRenderer::ChessRenderer(GLFWwindow *window) {
    this->window = window;
}

void ChessRenderer::Initialize() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_TEXTURE_2D);
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
    this->picker = new PickEngine(board, camera);
    board->Initialize();

    boardShader = new BoardShader();
    copyShader = new CopyShader();
    selectionShader = new SelectionShader();
    hGaussShader = new HBlurShader();
    vGaussShader = new VBlurShader();

    skyboxRenderer = new SkyboxRenderer();
    bottomModel = Loader::LoadModel("bottom.glm");
}

void ChessRenderer::RenderFrame() {
    glViewport(0, 0, viewportSize.x, viewportSize.y);
    glClearColor(0.8f, 0.8f, 0.8f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glm::mat4 worldMat = camera->CalculateMatrix(viewportSize);

    boardShader->Bind();
    boardShader->SetMvpMatrix(worldMat);

    float yaw = glm::radians(camera->rotation.x);
    float pitch = glm::radians(camera->rotation.y);

    boardShader->SetCameraPos(camera->GetEyePosition());

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxRenderer->GetTexture());
    glm::vec2 selectedPosition;

    for (int x = 0; x < 8; x++)
        for (int y = 0; y < 8; y++) {
            Piece *piece = board->GetPiece(glm::vec2(x, y));
            if (piece == nullptr) continue;

            glm::vec2 pos(x, y);
            if (piece == selectedPiece) {
                selectedPosition = pos;
                continue;
            }

            DrawPiece(piece, pos);
        }

    glDisable(GL_CULL_FACE);
    skyboxRenderer->Render(camera);

    // bottomModel->Render();
    glEnable(GL_CULL_FACE);

    if (selectedPiece != nullptr)
        DrawSelection(worldMat, selectedPosition);


    HandleInput();
}

void ChessRenderer::DrawSelection(glm::mat4 mat, glm::vec2 position) {
    // Outline pass
    fbo->Bind();
    glClearColor(0, 0.62f, 1.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    selectionShader->Bind();
    selectionShader->SetMvpMatrix(mat);
    selectionShader->SetPosition(position);
    PieceRegistry::GetModel(selectedPiece->type)->Render();
    fbo->Unbind();

    // Non-Outline Pass
    fbo2->Bind();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    boardShader->Bind();
    boardShader->SetMvpMatrix(mat);
    DrawPiece(selectedPiece, position);
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

        camera->rotation.y = glm::clamp(camera->rotation.y, -180.f, -90.f);
    }

    mouseXLast = mouseX;
    mouseYLast = mouseY;

    camera->position.x = 7;
    camera->position.z = 7;
}

void ChessRenderer::OnScroll(glm::vec2 scrollVector) {
    camera->zoom -= scrollVector.y;
    camera->zoom = glm::clamp(camera->zoom, 0.01f, 25.0f);
}

void ChessRenderer::OnWindowSizeChanged(glm::vec2 windowSize) {
    this->windowSize = windowSize;
}

void ChessRenderer::OnViewportSizeChanged(glm::vec2 viewportSize) {
    this->viewportSize = viewportSize;
    this->picker->Resize(viewportSize.x, viewportSize.y);

    delete this->fbo;
    this->fbo = new Fbo(viewportSize.x, viewportSize.y, DepthBufferType::DEPTH_RBUF);

    delete this->fbo2;
    this->fbo2 = new Fbo(viewportSize.x, viewportSize.y, DepthBufferType::DEPTH_RBUF);

    delete this->fbo3;
    this->fbo3 = new Fbo(viewportSize.x, viewportSize.y, DepthBufferType::NONE);
}

void ChessRenderer::OnClick() {
    double mouseX, mouseY;
    glfwGetCursorPos(window, &mouseX, &mouseY);

    Piece *piece = picker->Pick((int) mouseX, (int) mouseY);
    selectedPiece = piece;
}

void ChessRenderer::DrawPiece(Piece *piece, glm::vec2 position) {
    // Goal: White is reflective, black is glassy

    // Environment blending factor. 0 means full reflection, 1 means full refraction
    float envFac = piece->team == White ? 0.0f : 0.95f;
    boardShader->SetEnvironFac(envFac);

    // Diffuse blending factor. 0 means full diffuse, 1 means full environment
    float difFac = piece->team == White ? 0.8f : 0.90f;
    boardShader->SetDiffuseFac(difFac);

    boardShader->SetPosition(position);
    PieceRegistry::GetModel(piece->type)->Render();
}



