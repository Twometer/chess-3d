//
// Created by Twometer on 13/12/2019.
//

#ifndef CHESS_3D_MOVERESULT_H
#define CHESS_3D_MOVERESULT_H

#include <glm/vec2.hpp>

enum MoveResultType {
    INVALID,
    OK,
    HIT
};

struct MoveResult {

    MoveResultType resultType;

    glm::vec2 hitPosition;

    explicit MoveResult(MoveResultType type) {
        this->resultType = type;
    }

    MoveResult(glm::vec2 hitPosition) {
        this->resultType = HIT;
        this->hitPosition = hitPosition;
    }

};

#endif //CHESS_3D_MOVERESULT_H
