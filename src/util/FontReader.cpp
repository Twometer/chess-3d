//
// Created by Twometer on 07/01/2020.
//

#include "FontReader.h"

int FontReader::ParseProperty(const std::string &line, const std::string &property) {
    std::string key = property + "=";
    int offset = line.find(key);
    if (offset == std::string::npos)
        throw std::runtime_error("Failed to read invalid font file");

    std::string substr = line.substr(offset + key.length());
    std::string value = substr.substr(0, substr.find(" "));

    return std::stoi(value);
}

Glyph *FontReader::ParseGlyph(const std::string &line) {
    auto *glyph = new Glyph();
    glyph->id = ParseProperty(line, "id");
    glyph->x = ParseProperty(line, "x");
    glyph->y = ParseProperty(line, "y");
    glyph->width = ParseProperty(line, "width");
    glyph->height = ParseProperty(line, "height");
    glyph->xOffset = ParseProperty(line, "xoffset");
    glyph->yOffset = ParseProperty(line, "yoffset");
    glyph->advance = ParseProperty(line, "xadvance");
    return glyph;
}

bool FontReader::IsGlyph(const std::string &line) {
    return line.find("char ") == 0;
}

Font *FontReader::ReadFont(std::ifstream &stream) {
    auto *font = new Font();
    std::string line;
    while (std::getline(stream, line)) {
        if (!IsGlyph(line)) continue;

        Glyph *glyph = ParseGlyph(line);
        font->glyphs[glyph->id] = glyph;
    }

    return font;
}
