//
// Created by Twometer on 13/12/2019.
//

#include "Rule.h"
#include "../render/ChessRenderer.h"
#include <iostream>

void Rule::ReadVecList(nlohmann::json &json, std::vector<glm::vec2> &vec) {
    for (std::string item : json) {
        std::string x = item.substr(0, item.find(','));
        std::string y = item.substr(x.length() + 1);
        vec.emplace_back(glm::vec2(std::stoi(x), std::stoi(y)));
    }
}

MoveResult Rule::TryMove(Piece *piece, glm::vec2 to) {
    // Move direction in file is relative to the team's base
    // Therefore, we have to align our vector with that
    Board *board = ChessRenderer::GetBoard();

    glm::vec2 diff = to - piece->position;
    if (piece->team == White)
        diff.y *= -1;

    int range = CalculateRange(piece);
    glm::vec2 *baseVec = FindBaseVector(diff, range);

    // This move does not match any base vectors defined
    // in the ruleset and is therefore invalid.
    if (baseVec == nullptr)
        return MoveResult(false);

    // If the piece can't jump, raytrace so that it
    // can't walk through other pieces.
    if (!mayJump) {

    }

    return MoveResult(true);
}

Rule *Rule::Load(nlohmann::json &json) {
    Rule *rule = new Rule();

    rule->infinite = json["infinite"];
    rule->mayJump = json.contains("mayJump") ? (bool) json["mayJump"] : false;

    if (json.contains("move"))
        ReadVecList(json["move"], rule->moves);
    else
        for (int i = -1; i <= 1; i++)
            for (int j = -1; j <= 1; j++)
                rule->moves.emplace_back(i, j);

    if (json.contains("hit"))
        ReadVecList(json["hit"], rule->hit);

    return rule;
}

glm::vec2 *Rule::FindBaseVector(glm::vec2 move, int range) {
    for (glm::vec2 &vec : moves) {
        for (int i = 1; i <= range; i++)
            if (vec * (float) i == move)
                return &vec;
    }
    return nullptr;
}

int Rule::CalculateRange(Piece *piece) {
    glm::vec2 position = piece->position;
    if (infinite) return 8;
    else if (piece->type == Pawn && (position.y == 1 || position.y == 6))
        return 2;
    else return 1;
}
