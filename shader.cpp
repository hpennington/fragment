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
    this->vertex_shader = vertex_shader;
    this->fragment_shader = fragment_shader;
}

bool Shader::compile_shaders() {
    // Read shaders into variables v_content and f_content
    std::ifstream v_ifs(this->vertex_shader);
    std::string v_content((std::istreambuf_iterator<char>(v_ifs)), (std::istreambuf_iterator<char>()));
    std::ifstream f_ifs(this->fragment_shader);
    std::string f_content((std::istreambuf_iterator<char>(f_ifs)), (std::istreambuf_iterator<char>()));

    bool compileSuccess = true;
    
    // Compile shaders
    unsigned int vertex = glCreateShader(GL_VERTEX_SHADER);
    const char* v_source = v_content.c_str();
    glShaderSource(vertex, 1, &v_source, NULL);
    glCompileShader(vertex);
    compileSuccess = check_compile_error(vertex);

    unsigned int fragment = glCreateShader(GL_FRAGMENT_SHADER);
    const char* f_source = f_content.c_str();
    glShaderSource(fragment, 1, &f_source, NULL);
    glCompileShader(fragment);
    compileSuccess = check_compile_error(fragment);

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
        return false;
    }

    this->program = shaderProgram;

    // Clean up
    glDeleteShader(vertex);
    glDeleteShader(fragment);
    return (bool)success && compileSuccess;

}

void Shader::bind_buffers(std::vector<Vertex> vertices) {
    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);
    this->VAO = VAO;

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0); 

    // remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);

}

unsigned int Shader::getProgram() {
    return this->program;
}

unsigned int Shader::getVAO() {
    return this->VAO;
}
