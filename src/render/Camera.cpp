//
// Created by Twometer on 16/12/2019.
//

#include <glm/gtc/matrix_transform.hpp>
#include "Camera.h"

#define PI 3.141592653589793

glm::mat4 Camera::CalculateMatrix(glm::vec2 viewportSize) {
    float yaw = glm::radians(rotation.x);
    float pitch = glm::radians(rotation.y);

    glm::vec3 direction(
            cos(pitch) * sin(yaw),
            sin(pitch),
            cos(pitch) * cos(yaw)
    );

    glm::vec3 right = glm::vec3(
            sin(yaw - PI / 2.0f),
            0.0f,
            cos(yaw - PI / 2.0f)
    );

    glm::vec3 up = glm::cross(right, -direction);
    eyePosition = (-direction * zoom.GetValue()) + position;

    projectionMatrix = glm::perspective(glm::radians(70.0f), (float) viewportSize.x / (float) viewportSize.y,
                                        0.01f, 2000.0f);
    viewMatrix = glm::lookAt(eyePosition, position, up);

    return matrix = (projectionMatrix * viewMatrix);
}

glm::vec3 Camera::GetEyePosition() {
    return eyePosition;
}
