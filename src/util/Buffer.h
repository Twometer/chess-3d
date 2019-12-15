//
// Created by Twometer on 15/12/2019.
//

#ifndef CHESS_3D_BUFFER_H
#define CHESS_3D_BUFFER_H


#include <cstdint>

class Buffer {

private:
    uint8_t* data;

    int idx;

public:
    Buffer(uint8_t *data);

    uint16_t ReadUINT16();

    uint32_t ReadUINT32();

    float ReadREAL32();

    void Skip(int n);



};


#endif //CHESS_3D_BUFFER_H
