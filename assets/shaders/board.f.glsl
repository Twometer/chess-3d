#version 330 core

in vec3 v_pos;

out vec4 color;

void main() {
    float x = floor((v_pos.x + 1.0) / 2f);
    float y = floor((v_pos.z + 1.0) / 2f);

    if (x < 0 || y < 0 || x > 7 || y > 7){
        discard;
    }

    if (mod(x + mod(y, 2), 2) == 0) {
        color = vec4(1.0f, 1.0f, 1.0f, 1.0f);
    } else {
        color = vec4(0.0f, 0.0f, 0.0f, 1.0f);
    }


}