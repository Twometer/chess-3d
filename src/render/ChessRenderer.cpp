//
// Created by Twometer on 16/12/2019.
//

#include <glm/gtc/matrix_transform.hpp>
#include "ChessRenderer.h"
#include "../util/Logger.h"
#include "../model/Ruleset.h"
#include "../model/PieceRegistry.h"
#include "Postproc.h"

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

    boardShader = new SimpleShader();
    copyShader = new CopyShader();
    selectionShader = new SelectionShader();
    hGaussShader = new HGaussShader();
    vGaussShader = new VGaussShader();
}

void ChessRenderer::RenderFrame() {


    glViewport(0, 0, viewportSize.x, viewportSize.y);
    glClearColor(0.8f, 0.8f, 0.8f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glm::mat4 worldMat = camera->CalculateMatrix(viewportSize);

    boardShader->Bind();
    boardShader->SetMvpMatrix(worldMat);

    for (int x = 0; x < 8; x++)
        for (int y = 0; y < 8; y++) {
            Piece *piece = board->GetPiece(glm::vec2(x, y));
            if (piece == nullptr) continue;

            glm::vec3 offset(x, 0, y);
            if (piece == selectedPiece) {
                continue;
            }

            boardShader->SetOffset(offset * glm::vec3(2, 2, 2));

            Model *model = PieceRegistry::GetModel(piece->type);
            model->Draw();
        }


    fbo->Bind();
    glClearColor(1.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    selectionShader->Bind();
    selectionShader->SetMvpMatrix(worldMat);
    for (int x = 0; x < 8; x++)
        for (int y = 0; y < 8; y++) {
            Piece *piece = board->GetPiece(glm::vec2(x, y));
            if (piece == nullptr) continue;

            if (piece != selectedPiece) {
                continue;
            }
            glm::vec3 offset(x, 0, y);

            selectionShader->SetPosition(glm::vec2(x, y));

            Model *model = PieceRegistry::GetModel(piece->type);
            model->Draw();
        }
    fbo->Unbind();

    fbo2->Bind();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    boardShader->Bind();
    boardShader->SetMvpMatrix(worldMat);
    for (int x = 0; x < 8; x++)
        for (int y = 0; y < 8; y++) {
            Piece *piece = board->GetPiece(glm::vec2(x, y));
            if (piece == nullptr) continue;

            if (piece != selectedPiece) {
                continue;
            }
            glm::vec3 offset(x, 0, y);

            boardShader->SetOffset(offset * glm::vec3(2, 2, 2));

            Model *model = PieceRegistry::GetModel(piece->type);
            model->Draw();
        }
    fbo2->Unbind();

    glDisable(GL_CULL_FACE);
    glDepthMask(false);

    // TODO Why does copying from FBO to FBO not work?
    Postproc::Start();
    hGaussShader->Bind();
    hGaussShader->SetTargetWidth(viewportSize.x / 2);
    Postproc::Copy(fbo, nullptr);

    vGaussShader->Bind();
    vGaussShader->SetTargetHeight(viewportSize.y / 2);
    Postproc::Copy(fbo, nullptr);

    copyShader->Bind();
    Postproc::Copy(fbo2, nullptr);

    Postproc::Stop();
    glDepthMask(true);
    glEnable(GL_CULL_FACE);


    HandleInput();
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
    this->fbo = new Fbo(viewportSize.x / 2, viewportSize.y / 2, DepthBufferType::DEPTH_RBUF);

    delete this->fbo2;
    this->fbo2 = new Fbo(viewportSize.x, viewportSize.y, DepthBufferType::DEPTH_RBUF);
}

void ChessRenderer::OnClick() {
    double mouseX, mouseY;
    glfwGetCursorPos(window, &mouseX, &mouseY);

    Piece *piece = picker->Pick((int) mouseX, (int) mouseY);
    selectedPiece = piece;
}

