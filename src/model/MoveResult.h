//
// Created by Twometer on 13/12/2019.
//

#ifndef CHESS_3D_MOVERESULT_H
#define CHESS_3D_MOVERESULT_H

#include <glm/vec2.hpp>

struct MoveResult {

    bool allowed;

    bool hit;

    glm::vec2 hitPosition;

};

#endif //CHESS_3D_MOVERESULT_H
