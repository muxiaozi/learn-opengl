#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTex;
layout (location = 2) in vec3 aColor;

uniform mat4 transform;

out vec2 TexCoord;
out vec3 outColor;

void main() {
    gl_Position = transform * vec4(aPos, 1.0f);
    TexCoord = aTex;
    outColor = aColor;
}