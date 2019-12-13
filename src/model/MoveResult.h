//
// Created by Twometer on 13/12/2019.
//

#ifndef CHESS_3D_MOVERESULT_H
#define CHESS_3D_MOVERESULT_H

#include <glm/vec2.hpp>

struct MoveResult {

    bool allowed;

    bool hit;

    glm::vec2 hitPosition{};

    explicit MoveResult(bool allowed) {
        this->allowed = allowed;
        this->hit = false;
    }

    MoveResult(bool allowed, glm::vec2 hitPosition) {
        this->allowed = allowed;
        this->hit = true;
        this->hitPosition = hitPosition;
    }

};

#endif //CHESS_3D_MOVERESULT_H
