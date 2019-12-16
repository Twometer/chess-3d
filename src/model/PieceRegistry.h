//
// Created by Twometer on 16/12/2019.
//

#ifndef CHESS_3D_PIECEREGISTRY_H
#define CHESS_3D_PIECEREGISTRY_H

#include <map>
#include "../gl/Model.h"
#include "PieceType.h"

class PieceRegistry {
private:
    static std::map<std::string, PieceType> typeMap;

    static std::map<PieceType, Model *> models;

public:
    static PieceType GetType(const std::string &str);

    static Model *GetModel(PieceType type);

    static void Initialize();

};


#endif //CHESS_3D_PIECEREGISTRY_H
