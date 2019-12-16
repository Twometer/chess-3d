//
// Created by Twometer on 13/12/2019.
//
#include <exception>
#include <iostream>
#include "../util/Loader.h"
#include "Ruleset.h"
#include "PieceRegistry.h"

using namespace nlohmann;

Ruleset *Ruleset::Load(const std::string &path) {
    auto *ruleset = new Ruleset();

    std::string content = Loader::ReadAllText(path);
    json file = json::parse(content);
    for (json &item : file) {
        Rule *rule = Rule::Load(item);
        PieceType type = PieceRegistry::GetType(item["name"]);
        ruleset->rules[type] = rule;
    }

    return ruleset;
}

Rule *Ruleset::GetRule(PieceType type) {
    return rules[type];
}
