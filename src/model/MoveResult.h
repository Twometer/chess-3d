//
// Created by Twometer on 13/12/2019.
//

#ifndef CHESS_3D_MOVERESULT_H
#define CHESS_3D_MOVERESULT_H

#include <glm/vec2.hpp>
#include "PieceType.h"
#include "Team.h"

enum MoveResultType {
    INVALID,
    OK,
    HIT
};

struct MoveResult {

    MoveResultType resultType;

    PieceType pieceHit;
    Team teamHit;

    explicit MoveResult(MoveResultType type) {
        this->resultType = type;
    }

    MoveResult(PieceType pieceType, Team team) {
        this->resultType = HIT;
        this->pieceHit = pieceType;
        this->teamHit = team;
    }

};

#endif //CHESS_3D_MOVERESULT_H
