//
// Created by Twometer on 07/01/2020.
//

#ifndef CHESS_3D_GAMESTATE_H
#define CHESS_3D_GAMESTATE_H

#include "Team.h"

class GameState {
public:
    bool isRunning = false;

    double gameStart = -1;
    double gameStop = -1;

    Team currentTeam = Team::White;

    void StartGame();

    void StopGame();

    void SwitchTeam();

};

#endif //CHESS_3D_GAMESTATE_H
