//
// Created by Twometer on 13/12/2019.
//

#ifndef CHESS_3D_RULESET_H
#define CHESS_3D_RULESET_H

#include <map>
#include <string>
#include "Rule.h"
#include "PieceType.h"

class Ruleset {
private:
    std::map<PieceType, Rule *> rules;

public:
    static Ruleset *Load(const std::string &path);

    Rule *GetRule(PieceType type);

};


#endif //CHESS_3D_RULESET_H
