#version 330 core
out vec4 aColor;

in vec3 outColor;
in vec2 TexCoord;

uniform sampler2D wall;
uniform sampler2D face;

void main() {
    aColor = mix(texture(wall, TexCoord), texture(face, TexCoord), 0.2);
}