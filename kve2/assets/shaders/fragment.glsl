#version 330 core
in vec2 fUv;
in vec4 fColor;

out vec4 fColorOutput;

uniform sampler2D fTexture;

void main() {
    fColorOutput = texture(fTexture, fUv) * fColor;
}