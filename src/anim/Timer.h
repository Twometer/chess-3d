//
// Created by Twometer on 10/01/2020.
//

#ifndef CHESS_3D_TIMER_H
#define CHESS_3D_TIMER_H

#include <GLFW/glfw3.h>

class Timer {
private:
    float lastTick = 0;

    float ms;

public:
    Timer(int tps) {
        ms = 1.f / tps;
    }

    bool HasReached() {
        return glfwGetTime() >= lastTick + ms;
    }

    void Reset() {
        lastTick = glfwGetTime();
    }

};

#endif //CHESS_3D_TIMER_H
