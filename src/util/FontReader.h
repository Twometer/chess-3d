//
// Created by Twometer on 07/01/2020.
//

#ifndef CHESS_3D_FONTREADER_H
#define CHESS_3D_FONTREADER_H


#include <fstream>
#include "../gui/font/Font.h"

class FontReader {

private:
    static int ParseProperty(const std::string &line, const std::string &property);

    static Glyph *ParseGlyph(const std::string &line);

    static bool IsGlyph(const std::string &line);

public:
    static Font *ReadFont(std::ifstream &stream);

};


#endif //CHESS_3D_FONTREADER_H
