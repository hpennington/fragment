#version 330 core
in vec3 color;
in vec3 normal;
in vec3 fragPos;

out vec4 FragColor;

uniform vec3 camera_position;

void main() {
    // Ambient
    float ambientStrength = 0.25;
    vec3 ambient = vec3(1.0f, 1.0f, 1.0f) * ambientStrength;
    
    // Diffuse 
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(vec3(1.0f, 20.0f, 20.0f) - fragPos);

    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * vec3(1.0f, 1.0f, 1.0f);

    // Specular
    float specularStrength = 0.5;
    vec3 viewDir = normalize(camera_position - fragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * vec3(1.0f, 1.0f, 1.0f);

    vec3 result = (ambient + diffuse + specular) * color;
    FragColor = vec4(result, 1.0f);
}
