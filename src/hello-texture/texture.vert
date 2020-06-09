#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTex;
layout (location = 2) in vec3 aColor;
out vec2 TexCoord;
out vec3 outColor;
void main() {
    gl_Position = vec4(aPos, 1.0);
    TexCoord = aTex;
    outColor = aColor;
}