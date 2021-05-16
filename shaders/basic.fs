#version 330 core
in vec3 color;
in vec3 normal;
in vec3 fragPos;

out vec4 FragColor;

uniform vec3 lightPos;

void main() {
    // Ambient
    float ambientStrength = 0.25;
    vec3 ambient = vec3(1.0f, 1.0f, 1.0f) * ambientStrength;
    
    // Diffuse 
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(lightPos - fragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * vec3(1.0f, 1.0f, 1.0f);

    vec3 result = (ambient + diffuse) * color;
    FragColor = vec4(result, 1.0f);
}
