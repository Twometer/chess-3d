#version 330 core

in vec3 normal;
in vec3 reflected;
in vec3 refracted;

uniform samplerCube skybox;
uniform float environFac;
uniform float diffuseFac;

out vec4 color;

const vec3 lightDirection = normalize(vec3(0.2, -1.0, 0.3));
const float ambient = 0.3;

void main() {
    float brightness = max(dot(-lightDirection, normal), 0.0) + ambient;
    color = vec4(vec3(1.0f, 1.0f, 1.0f) * brightness, 1.0f);

    vec4 reflectedColour = texture(skybox, reflected);
    vec4 refractedColour = texture(skybox, refracted);
    vec4 envColor = mix(reflectedColour, refractedColour, environFac);

    color = mix(color, envColor, diffuseFac);
}