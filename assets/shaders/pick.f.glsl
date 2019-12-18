#version 330 core

in vec2 pos;

out vec4 color;

void main() {
    color = vec4(pos.x / 255.f, pos.y / 255.f, 255.f, 1.0f);
}