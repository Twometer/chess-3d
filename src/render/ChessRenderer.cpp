//
// Created by Twometer on 16/12/2019.
//

#include <glm/gtc/matrix_transform.hpp>
#include "ChessRenderer.h"
#include "../util/Logger.h"
#include "../util/Loader.h"
#include "../model/Ruleset.h"
#include "../model/PieceRegistry.h"
#include "Postproc.h"

glm::vec2 ChessRenderer::viewportSize;

ChessRenderer::ChessRenderer(GLFWwindow *window) {
    this->window = window;
}

void ChessRenderer::Initialize() {
    glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_TEXTURE_2D);
    glCullFace(GL_FRONT);

    Logger::Info("Loading models...");
    PieceRegistry::Initialize();
    Postproc::Initialize();

    Logger::Info("Loading ruleset...");
    Ruleset *ruleset = Ruleset::Load("assets/rules.json");

    this->camera = new Camera();
    this->board = new Board(ruleset);
    this->picker = new PickEngine(board, camera);
    board->Initialize();

    shader = new SimpleShader();
    copyShader = new CopyShader();
}

void ChessRenderer::RenderFrame() {

    fbo->Bind();
    glViewport(0, 0, viewportSize.x, viewportSize.y);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glm::mat4 worldMat = camera->CalculateMatrix(viewportSize);

    shader->Bind();
    shader->SetMvpMatrix(worldMat);

    for (int x = 0; x < 8; x++)
        for (int y = 0; y < 8; y++) {
            Piece *piece = board->GetPiece(glm::vec2(x, y));
            if (piece == nullptr) continue;

            glm::vec3 offset(x, 0, y);
            if (piece == selectedPiece)
                offset.y += 0.5;

            shader->SetOffset(offset * glm::vec3(2, 2, 2));

            Model *model = PieceRegistry::GetModel(piece->type);
            model->Draw();
        }

    fbo->Unbind();


    glDisable(GL_CULL_FACE);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    copyShader->Bind();
    Postproc::Start();
    Postproc::Copy(fbo, nullptr);
    Postproc::Stop();
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
    this->fbo = new Fbo(viewportSize.x, viewportSize.y, DepthBufferType::DEPTH_RBUF);
}

void ChessRenderer::OnClick() {
    double mouseX, mouseY;
    glfwGetCursorPos(window, &mouseX, &mouseY);

    Piece *piece = picker->Pick((int) mouseX, (int) mouseY);
    selectedPiece = piece;
}

