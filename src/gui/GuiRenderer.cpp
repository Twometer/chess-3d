//
// Created by Twometer on 07/01/2020.
//

#include <glad/glad.h>
#include "GuiRenderer.h"
#include "../util/Loader.h"
#include "../render/ChessRenderer.h"


GuiRenderer::GuiRenderer(GameState *gameState) {
    this->gameState = gameState;
    debug = new Debug();
    font = Loader::LoadFont("nirmala");
    fontRenderer = new FontRenderer(font);
}

void GuiRenderer::Render() {
    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);

    if (showDebug)
        debug->Render(fontRenderer);

    glm::vec2 viewport = ChessRenderer::GetViewportSize();

    double elapsed;
    switch (gameState->runState) {
        case RunState::NotStarted:
            fontRenderer->RenderCentered("Weiss beginnt das Spiel", viewport.x / 2, viewport.y - 100, 0.75);
            elapsed = 0;
            break;
        case RunState::Running:
            elapsed = glfwGetTime() - gameState->gameStart;

            if (gameState->currentTeam == Team::Black)
                fontRenderer->RenderCentered("Schwarz ist am Zug", viewport.x / 2, viewport.y - 100, 0.75);
            else
                fontRenderer->RenderCentered("Weiss ist am Zug", viewport.x / 2, viewport.y - 100, 0.75);
            break;
        case RunState::Ended:
            elapsed = gameState->gameStop - gameState->gameStart;

            fontRenderer->RenderCentered("Schachmatt!", viewport.x / 2, viewport.y / 2 - 150, 1.f);

            if (gameState->currentTeam == Team::Black)
                fontRenderer->RenderCentered("Schwarz hat gewonnen", viewport.x / 2, viewport.y / 2, 1.f);
            else
                fontRenderer->RenderCentered("Weiss hat gewonnen", viewport.x / 2, viewport.y / 2, 1.f);
            break;
    }

    fontRenderer->RenderCentered(FormatTime(elapsed), viewport.x / 2, 5, 0.75);

    glEnable(GL_DEPTH_TEST);
}

std::string GuiRenderer::FormatTime(double time) {
    int secs = (int) time % 60;
    int mins = ((int) time / 60) % 60;
    int hours = (int) time / 60 / 60;

    std::string str_secs = (secs < 10 ? "0" : "") + std::to_string(secs);
    std::string str_mins = (mins < 10 ? "0" : "") + std::to_string(mins);
    std::string str_hours = (hours < 10 ? "0" : "") + std::to_string(hours);

    return str_hours + ":" + str_mins + ":" + str_secs;
}
