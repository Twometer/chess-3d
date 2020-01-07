//
// Created by Twometer on 07/01/2020.
//

#ifndef CHESS_3D_FONT_H
#define CHESS_3D_FONT_H

#include <map>
#include <glad/glad.h>
#include "Glyph.h"
#include "../../util/Texture.h"

struct Font {
    std::map<int, Glyph *> glyphs;
    Texture texture;
};


#endif //CHESS_3D_FONT_H
