//
// Created by Twometer on 13/12/2019.
//

#include "Board.h"

Board::Board(Ruleset *ruleset) {
    this->ruleset = ruleset;
}

Board::~Board() {
    delete[] pieces;
}

int Board::GetIndex(int x, int y) {
    return (y * BOARD_SIZE) + x;
}

bool Board::CheckPosition(glm::vec2 position) {
    return position.x >= 0 && position.y >= 0 && position.x < BOARD_SIZE && position.y < BOARD_SIZE;
}

void Board::Initialize() {

}

MoveResult Board::Move(glm::vec2 from, glm::vec2 to) {
    if (!CheckPosition(from) || !CheckPosition(to))
        return MoveResult(false);

    Piece *piece = GetPiece(from);
    MoveResult result = piece->rule->TryMove(piece, from, to);
    if (result.allowed)
        SetPiece(to, piece);

    return result;
}

Piece *Board::CreatePiece(PieceType type, Team team) {
    Rule *rule = ruleset->GetRule(type);
    return new Piece(rule, type, team);
}

Piece *Board::GetPiece(glm::vec2 vec) {
    return pieces[GetIndex(vec.x, vec.y)];
}

void Board::SetPiece(glm::vec2 vec, Piece *piece) {
    pieces[GetIndex(vec.x, vec.y)] = piece;
}
