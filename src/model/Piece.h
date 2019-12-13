//
// Created by Twometer on 13/12/2019.
//

#ifndef CHESS_3D_PIECE_H
#define CHESS_3D_PIECE_H

#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <nlohmann/json.hpp>
#include "Board.h"
#include "Team.h"
#include "MoveResult.h"

class Piece {

private:
    std::string name;
    std::string model;
    std::vector<glm::vec2> moves;
    std::vector<glm::vec2> hit;
    bool infinite;
    bool mayJump;

public:

    static Piece *Load(nlohmann::json &json, std::string &name);

    MoveResult ValidateMove(Board *board, Team team, glm::vec2 from, glm::vec2 to);

};


#endif //CHESS_3D_PIECE_H
