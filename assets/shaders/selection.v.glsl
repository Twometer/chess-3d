#version 330 core

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec3 vertexNormal;

uniform mat4 cameraMatrix;
uniform mat4 modelMatrix;
uniform vec2 position;

out vec2 pos;

void main() {
    vec4 worldPosition = (modelMatrix * vec4(vertexPosition, 1.0)) + vec4(position.x * 2, 0, position.y * 2, 0.0);
    gl_Position = cameraMatrix * worldPosition;
    pos = position;
}