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

    static int CalculateRange(Piece *piece);

    static glm::vec2
    FindBaseVector(Piece *piece, int range, glm::vec2 move, std::vector<glm::vec2> &vectors, bool &success);

    static void ReadVecList(nlohmann::json &json, std::vector<glm::vec2> &vec);

    static glm::vec2 AlignDirection(Team team, glm::vec2 vec);

    static void FillMoore(std::vector<glm::vec2> &vec);

public:

    static Rule *Load(nlohmann::json &json);

    MoveResult TryMove(Piece *piece, glm::vec2 to);

};


#endif //CHESS_3D_RULE_H
