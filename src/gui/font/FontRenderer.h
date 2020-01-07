//
// Created by Twometer on 07/01/2020.
//

#ifndef CHESS_3D_FONTRENDERER_H
#define CHESS_3D_FONTRENDERER_H

#define WHITE glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)

#include "Font.h"
#include "../../render/shaders/FontShader.h"

class FontRenderer {

private:
    Font *font;

    FontShader *fontShader;

    GLuint vao;
    GLuint vbo;

public:

    explicit FontRenderer(Font *font);

    int GetFontWidth(const std::string &value, float fontSize);

    void RenderCentered(const std::string &value, int x, int y, float fontSize = 1.0f, glm::vec4 color = WHITE);

    void Render(const std::string &value, int x, int y, float fontSize = 1.0f, glm::vec4 color = WHITE);

};


#endif //CHESS_3D_FONTRENDERER_H
