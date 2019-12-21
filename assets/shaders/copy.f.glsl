#version 140

in vec2 textureCoords;
out vec4 out_Colour;
uniform sampler2D tex;

void main(void){
    vec4 sceneColour = texture(tex, textureCoords);
    out_Colour = sceneColour;

}