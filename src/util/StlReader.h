//
// Created by Twometer on 16/12/2019.
//

#ifndef CHESS_3D_STLREADER_H
#define CHESS_3D_STLREADER_H

#include <glm/vec3.hpp>
#include "../gl/Model.h"
#include "Buffer.h"

class StlReader {

private:
    static glm::vec3 ReadVec3(Buffer &buf);

public:

    static Model *Load(uint8_t *buf);

};


#endif //CHESS_3D_STLREADER_H
