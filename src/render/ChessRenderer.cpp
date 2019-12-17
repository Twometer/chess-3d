//
// Created by Twometer on 16/12/2019.
//

#include <glm/gtc/matrix_transform.hpp>
#include "ChessRenderer.h"
#include "../util/Logger.h"
#include "../util/Loader.h"
#include "../model/Ruleset.h"
#include "../model/PieceRegistry.h"

GLuint shader;
GLuint matLoc;
GLuint vecLoc;

ChessRenderer::ChessRenderer(GLFWwindow *window) {
    this->window = window;
}

void ChessRenderer::Initialize() {
    glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);

    Logger::Info("Loading models...");
    PieceRegistry::Initialize();

    Logger::Info("Loading ruleset...");
    Ruleset *ruleset = Ruleset::Load("assets/rules.json");

    this->camera = new Camera();
    this->board = new Board(ruleset);
    board->Initialize();

    shader = Loader::LoadShader("simple");
    matLoc = glGetUniformLocation(shader, "mvpMatrix");
    vecLoc = glGetUniformLocation(shader, "offset");
}

void ChessRenderer::RenderFrame() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glm::mat4 worldMat = camera->CalculateMatrix(viewportSize);

    glUseProgram(shader);
    glUniformMatrix4fv(matLoc, 1, GL_FALSE, &worldMat[0][0]);

    for (int x = 0; x < 8; x++)
        for (int y = 0; y < 8; y++) {
            Piece *piece = board->GetPiece(glm::vec2(x, y));
            if (piece == nullptr) continue;

            glm::vec3 offset(x, 0, y);
            glUniform3f(vecLoc, offset.x * 2, offset.y * 2, offset.z * 2);

            Model *model = PieceRegistry::GetModel(piece->type);
            model->Draw();
        }


    HandleInput();
}

void ChessRenderer::HandleInput() {
    bool focused = glfwGetWindowAttrib(window, GLFW_FOCUSED) == GLFW_TRUE;
    if (!focused) return;

    double mouseX, mouseY;
    glfwGetCursorPos(window, &mouseX, &mouseY);
    glfwSetCursorPos(window, windowSize.x / 2.0f, windowSize.y / 2.0f);

    camera->rotation.x += 0.1 * (windowSize.x / 2.0f - mouseX);
    camera->rotation.y -= 0.1 * (windowSize.y / 2.0f - mouseY);
    camera->position.x = 7;
    camera->position.z = 7;
}

void ChessRenderer::OnScroll(glm::vec2 scrollVector) {
    camera->zoom += scrollVector.y;
}

void ChessRenderer::OnWindowSizeChanged(glm::vec2 windowSize) {
    this->windowSize = windowSize;
}

void ChessRenderer::OnViewportSizeChanged(glm::vec2 viewportSize) {
    glViewport(0, 0, viewportSize.x, viewportSize.y);
    this->viewportSize = viewportSize;
}

