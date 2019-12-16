//
// Created by Twometer on 15/12/2019.
//

#ifndef CHESS_3D_BUFFER_H
#define CHESS_3D_BUFFER_H


#include <cstdint>

class Buffer {

private:
    uint8_t* data;

    int offset;

    void Read(void *data, int len);

public:
    explicit Buffer(uint8_t *data);

    uint16_t ReadUInt16();

    uint32_t ReadUInt32();

    float ReadFloat();

    void Skip(int n);



};


#endif //CHESS_3D_BUFFER_H
