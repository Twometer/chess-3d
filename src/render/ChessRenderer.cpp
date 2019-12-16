//
// Created by Twometer on 16/12/2019.
//

#include "ChessRenderer.h"
#include "../util/Logger.h"
#include "../model/Ruleset.h"
#include "../util/Loader.h"

GLuint shader;
GLuint matLoc;

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
}
