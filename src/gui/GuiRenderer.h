//
// Created by Twometer on 07/01/2020.
//

#ifndef CHESS_3D_GUIRENDERER_H
#define CHESS_3D_GUIRENDERER_H


#include "font/Font.h"
#include "../render/shaders/FontShader.h"
#include "font/FontRenderer.h"
#include "Debug.h"

class GuiRenderer {
private:
    Font *font;

    FontRenderer *fontRenderer;

    Debug *debug;

public:
    bool showDebug = false;

    GuiRenderer();

    void Render();

};


#endif //CHESS_3D_GUIRENDERER_H
