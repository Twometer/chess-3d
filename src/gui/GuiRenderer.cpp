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

    glEnable(GL_DEPTH_TEST);
}