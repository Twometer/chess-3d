//
// Created by Twometer on 13/12/2019.
//

#include "Board.h"

Board::Board(Ruleset *ruleset) {
    this->ruleset = ruleset;
    memset(pieces, 0, BOARD_SIZE * BOARD_SIZE * sizeof(Piece *));
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
    CreateBaseline(0, Team::Black);
    CreatePawns(1, Team::Black);
    CreatePawns(6, Team::White);
    CreateBaseline(7, Team::White);
}

MoveResult Board::Move(glm::vec2 from, glm::vec2 to) {
    if (!CheckPosition(from) || !CheckPosition(to))
        return MoveResult(INVALID);

    Piece *piece = GetPiece(from);
    MoveResult result = piece->rule->TryMove(piece, to);
    if (result.resultType == OK) {
        SetPiece(to, piece);
        SetPiece(from, nullptr);
    }

    return result;
}

Piece *Board::CreatePiece(PieceType type, Team team) {
    Rule *rule = ruleset->GetRule(type);
    return new Piece(rule, type, team);
}

Piece *Board::GetPiece(glm::vec2 vec) {
    int idx = GetIndex(vec.x, vec.y);
    if (idx < 0 || idx >= BOARD_SIZE * BOARD_SIZE)
        return nullptr;

    return pieces[idx];
}

void Board::SetPiece(glm::vec2 vec, Piece *piece) {
    pieces[GetIndex(vec.x, vec.y)] = piece;
    if (piece != nullptr)
        piece->position = vec;
}

void Board::SetPiece(glm::vec2 vec, PieceType type, Team team) {
    SetPiece(vec, CreatePiece(type, team));
}

void Board::CreatePawns(int row, Team team) {
    for (int i = 0; i < BOARD_SIZE; i++)
        SetPiece(glm::vec2(i, row), PieceType::Pawn, team);
}

void Board::CreateBaseline(int row, Team team) {
    SetPiece(glm::vec2(0, row), PieceType::Rook, team);
    SetPiece(glm::vec2(1, row), PieceType::Knight, team);
    SetPiece(glm::vec2(2, row), PieceType::Bishop, team);
    SetPiece(glm::vec2(3, row), PieceType::King, team);
    SetPiece(glm::vec2(4, row), PieceType::Queen, team);
    SetPiece(glm::vec2(5, row), PieceType::Bishop, team);
    SetPiece(glm::vec2(6, row), PieceType::Knight, team);
    SetPiece(glm::vec2(7, row), PieceType::Rook, team);
}