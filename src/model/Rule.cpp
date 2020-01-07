//
// Created by Twometer on 13/12/2019.
//

#include "Rule.h"
#include "../render/ChessRenderer.h"
#include <iostream>

void Rule::ReadVecList(nlohmann::json &json, std::vector<glm::vec2> &vec) {
    for (std::string item : json) {
        std::string x = item.substr(0, item.find(','));
        std::string y = item.substr(x.length() + 1);
        vec.emplace_back(glm::vec2(std::stoi(x), std::stoi(y)));
    }
}

MoveResult Rule::TryMove(Piece *piece, glm::vec2 to) {
    Board *board = ChessRenderer::GetBoard();

    glm::vec2 diff = to - piece->position;

    bool foundVec = false;
    glm::vec2 baseVec = FindBaseVector(piece, diff, foundVec);

    // The move does not match any base vectors defined
    // in the ruleset and is therefore invalid.
    if (!foundVec)
        return MoveResult(INVALID);

    // Can't move where there's already someone
    Piece *other = board->GetPiece(to);
    if (other != nullptr) {
        if (CanKill(piece, other))
            return MoveResult(other->position);
        else return MoveResult(INVALID);
    }

    // If the piece can't jump, ray trace so that it
    // can't walk through other pieces.
    if (!mayJump) {
        glm::vec2 src = piece->position;
        while (src != to && board->CheckPosition(src)) {
            src += baseVec;
            if (board->GetPiece(src) != nullptr)
                return MoveResult(INVALID);
        }
    }

    return MoveResult(OK);
}

Rule *Rule::Load(nlohmann::json &json) {
    Rule *rule = new Rule();

    rule->infinite = json["infinite"];
    rule->mayJump = json.contains("mayJump") ? (bool) json["mayJump"] : false;

    if (json.contains("move"))
        ReadVecList(json["move"], rule->moves);
    else
        for (int i = -1; i <= 1; i++)
            for (int j = -1; j <= 1; j++)
                rule->moves.emplace_back(i, j);

    if (json.contains("hit"))
        ReadVecList(json["hit"], rule->hit);

    return rule;
}

/**
 * Given a piece and a move vector, this method tries to find
 * a matching base vector from the rule definitions.
 * A base vector is a team-aligned vector defined in a rule that
 * specifies where a piece can move. If this vector can't be found,
 * that means that the move is not allowed.
 *
 * @param piece    The piece in question
 * @param move     The move that is tried to be matched
 * @param success  Whether a move was matched
 * @return The base-vector, in absolute coordinates
 */
glm::vec2 Rule::FindBaseVector(Piece *piece, glm::vec2 move, bool &success) {
    int range = CalculateRange(piece);

    glm::vec2 aligned = AlignDirection(piece->team, move); // Align to team-relative coordinates

    for (glm::vec2 &vec : moves) {
        for (int i = 1; i <= range; i++)
            if (vec * (float) i == aligned) {
                success = true;
                return AlignDirection(piece->team, vec); // Unalign to absolute coordinates
            }
    }

    success = false;
    return {};
}

int Rule::CalculateRange(Piece *piece) {
    glm::vec2 position = piece->position;
    if (infinite) return 8;
    else if (piece->type == Pawn && (position.y == 1 || position.y == 6))
        return 2;
    else return 1;
}

glm::vec2 Rule::AlignDirection(Team team, glm::vec2 vec) {
    // Move direction in the definition is relative to the team's base
    // Therefore, we have to align our vector with that
    if (team == White)
        vec.y *= -1;
    return vec;
}

bool Rule::CanKill(Piece *a, Piece *b) {
    if (a->team == b->team)
        return false;
    return true;
}
