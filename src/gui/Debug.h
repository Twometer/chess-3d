//
// Created by Twometer on 07/01/2020.
//

#ifndef CHESS_3D_DEBUG_H
#define CHESS_3D_DEBUG_H

#include <GLFW/glfw3.h>

class Debug {
private:

    float fps;
    float frames;
    float lastFrame;
    double lastCheck;
    double ftime;
    double avg_ftime;

public:

    void Render(FontRenderer *fontRenderer) {
        fontRenderer->Render("3D Chess", 0, 0, 0.4f);
        fontRenderer->Render(std::to_string((int) fps) + " fps", 0, 25, 0.4f);

        double now = glfwGetTime();
        ftime += (now - lastFrame) * 1000;
        fontRenderer->Render(std::to_string(avg_ftime) + " ms", 0, 50, 0.4f);

        frames++;

        if (now - lastCheck >= 1) {
            lastCheck = glfwGetTime();
            fps = frames;
            avg_ftime = ftime / frames;
            frames = 0;
            ftime = 0;
        }
        lastFrame = glfwGetTime();
    }

};

#endif //CHESS_3D_DEBUG_H
