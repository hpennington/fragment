#include <string>
#include <vector>
#include "vertex.hpp"

#ifndef SHADER_H
#define SHADER_H

class Shader {
public:
    Shader(std::string vertex_shader, std::string fragment_shader);
    void bind_buffers(std::vector<Vertex> vertices);
    unsigned int getProgram();
    unsigned int getVAO();
private:
    unsigned int program;
    unsigned int VAO;
};

#endif