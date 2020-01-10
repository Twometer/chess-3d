//
// Created by Twometer on 07/01/2020.
//

#ifndef CHESS_3D_GAMESTATE_H
#define CHESS_3D_GAMESTATE_H

#include <vector>

#include "Piece.h"
#include "Team.h"

enum class RunState {
    NotStarted,
    Running,
    Ended
};

class GameState {
public:
    RunState runState = RunState::NotStarted;

    double gameStart = -1;
    double gameStop = -1;

    Team currentTeam = Team::White;

    std::vector<Piece *> capturedPieces;

    void StartGame();

    void StopGame();

    void SwitchTeam();

};

#endif //CHESS_3D_GAMESTATE_H
