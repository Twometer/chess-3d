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

    // Can't move where there's already someone
    Piece *other = board->GetPiece(to);
    if (other != nullptr) {
        if (piece->team == other->team)
            return MoveResult(MoveResultType::Invalid);
        else if (!hit.empty()) {
            bool success;
            glm::vec2 dist = other->position - piece->position;
            glm::vec2 baseVec = FindBaseVector(piece, 1, dist, hit, success);
            if (success)
                return MoveResult(other->type, other->team);
            else
                return MoveResult(MoveResultType::Invalid);
        }
        // If no special hit vectors are defined
        // and we are trying to move to an enemy, check normal
        // move vectors
    }

    // The move does not match any base vectors defined
    // in the ruleset and is therefore invalid.
    bool foundVec = false;
    int range = CalculateRange(piece);;
    glm::vec2 baseVec = FindBaseVector(piece, range, diff, moves, foundVec);
    if (!foundVec)
        return MoveResult(MoveResultType::Invalid);

    // If the piece can't jump, ray trace so that it
    // can't walk through other pieces.
    if (!mayJump) {
        glm::vec2 src = piece->position;
        while (src != to && Board::CheckPosition(src)) {
            src += baseVec;
            Piece *other = board->GetPiece(src);
            if (other != nullptr)
                if (other->team == piece->team)
                    return MoveResult(MoveResultType::Invalid);
                else if (src == to)
                    return MoveResult(other->type, other->team);
                else return MoveResult(MoveResultType::Invalid);
        }
    }

    return MoveResult(MoveResultType::OK);
}

Rule *Rule::Load(nlohmann::json &json) {
    Rule *rule = new Rule();

    rule->infinite = json["infinite"];
    rule->mayJump = json.contains("mayJump") ? (bool) json["mayJump"] : false;

    if (json.contains("move"))
        ReadVecList(json["move"], rule->moves);
    else
        FillMoore(rule->moves);

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
 * @param range    The range of the piece
 * @param move     The move that is tried to be matched
 * @param vectors  This function can be applied to the movement as well as the hit check.
 *                 We therefore have to specify which vector of vectors (lol) to search.
 * @param success  Whether a move was matched
 * @return The base-vector, in absolute coordinates
 */
glm::vec2
Rule::FindBaseVector(Piece *piece, int range, glm::vec2 move, std::vector<glm::vec2> &vectors, bool &success) {
    glm::vec2 aligned = AlignDirection(piece->team, move); // Align to team-relative coordinates

    for (glm::vec2 &vec : vectors) {
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
    if (piece->rule->infinite) return 8;
    else if (piece->type == PieceType::Pawn && (position.y == 1 || position.y == 6))
        return 2;
    else return 1;
}

glm::vec2 Rule::AlignDirection(Team team, glm::vec2 vec) {
    // Move direction in the definition is relative to the team's base
    // Therefore, we have to align our vector with that
    if (team == Team::White)
        vec.y *= -1;
    return vec;
}

void Rule::FillMoore(std::vector<glm::vec2> &vec) {
    for (int i = -1; i <= 1; i++)
        for (int j = -1; j <= 1; j++)
            vec.emplace_back(i, j);
}
