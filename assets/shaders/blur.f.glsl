#version 150

in vec2 blurTextureCoords[11];
uniform sampler2D originalTexture;
out vec4 out_colour;

void main(void){
    out_colour = vec4(0.0);
    for (int i = 0; i < 11; i++)
    out_colour +=texture(originalTexture, blurTextureCoords[i]);
    out_colour /= 11;
}