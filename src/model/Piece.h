//
// Created by Twometer on 13/12/2019.
//

#ifndef CHESS_3D_PIECE_H
#define CHESS_3D_PIECE_H

#include "PieceType.h"
#include "Team.h"
#include "Rule.h"

class Rule;

struct Piece {

    Rule *rule;
    PieceType type;
    Team team;

    Piece(Rule *rule, PieceType type, Team team) {
        this->rule = rule;
        this->type = type;
        this->team = team;
    }

};


#endif //CHESS_3D_PIECE_H
