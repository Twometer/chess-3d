//
// Created by Twometer on 07/01/2020.
//

#include <glad/glad.h>
#include "GuiRenderer.h"
#include "../util/Loader.h"

GuiRenderer::GuiRenderer() {
    font = Loader::LoadFont("lucida");
    fontRenderer = new FontRenderer(font);
}

void GuiRenderer::Render() {
    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
    fontRenderer->Render("Hello world", 10, 10, 0.5f);

    glEnable(GL_DEPTH_TEST);
}
