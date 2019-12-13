#include <iostream>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include "model/Board.h"
#include "model/Piece.h"

int main() {
    auto *board = new Board();
    auto *piece = new Piece();

    piece->ValidateMove(board, Team::Black, glm::vec2(0,1), glm::vec2(2, 2));
    piece->ValidateMove(board, Team::White, glm::vec2(0, 6), glm::vec2(0, 5));

    if (!glfwInit())
        return 1;

    return 0;
}