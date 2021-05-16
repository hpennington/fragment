#version 330 core
layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec3 aNormal;

uniform mat4 model;
out vec3 color;
out vec3 normal;

void main() {
    gl_Position = model * vec4(aPosition, 1.0f);

    color = aColor;
    normal = aNormal;
}