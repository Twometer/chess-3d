#version 330 core

in vec3 normal;

void main() {
    color = vec4(normal, 1.0f);
}