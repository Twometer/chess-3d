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

    if (gameState->currentTeam == Black)
        fontRenderer->RenderCentered("Schwarz ist am Zug", viewport.x / 2, viewport.y - 100, 0.75);
    else
        fontRenderer->RenderCentered("Weiss ist am Zug", viewport.x / 2, viewport.y - 100, 0.75);


    if (gameState->gameStart > 0) {
        double elapsed = glfwGetTime() - gameState->gameStart;
        fontRenderer->RenderCentered(FormatTime(elapsed), viewport.x / 2, 5, 0.75);
    } else if (gameState->gameStop > 0) {
        double elapsed = gameState->gameStop - gameState->gameStart;
        fontRenderer->RenderCentered(FormatTime(elapsed), viewport.x / 2, 5, 0.75);
    } else {
        fontRenderer->RenderCentered("00:00:00", viewport.x / 2, 5, 0.75);
    }

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
