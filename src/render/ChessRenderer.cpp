//
// Created by Twometer on 16/12/2019.
//

#include "ChessRenderer.h"
#include "../util/Logger.h"
#include "../model/Ruleset.h"
#include "../util/Loader.h"

void ChessRenderer::Initialize() {
    Logger::Info("Loading ruleset...");
    Ruleset *ruleset = Ruleset::Load("assets/rules.json");
    this->board = new Board(ruleset);
    board->Initialize();

    Model *model = Loader::LoadModel("bishop.stl");
}

void ChessRenderer::RenderFrame() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glm::mat4 worldMat = camera->CalculateMatrix(viewportSize);


}
