//
// Created by Twometer on 13/12/2019.
//

#ifndef CHESS_3D_BOARD_H
#define CHESS_3D_BOARD_H


#include <glm/glm.hpp>
#include "MoveResult.h"
#include "Piece.h"
#include "Ruleset.h"

class Board {
private:
    static constexpr int BOARD_SIZE = 8;

    Piece **pieces = new Piece *[BOARD_SIZE * BOARD_SIZE];

    Ruleset *ruleset;

private:
    static bool CheckPosition(glm::vec2 position);

    Piece *CreatePiece(PieceType type, Team team);

    static inline int GetIndex(int x, int y);

public:
    explicit Board(Ruleset *ruleset);

    ~Board();

    void Initialize();

    MoveResult Move(glm::vec2 from, glm::vec2 to);

    Piece *GetPiece(glm::vec2 vec);

    void SetPiece(glm::vec2 vec, Piece *piece);
};


#endif //CHESS_3D_BOARD_H
