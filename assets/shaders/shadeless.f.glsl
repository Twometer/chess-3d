#version 330 core

in vec2 pos;

out vec4 color;

uniform vec4 modelColor;

void main() {
    color = modelColor;
}