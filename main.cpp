#include <iostream>
#include <vector>
#include <random>
#include <GLFW/glfw3.h>
#include "glad/glad.h"
#include <OpenGL/gl.h>
#include "linmath.h"

struct Vertex {
    float x, y, z, r, g, b;
};

struct RectSize {
    float x, y, z;
};

struct Origin {
    float x, y, z;
};

struct Color {
    float r, g, b;
};

static const char* vertex_shader_text =
"#version 110\n"
"uniform mat4 MVP;\n"
"attribute vec3 vCol;\n"
"attribute vec3 vPos;\n"
"varying vec3 color;\n"
"void main()\n"
"{\n"
"    gl_Position = MVP * vec4(vPos, 1.0);\n"
"    color = vCol;\n"
"}\n";
 
static const char* fragment_shader_text =
"#version 110\n"
"varying vec3 color;\n"
"void main()\n"
"{\n"
"    gl_FragColor = vec4(color, 1.0);\n"
"}\n";
 
void error_callback(int error, const char* description) {
    fprintf(stderr, "Error: %s\n", description);
    std::cout << description << std::endl;
}

float random_float(float min, float max) {
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_real_distribution<> dis(min, max);
    return (float)dis(gen);
}

std::vector<Vertex> create_rectangle(RectSize size, Origin origin, Color color) {
    std::vector<Vertex> vertices = {
        // Front
        {  origin.x + size.x / 2,  origin.y + size.y / 2, origin.z + size.z / 2, color.r, color.g, color.b },
        {  origin.x + size.x / 2,  origin.y - size.y / 2, origin.z + size.z / 2, color.r, color.g, color.b },
        {  origin.x - size.x / 2,  origin.y + size.y / 2, origin.z + size.z / 2, color.r, color.g, color.b },
        {  origin.x + size.x / 2,  origin.y - size.y / 2, origin.z + size.z / 2, color.r, color.g, color.b },
        {  origin.x - size.x / 2,  origin.y - size.y / 2, origin.z + size.z / 2, color.r, color.g, color.b },
        {  origin.x - size.x / 2,  origin.y + size.y / 2, origin.z + size.z / 2, color.r, color.g, color.b },
        // Back
        {  origin.x + size.x / 2,  origin.y + size.y / 2, origin.z - size.z / 2, color.r, color.g, color.b },
        {  origin.x + size.x / 2,  origin.y - size.y / 2, origin.z - size.z / 2, color.r, color.g, color.b },
        {  origin.x - size.x / 2,  origin.y + size.y / 2, origin.z - size.z / 2, color.r, color.g, color.b },
        {  origin.x + size.x / 2,  origin.y - size.y / 2, origin.z - size.z / 2, color.r, color.g, color.b },
        {  origin.x - size.x / 2,  origin.y - size.y / 2, origin.z - size.z / 2, color.r, color.g, color.b },
        {  origin.x - size.x / 2,  origin.y + size.y / 2, origin.z - size.z / 2, color.r, color.g, color.b },
        // Top
        {  origin.x + size.x / 2,  origin.y + size.y / 2, origin.z + size.z / 2, color.r, color.g, color.b },
        {  origin.x + size.x / 2,  origin.y + size.y / 2, origin.z - size.z / 2, color.r, color.g, color.b },
        {  origin.x - size.x / 2,  origin.y + size.y / 2, origin.z + size.z / 2, color.r, color.g, color.b },
        {  origin.x - size.x / 2,  origin.y + size.y / 2, origin.z + size.z / 2, color.r, color.g, color.b },
        {  origin.x - size.x / 2,  origin.y + size.y / 2, origin.z - size.z / 2, color.r, color.g, color.b },
        {  origin.x + size.x / 2,  origin.y + size.y / 2, origin.z - size.z / 2, color.r, color.g, color.b },
        // Bottom
        {  origin.x + size.x / 2,  origin.y - size.y / 2, origin.z + size.z / 2, color.r, color.g, color.b },
        {  origin.x + size.x / 2,  origin.y - size.y / 2, origin.z - size.z / 2, color.r, color.g, color.b },
        {  origin.x - size.x / 2,  origin.y - size.y / 2, origin.z + size.z / 2, color.r, color.g, color.b },
        {  origin.x - size.x / 2,  origin.y - size.y / 2, origin.z + size.z / 2, color.r, color.g, color.b },
        {  origin.x - size.x / 2,  origin.y - size.y / 2, origin.z - size.z / 2, color.r, color.g, color.b },
        {  origin.x + size.x / 2,  origin.y - size.y / 2, origin.z - size.z / 2, color.r, color.g, color.b },
        // Left
        {  origin.x - size.x / 2,  origin.y + size.y / 2, origin.z + size.z / 2, color.r, color.g, color.b },
        {  origin.x - size.x / 2,  origin.y + size.y / 2, origin.z - size.z / 2, color.r, color.g, color.b },
        {  origin.x - size.x / 2,  origin.y - size.y / 2, origin.z + size.z / 2, color.r, color.g, color.b },
        {  origin.x - size.x / 2,  origin.y - size.y / 2, origin.z + size.z / 2, color.r, color.g, color.b },
        {  origin.x - size.x / 2,  origin.y - size.y / 2, origin.z - size.z / 2, color.r, color.g, color.b },
        {  origin.x - size.x / 2,  origin.y + size.y / 2, origin.z - size.z / 2, color.r, color.g, color.b },
        // Right
        {  origin.x + size.x / 2,  origin.y + size.y / 2, origin.z + size.z / 2, color.r, color.g, color.b },
        {  origin.x + size.x / 2,  origin.y + size.y / 2, origin.z - size.z / 2, color.r, color.g, color.b },
        {  origin.x + size.x / 2,  origin.y - size.y / 2, origin.z + size.z / 2, color.r, color.g, color.b },
        {  origin.x + size.x / 2,  origin.y - size.y / 2, origin.z + size.z / 2, color.r, color.g, color.b },
        {  origin.x + size.x / 2,  origin.y - size.y / 2, origin.z - size.z / 2, color.r, color.g, color.b },
        {  origin.x + size.x / 2,  origin.y + size.y / 2, origin.z - size.z / 2, color.r, color.g, color.b },
    };

    return vertices;
}

