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
    static constexpr int SIZE = 8;

    Piece **pieces = new Piece *[SIZE * SIZE];

    Ruleset *ruleset;

    static inline int GetIndex(int x, int y);

    Piece *CreatePiece(PieceType type, Team team);

    void CreatePawns(int row, Team team);

    void CreateBaseline(int row, Team team);

public:
    explicit Board(Ruleset *ruleset);

    ~Board();

    void Initialize();

    MoveResult Move(glm::vec2 from, glm::vec2 to);

    Piece *GetPiece(glm::vec2 vec);

    Piece *FindPiece(PieceType type, Team team);

    void SetPiece(glm::vec2 vec, Piece *piece);

    void SetPiece(glm::vec2 vec, PieceType type, Team team);

    bool IsInCheck(Piece *king);

    static bool CheckPosition(glm::vec2 position);
};


#endif //CHESS_3D_BOARD_H
