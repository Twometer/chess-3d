//
// Created by Twometer on 07/01/2020.
//

#ifndef CHESS_3D_GAMESTATE_H
#define CHESS_3D_GAMESTATE_H

#include "Team.h"

struct GameState {

    Team currentTeam = Team::White;

    void SwitchTeam() {
        currentTeam = (currentTeam == White ? Black : White);
    }

};

#endif //CHESS_3D_GAMESTATE_H
