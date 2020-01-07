//
// Created by Twometer on 13/12/2019.
//

#include "Rule.h"
#include <iostream>

void Rule::ReadVecList(nlohmann::json &json, std::vector<glm::vec2> &vec) {
    for (std::string item : json) {
        std::string x = item.substr(0, item.find(','));
        std::string y = item.substr(x.length() + 1);
        vec.emplace_back(glm::vec2(std::stoi(x), std::stoi(y)));
    }
}

MoveResult Rule::TryMove(Piece *piece, glm::vec2 to) {
    // Move direction relative to the team's base
    glm::vec2 diff = to - piece->position;
    if (piece->team == White)
        diff.y *= -1;

    if (infinite)
        diff = glm::normalize(diff);

    for (glm::vec2 &vec : moves)
        if (vec == diff)
            return MoveResult(true);

    // TODO: Check collision with other pieces

    return MoveResult(false);
}

Rule *Rule::Load(nlohmann::json &json) {
    Rule *rule = new Rule();

    rule->infinite = json["infinite"];
    rule->mayJump = json.contains("mayJump") ? (bool) json["mayJump"] : false;

    if (json.contains("move"))
        ReadVecList(json["move"], rule->moves);

    if (json.contains("hit"))
        ReadVecList(json["hit"], rule->hit);

    return rule;
}
