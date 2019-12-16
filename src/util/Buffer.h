//
// Created by Twometer on 15/12/2019.
//

#ifndef CHESS_3D_BUFFER_H
#define CHESS_3D_BUFFER_H

#include <cstdint>

class Buffer {

private:
    uint8_t *data;

    int offset;

public:
    explicit Buffer(uint8_t *data) {
        this->data = data;
        this->offset = 0;
    }

    template<class T>
    T Read() {
        T *t = (T *) (data + offset);
        offset += sizeof(T);
        return *t;
    }

    void Skip(int n) {
        offset += n;
    }

};


#endif //CHESS_3D_BUFFER_H
