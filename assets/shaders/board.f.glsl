#version 330 core

in vec3 normal;

out vec4 color;

const vec3 lightDirection = normalize(vec3(0.2, -1.0, 0.3));
const float ambient = 0.3;

void main() {
    float brightness = max(dot(-lightDirection, normalize(normal)), 0.0) + ambient;
    color = vec4(vec3(1.0f, 1.0f, 1.0f) * brightness, 1.0f);
}