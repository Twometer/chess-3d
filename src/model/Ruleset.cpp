//
// Created by Twometer on 13/12/2019.
//
#include <exception>
#include <iostream>
#include "../util/Loader.h"
#include "Ruleset.h"

using namespace nlohmann;

Ruleset *Ruleset::Load(const std::string &path) {
    auto *ruleset = new Ruleset();

    std::string content = Loader::LoadFromFile(path);
    json file = json::parse(content);
    for (json &item : file) {
        Rule *rule = Rule::Load(item);
        PieceType type = TypeFromString(item["name"]);
        ruleset->rules[type] = rule;
    }

    return ruleset;
}

PieceType Ruleset::TypeFromString(const std::string &string) {
    if (string == "pawn") return Pawn;
    else if (string == "rook") return Rook;
    else if (string == "bishop") return Bishop;
    else if (string == "knight") return Knight;
    else if (string == "queen") return Queen;
    else if (string == "king") return King;
    throw std::runtime_error("Invalid piece type " + string);
}

Rule *Ruleset::GetRule(PieceType type) {
    return rules[type];
}
