#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 3) in vec3 aCol;
layout (location = 6) in vec3 aNorm;
out vec3 color;
out vec3 normal;
out vec3 FragPos;
uniform mat4 transform;
uniform mat4 view;
uniform mat4 projection;

void main()
{
   gl_Position = projection * view * transform * vec4(aPos.x, aPos.y, aPos.z, 1.0);
   color = aCol;
   normal = aNorm;
   FragPos = aPos;
}