#include <iostream>
#include <GLFW/glfw3.h>
#include "model/Board.h"
#include "model/Rule.h"
#include "model/Ruleset.h"

int main() {
    Ruleset *ruleset = Ruleset::Load("assets/rules.json");
    auto *board = new Board(ruleset);
    board->Initialize();

    if (!glfwInit())
        return 1;

    return 0;
}