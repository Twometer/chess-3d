//
// Created by Twometer on 08/01/2020.
//

#include <GLFW/glfw3.h>
#include "GameState.h"

void GameState::StartGame() {
    runState = RunState::Running;
    gameStart = glfwGetTime();
}

void GameState::StopGame() {
    runState = RunState::Ended;
    gameStop = glfwGetTime();
}

void GameState::SwitchTeam() {
    currentTeam = (currentTeam == Team::White ? Team::Black : Team::White);
}
