//
// Created by Twometer on 15/12/2019.
//

#include <cstring>
#include "Buffer.h"

Buffer::Buffer(uint8_t *data) {
    this->data = data;
    this->offset = 0;
}

uint16_t Buffer::ReadUInt16() {
    uint16_t fl = 0;
    Read(&fl, sizeof(uint16_t));
    return fl;
}

uint32_t Buffer::ReadUInt32() {
    uint16_t fl = 0;
    Read(&fl, sizeof(uint16_t));
    return fl;
}

float Buffer::ReadFloat() {
    float fl = 0;
    Read(&fl, sizeof(float));
    return fl;
}

void Buffer::Read(void *data, int len) {
    memcpy(data, this->data + this->offset, len);
}

void Buffer::Skip(int n) {

}
