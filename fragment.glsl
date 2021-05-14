#version 330 core
in vec3 color;
in vec3 normal;
in vec3 FragPos;
out vec4 FragColor;
uniform vec3 lightPos;
uniform vec3 viewPos;
void main()
{
   float ambientStrength = 0.5;
   vec3 ambient = ambientStrength * color;
   vec3 norm = normalize(normal);
   vec3 lightDir = normalize(lightPos - FragPos);
   float diff = max(dot(norm, lightDir), 0.0);
   vec3 diffuse = diff * color;
   float specularStrength = 0.5;
   vec3 viewDir = normalize(viewPos - FragPos);
   vec3 reflectDir = reflect(-lightDir, norm);
   float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
   vec3 specular = specularStrength * spec * vec3(1.0, 1.0, 1.0);
   vec3 result = (ambient + diffuse + specular) * color;
   FragColor = vec4(result, 1.0);
}