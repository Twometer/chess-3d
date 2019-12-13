//
// Created by Twometer on 13/12/2019.
//

#include "Piece.h"
#include <iostream>

MoveResult Piece::ValidateMove(Board *board, Team team, glm::vec2 from, glm::vec2 to) {
    MoveResult result;
    result.allowed = true;

    // Move direction relative to the team's base
    glm::vec2 diff = to - from;
    if (team == White)
        diff.y *= -1;

    if (infinite)
        diff = glm::normalize(diff);

    std::cout << diff.x << " " << diff.y << std::endl;

    return result;
}

Piece *Piece::Load(nlohmann::json &json, std::string &name) {

    return nullptr;
}
