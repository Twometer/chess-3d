#version 330 core

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec3 vertexNormal;

uniform mat4 mvpMatrix;
uniform vec3 cameraPos;
uniform vec2 position;

out vec3 normal;
out vec3 reflected;
out vec3 refracted;

void main() {
    vec4 worldPosition = vec4(vertexPosition + vec3(position.x * 2, 0, position.y * 2), 1.0);
    gl_Position = mvpMatrix * worldPosition;
    normal = vertexNormal;

    vec3 viewVector = normalize(worldPosition.xyz) - cameraPos;
    reflected = reflect(viewVector, normalize(normal));
    refracted = refract(viewVector, normalize(normal), 1.0 / 1.33);
}