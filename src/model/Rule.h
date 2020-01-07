//
// Created by Twometer on 13/12/2019.
//

#ifndef CHESS_3D_RULE_H
#define CHESS_3D_RULE_H

#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <nlohmann/json.hpp>
#include "Piece.h"
#include "MoveResult.h"

struct Piece;

class Rule {

private:
    std::string name;
    std::vector<glm::vec2> moves;
    std::vector<glm::vec2> hit;
    bool infinite = false;
    bool mayJump = false;

    Rule() = default;

    int CalculateRange(Piece *piece);

    glm::vec2 FindBaseVector(Piece *piece, glm::vec2 move, bool &success);

    static void ReadVecList(nlohmann::json &json, std::vector<glm::vec2> &vec);

    static glm::vec2 AlignDirection(Team team, glm::vec2 vec);

    bool CanKill(Piece *a, Piece *b);

public:

    static Rule *Load(nlohmann::json &json);

    MoveResult TryMove(Piece *piece, glm::vec2 to);

};


#endif //CHESS_3D_RULE_H
