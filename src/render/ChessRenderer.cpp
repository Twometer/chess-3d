//
// Created by Twometer on 16/12/2019.
//

#include "ChessRenderer.h"
#include "../util/Logger.h"
#include "../model/Ruleset.h"
#include "../util/Loader.h"

GLuint shader;
GLuint matLoc;

ChessRenderer::ChessRenderer(GLFWwindow *window) {
    this->window = window;
}

void ChessRenderer::Initialize() {
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.8f, 0.8f, 0.8f, 1.0f);

    Logger::Info("Loading ruleset...");
    Ruleset *ruleset = Ruleset::Load("assets/rules.json");

    this->camera = new Camera();
    this->board = new Board(ruleset);
    board->Initialize();

    shader = Loader::LoadShader("simple");
    matLoc = glGetUniformLocation(shader, "mvpMatrix");
    testModel = Loader::LoadModel("bishop.stl");
}

void ChessRenderer::RenderFrame() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glm::mat4 worldMat = camera->CalculateMatrix(viewportSize);

    glUseProgram(shader);
    glUniformMatrix4fv(matLoc, 1, GL_FALSE, &worldMat[0][0]);
    testModel->Draw();

    HandleInput();
}

void ChessRenderer::HandleInput() {
    bool focused = glfwGetWindowAttrib(window, GLFW_FOCUSED) == GLFW_TRUE;
    if (!focused) return;

    double mouseX, mouseY;
    glfwGetCursorPos(window, &mouseX, &mouseY);

    glfwSetCursorPos(window, viewportSize.x / 2, viewportSize.y / 2);
    camera->rotation.x += 0.1 * (viewportSize.x / 2 - mouseX);
    camera->rotation.y += 0.1 * (viewportSize.y / 2 - mouseY);
    camera->rotation.y = glm::clamp(camera->rotation.y, -90.0f, 90.0f);

    glm::vec3 directionMovement(
            sin(glm::radians(camera->rotation.x)),
            0,
            cos(glm::radians(camera->rotation.x))
    );

    glm::vec3 directionRight(
            sin(glm::radians(camera->rotation.x) - 1.575),
            0,
            cos(glm::radians(camera->rotation.x) - 1.575)
    );

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        camera->position.x += 0.1 * directionMovement.x;
        camera->position.z += 0.1 * directionMovement.z;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        camera->position.x -= 0.1 * directionRight.x;
        camera->position.z -= 0.1 * directionRight.z;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        camera->position.x -= 0.1 * directionMovement.x;
        camera->position.z -= 0.1 * directionMovement.z;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        camera->position.x += 0.1 * directionRight.x;
        camera->position.z += 0.1 * directionRight.z;
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        camera->position.y += 0.1;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
        camera->position.y -= 0.1;
    }
}

