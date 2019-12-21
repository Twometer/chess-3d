#version 330 core

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec3 vertexNormal;

uniform mat4 mvpMatrix;
uniform vec2 position;

out vec2 pos;

void main() {
    gl_Position = mvpMatrix * vec4(vertexPosition + vec3(position.x * 2, 0, position.y * 2), 1.0);
    pos = position;
}