#include <iostream>
#include <fstream>
#include <string>
#ifdef __APPLE__
    #include <OpenGL/gl3.h>
#else
    #include <OpenGL/gl.h>
#endif

#include "shader.hpp"

bool check_compile_error(unsigned int shader) {
    int success;
    char info_log[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, info_log);
        std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << info_log << std::endl;
        return false;
    }

    return true;
}

Shader::Shader(std::string vertex_shader, std::string fragment_shader) {
    // Read shaders into variables v_content and f_content
    std::ifstream v_ifs(vertex_shader);
    std::string v_content((std::istreambuf_iterator<char>(v_ifs)), (std::istreambuf_iterator<char>()));
    std::ifstream f_ifs(fragment_shader);
    std::string f_content((std::istreambuf_iterator<char>(f_ifs)), (std::istreambuf_iterator<char>()));
    
    // Compile shaders
    unsigned int vertex = glCreateShader(GL_VERTEX_SHADER);
    const char* v_source = v_content.c_str();
    glShaderSource(vertex, 1, &v_source, NULL);
    glCompileShader(vertex);
    check_compile_error(vertex);

    unsigned int fragment = glCreateShader(GL_FRAGMENT_SHADER);
    const char* f_source = f_content.c_str();
    glShaderSource(fragment, 1, &f_source, NULL);
    glCompileShader(fragment);
    check_compile_error(fragment);

    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertex);
    glAttachShader(shaderProgram, fragment);
    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);
    
    int success;
    char info_log[512];
    
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, info_log);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << info_log << std::endl;
    }

    // Clean up
    glDeleteShader(vertex);
    glDeleteShader(fragment); 
}

void Shader::bind_buffers(std::vector<Vertex> vertices, unsigned int indices[]) {
    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0); 

}
