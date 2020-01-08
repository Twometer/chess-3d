//
// Created by Twometer on 07/01/2020.
//

#ifndef CHESS_3D_GAMESTATE_H
#define CHESS_3D_GAMESTATE_H

#include "Team.h"

enum RunState {
    NOT_STARTED,
    RUNNING,
    ENDED
};

class GameState {
public:
    RunState runState = NOT_STARTED;

    double gameStart = -1;
    double gameStop = -1;

    Team currentTeam = Team::White;

    void StartGame();

    void StopGame();

    void SwitchTeam();

};

#endif //CHESS_3D_GAMESTATE_H
