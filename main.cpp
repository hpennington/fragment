#include <iostream>
#include <random>
#include <GLFW/glfw3.h>
#include "glad/glad.h"
#include <OpenGL/gl.h>
#include "linmath.h"

static const int num_vertices = 36;
static const struct {
    float x, y, z, r, g, b;
} vertices[num_vertices] = {
    // Front 
    {  0.75f,  0.75f, 0.75f, 1.f, 0.f, 0.f },
    {  0.75f, -0.75f, 0.75f, 1.f, 0.f, 0.f },
    { -0.75f,  0.75f, 0.75f, 1.f, 0.f, 0.f },
    {  0.75f, -0.75f, 0.75f, 1.f, 0.f, 0.f },
    { -0.75f, -0.75f, 0.75f, 1.f, 0.f, 0.f },
    { -0.75f,  0.75f, 0.75f, 1.f, 0.f, 0.f },
    // Back
    {  0.75f,  0.75f, -0.75f, 1.f, 1.f, 0.f },
    {  0.75f, -0.75f, -0.75f, 1.f, 1.f, 0.f },
    { -0.75f,  0.75f, -0.75f, 1.f, 1.f, 0.f },
    {  0.75f, -0.75f, -0.75f, 1.f, 1.f, 0.f },
    { -0.75f, -0.75f, -0.75f, 1.f, 1.f, 0.f },
    { -0.75f,  0.75f, -0.75f, 1.f, 1.f, 0.f },
    // Top
    {  0.75f,  0.75f, 0.75f, 1.f, 1.f, 1.f },
    {  0.75f, 0.75f, -0.75f, 1.f, 1.f, 1.f },
    { -0.75f,  0.75f, 0.75f, 1.f, 1.f, 1.f },
    {  -0.75f,  0.75f, 0.75f, 1.f, 1.f, 1.f },
    {  -0.75f, 0.75f, -0.75f, 1.f, 1.f, 1.f },
    { 0.75f,  0.75f, -0.75f, 1.f, 1.f, 1.f },
    // Bottom
    {  0.75f,  -0.75f, 0.75f, 0.f, 1.f, 1.f },
    {  0.75f, -0.75f, -0.75f, 0.f, 1.f, 1.f },
    { -0.75f,  -0.75f, 0.75f, 0.f, 1.f, 1.f },
    {  -0.75f,  -0.75f, 0.75f, 0.f, 1.f, 1.f },
    {  -0.75f, -0.75f, -0.75f, 0.f, 1.f, 1.f },
    { 0.75f,  -0.75f, -0.75f, 0.f, 1.f, 1.f },
    // Left
    { -0.75f, 0.75f, 0.75f, 0.5f, 1.f, 1.f },
    { -0.75f, 0.75f, -0.75f, 0.5f, 1.f, 1.f },
    { -0.75f,  -0.75f, 0.75f, 0.5f, 1.f, 1.f },
    { -0.75f,  -0.75f, 0.75f, 0.5f, 1.f, 1.f },
    { -0.75f, -0.75f, -0.75f, 0.5f, 1.f, 1.f },
    { -0.75f,  0.75f, -0.75f, 0.5f, 1.f, 1.f },
    // Right
    { 0.75f, 0.75f, 0.75f, 0.25f, 1.f, 1.f },
    { 0.75f, 0.75f, -0.75f, 0.25f, 1.f, 1.f },
    { 0.75f,  -0.75f, 0.75f, 0.25f, 1.f, 1.f },
    { 0.75f,  -0.75f, 0.75f, 0.25f, 1.f, 1.f },
    { 0.75f, -0.75f, -0.75f, 0.25f, 1.f, 1.f },
    { 0.75f,  0.75f, -0.75f, 0.25f, 1.f, 1.f },
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
}

int main() {
    // Do initialization
    glfwSetErrorCallback(error_callback);
    if (!glfwInit()) {
        std::cout << "Failed to initizlize GLFW3" << std::endl;
    }

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

    GLuint vertex_buffer, vertex_shader, fragment_shader, program;
    GLint mvp_location, vpos_location, vcol_location;

    glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
 
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

        // Enable depth test
        glEnable(GL_DEPTH_TEST);
        // Accept fragment if it closer to the camera than the former one
        glDepthFunc(GL_LESS);
        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 
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
        glDrawArrays(GL_TRIANGLES, 0, num_vertices);

        glfwSwapBuffers(window);
        glfwPollEvents();  
    }


    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
