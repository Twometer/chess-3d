//
// Created by Twometer on 16/12/2019.
//

#ifndef CHESS_3D_CAMERA_H
#define CHESS_3D_CAMERA_H

#include <glm/glm.hpp>

class Camera {
private:
    glm::mat4 matrix;

    glm::mat4 projectionMatrix;
    glm::mat4 viewMatrix;

    glm::vec3 eyePosition;

public:
    float zoom = 15.0f;

    glm::vec3 position;

    glm::vec2 rotation = glm::vec2(0, -150);

    glm::vec3 GetEyePosition();

    glm::mat4 CalculateMatrix(glm::vec2 viewportSize);

    glm::mat4 GetMatrix() { return matrix; }

    glm::mat4 GetProjectionMatrix() { return projectionMatrix; }

    glm::mat4 GetViewMatrix() { return viewMatrix; }
};


#endif //CHESS_3D_CAMERA_H
