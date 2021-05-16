#version 330 core
layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aColor;

uniform mat4 model;
out vec3 color;

void main() {
    gl_Position = model * vec4(aPosition, 1.0f);

    color = aColor;
}