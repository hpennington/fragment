#version 330 core
layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec3 aNormal;

out vec3 color;
out vec3 normal;
out vec3 fragPos;

uniform mat4 model;

void main() {
    fragPos = vec3(model * vec4(aPosition, 1.0f));
    color = aColor;
    normal = mat3(transpose(inverse(model))) * aNormal;  

    gl_Position = vec4(fragPos, 1.0f);
}
