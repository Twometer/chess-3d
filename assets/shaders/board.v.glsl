#version 330 core

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec3 vertexNormal;

uniform mat4 cameraMatrix;

out vec3 v_pos;

void main() {
    vec4 worldPosition = vec4(vertexPosition, 1.0);
    v_pos = vertexPosition;
    gl_Position = cameraMatrix * worldPosition;
}