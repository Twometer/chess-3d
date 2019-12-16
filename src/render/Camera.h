//
// Created by Twometer on 16/12/2019.
//

#ifndef CHESS_3D_CAMERA_H
#define CHESS_3D_CAMERA_H

#include <glm/glm.hpp>

class Camera {
private:
    glm::vec3 position;

    glm::vec2 rotation;

public:
    glm::mat4 CalculateMatrix(glm::vec2 viewportSize);

};


#endif //CHESS_3D_CAMERA_H
