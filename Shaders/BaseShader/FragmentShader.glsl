#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform vec4 colorVector;
uniform sampler2D textureSampler;

void main(){
    FragColor = mix(
        texture(textureSampler,TexCoord)*vec4(colorVector.rgb,1.0f),
        vec4(0.0f,0.0f,0.0f,1.0f),
        1.0f-colorVector.a
    );
}