int main() {
    // Do initialization
    glfwSetErrorCallback(error_callback);
    if (!glfwInit()) {
        std::cout << "Failed to initizlize GLFW3" << std::endl;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

    // Create window
    GLFWwindow *window = glfwCreateWindow(640, 480, "Fragment", NULL, NULL);

    if (!window) {
        std::cout << "Failed to initizlize window" << std::endl;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glEnable(GL_DEBUG_OUTPUT);
    std::cout << glGetString(GL_VERSION) << std::endl;

    std::vector<Vertex> vertices = {};
    const int num_cubes = 10;
    for (int cube_index = 0; cube_index < num_cubes; cube_index += 1) {

        RectSize size = {random_float(0.1, 0.5), random_float(0.1, 0.5), random_float(0.1, 0.5)};
        Origin origin = {random_float(-0.9, 0.9), random_float(-0.9, 0.9), random_float(-0.9, 0.9)};
        Color color = {random_float(0.0, 1.0), random_float(0.0, 1.0), random_float(0.0, 1.0)};
        std::vector<Vertex> rect = create_rectangle(size, origin, color);
        
        for (int i = 0; i < rect.size(); i += 1) {
            vertices.push_back(rect[i]);
        }
    }
    
    GLuint vertex_buffer, vertex_shader, fragment_shader, program;
    GLint mvp_location, vpos_location, vcol_location;

    glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertices[0]), vertices.data(), GL_STATIC_DRAW);
 
    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_text, NULL);
    glCompileShader(vertex_shader);
 
    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_text, NULL);
    glCompileShader(fragment_shader);
 
    program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);
 
    mvp_location = glGetUniformLocation(program, "MVP");
    vpos_location = glGetAttribLocation(program, "vPos");
    vcol_location = glGetAttribLocation(program, "vCol");
 
    glEnableVertexAttribArray(vpos_location);
    glVertexAttribPointer(vpos_location, 3, GL_FLOAT, GL_FALSE,
                          sizeof(vertices[0]), (void*) 0);
    glEnableVertexAttribArray(vcol_location);
    glVertexAttribPointer(vcol_location, 3, GL_FLOAT, GL_FALSE,
                          sizeof(vertices[0]), (void*) (sizeof(float) * 3));

    while (!glfwWindowShouldClose(window)) {

        float ratio;
        int width, height;

        mat4x4 m, p, mvp;

        glfwGetFramebufferSize(window, &width, &height);
        ratio = width / (float) height;

        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);
 
        mat4x4_identity(m);
        mat4x4_rotate_Z(m, m, (float) glfwGetTime());
        mat4x4_rotate_Y(m, m, (float) glfwGetTime());
        mat4x4_ortho(p, -ratio, ratio, -2.f, 2.f, 2.f, -2.f);
        mat4x4_mul(mvp, p, m);
 
        glUseProgram(program);
        glUniformMatrix4fv(mvp_location, 1, GL_FALSE, (const GLfloat*) mvp);
        glDrawArrays(GL_TRIANGLES, 0, vertices.size());

        glfwSwapBuffers(window);
        glfwPollEvents();  
    }


    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
