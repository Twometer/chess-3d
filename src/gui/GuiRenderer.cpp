//
// Created by Twometer on 07/01/2020.
//

#include <glad/glad.h>
#include "GuiRenderer.h"
#include "../util/Loader.h"


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

    if (gameState->currentTeam == Black)
        fontRenderer->Render("Schwarz ist am Zug", 5, 5, 0.5);
    else
        fontRenderer->Render("Weiss ist am Zug", 5, 5, 0.5);

    glEnable(GL_DEPTH_TEST);
}
