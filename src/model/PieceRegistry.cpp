//
// Created by Twometer on 16/12/2019.
//

#include "PieceRegistry.h"
#include "../util/Loader.h"

std::map<std::string, PieceType> PieceRegistry::typeMap;
std::map<PieceType, Model *> PieceRegistry::models;

PieceType PieceRegistry::GetType(const std::string &str) {
    return typeMap[str];
}

Model *PieceRegistry::GetModel(PieceType type) {
    return models[type];
}

void PieceRegistry::Initialize() {
    typeMap["pawn"] = PieceType::Pawn;
    typeMap["rook"] = PieceType::Rook;
    typeMap["knight"] = PieceType::Knight;
    typeMap["bishop"] = PieceType::Bishop;
    typeMap["king"] = PieceType::King;
    typeMap["queen"] = PieceType::Queen;

    for (auto &entry : typeMap)
        models[entry.second] = Loader::LoadModel(entry.first + ".stl");
}
