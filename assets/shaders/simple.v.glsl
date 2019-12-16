#version 330 core

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec3 vertexNormal;

uniform mat4 mvpMatrix;

out vec3 normal;

void main() {
    gl_Position = mvpMatrix * vec4(vertexPosition, 1.0);
    normal = vertexNormal;
}