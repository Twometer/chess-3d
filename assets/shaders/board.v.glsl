#version 330 core

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec3 vertexNormal;

uniform mat4 cameraMatrix;
uniform mat4 modelMatrix;
uniform vec3 cameraPos;
uniform vec2 position;

out vec3 normal;
out vec3 reflected;
out vec3 refracted;

void main() {
    vec4 worldPosition = (modelMatrix * vec4(vertexPosition, 1.0)) + vec4(position.x * 2, 0, position.y * 2, 0.0);

    gl_Position = cameraMatrix * worldPosition;
    normal = normalize((modelMatrix * vec4(vertexNormal, 1.0)).xyz);

    vec3 viewVector = normalize(worldPosition.xyz - cameraPos);
    reflected = reflect(viewVector, normal);
    refracted = refract(viewVector, normal, 1.0 / 1.33);
}