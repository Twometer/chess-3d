//
// Created by Twometer on 07/01/2020.
//

#include <glm/gtc/matrix_transform.hpp>
#include "FontRenderer.h"
#include "../../render/ChessRenderer.h"

FontRenderer::FontRenderer(Font *font) {
    this->font = font;
    this->fontShader = new FontShader();

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
}

void FontRenderer::Render(const std::string &value, float x, float y, float fontSize, glm::vec4 color) {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glBindVertexArray(vao);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, nullptr);

    glm::mat4 projectionMatrix = glm::ortho(0.0f, ChessRenderer::GetViewportSize().x,
                                            ChessRenderer::GetViewportSize().y, 0.0f);

    fontShader->Bind();
    fontShader->SetProjectionMatrix(projectionMatrix);
    fontShader->SetColor(color);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, font->texture.id);

    float tw = font->texture.width;
    float th = font->texture.height;

    for (char c : value) {
        Glyph *glyph = font->glyphs[static_cast<int>(c)];
        if (glyph == nullptr)
            continue;

        float x0 = x + glyph->xOffset * fontSize;
        float y0 = y + glyph->yOffset * fontSize;
        float x1 = x0 + glyph->width * fontSize;
        float y1 = y0 + glyph->height * fontSize;

        float u0 = glyph->x / tw;
        float v0 = glyph->y / th;
        float u1 = (glyph->x + glyph->width) / tw;
        float v1 = (glyph->y + glyph->height) / th;

        GLfloat box[4][4] = {
                x0, y0, u0, v0,
                x1, y0, u1, v0,
                x0, y1, u0, v1,
                x1, y1, u1, v1
        };
        glBufferData(GL_ARRAY_BUFFER, sizeof box, box, GL_DYNAMIC_DRAW);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

        x += (glyph->advance - 15.0f) * fontSize;
    }

    fontShader->Unbind();

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDisableVertexAttribArray(0);
    glBindVertexArray(0);
}

void FontRenderer::RenderCentered(const std::string &value, float x, float y, float fontSize, glm::vec4 color) {
    x -= GetFontWidth(value, fontSize) / 2;
    Render(value, x, y, fontSize, color);
}

int FontRenderer::GetFontWidth(const std::string &value, float fontSize) {
    float x = 0;
    for (char c : value) {
        Glyph *glyph = font->glyphs[static_cast<int>(c)];
        if (glyph == nullptr)
            continue;
        x += (glyph->advance - 15.0f) * fontSize;
    }
    return (int) x;
}

void FontRenderer::RenderCenteredShadow(const std::string &value, float x, float y, float fontSize, glm::vec4 color) {
    RenderCentered(value, x + 1.5f, y + 1.75f, fontSize, BLACK);
    RenderCentered(value, x, y, fontSize, color);
}


