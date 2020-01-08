//
// Created by Twometer on 08/01/2020.
//

#include <GLFW/glfw3.h>
#include "GameState.h"

void GameState::StartGame() {
    runState = RUNNING;
    gameStart = glfwGetTime();
}

void GameState::StopGame() {
    runState = ENDED;
    gameStop = glfwGetTime();
}

void GameState::SwitchTeam() {
    currentTeam = (currentTeam == White ? Black : White);
}
