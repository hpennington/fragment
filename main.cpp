#include <iostream>
#include <vector>
#include <random>
#include <fstream>
#include <string>
#ifdef __APPLE__
    #include <OpenGL/gl3.h>
#else
    #include <OpenGL/gl.h>
#endif
// Include glad before GLFW per documentation
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "glm/glm/glm.hpp"
#include "glm/glm/gtc/matrix_transform.hpp"
#include "glm/glm/ext.hpp"
#include "glm/glm/gtx/string_cast.hpp"
#include "glm/glm/gtc/type_ptr.hpp"
#include "shader.hpp"
#include "vertex.hpp"

struct CubeSize {
    float x, y, z;
};

struct Origin {
    float x, y, z;
};

struct Color {
    float r, g, b;
};

std::vector<Vertex> create_cube(CubeSize size, Origin origin, Color color) {
    std::vector<Vertex> vertices = {
      { -0.5f, -0.5f, -0.5f, color.r, color.g, color.b, 0.0f,  0.0f, -1.0f, },
      {  0.5f, -0.5f, -0.5f, color.r, color.g, color.b, 0.0f,  0.0f, -1.0f, },
      {  0.5f,  0.5f, -0.5f, color.r, color.g, color.b, 0.0f,  0.0f, -1.0f, },
      {  0.5f,  0.5f, -0.5f, color.r, color.g, color.b, 0.0f,  0.0f, -1.0f, },
      { -0.5f,  0.5f, -0.5f, color.r, color.g, color.b, 0.0f,  0.0f, -1.0f, },
      { -0.5f, -0.5f, -0.5f, color.r, color.g, color.b, 0.0f,  0.0f, -1.0f, },

      { -0.5f, -0.5f,  0.5f, color.r, color.g, color.b, 0.0f,  0.0f,  1.0f, },
      {  0.5f, -0.5f,  0.5f, color.r, color.g, color.b, 0.0f,  0.0f,  1.0f, },
      {  0.5f,  0.5f,  0.5f, color.r, color.g, color.b, 0.0f,  0.0f,  1.0f, },
      {  0.5f,  0.5f,  0.5f, color.r, color.g, color.b, 0.0f,  0.0f,  1.0f, },
      { -0.5f,  0.5f,  0.5f, color.r, color.g, color.b, 0.0f,  0.0f,  1.0f, },
      { -0.5f, -0.5f,  0.5f, color.r, color.g, color.b, 0.0f,  0.0f,  1.0f, },

      { -0.5f,  0.5f,  0.5f, color.r, color.g, color.b, 1.0f,  0.0f,  0.0f, },
      { -0.5f,  0.5f, -0.5f, color.r, color.g, color.b, 1.0f,  0.0f,  0.0f, },
      { -0.5f, -0.5f, -0.5f, color.r, color.g, color.b, 1.0f,  0.0f,  0.0f, },
      { -0.5f, -0.5f, -0.5f, color.r, color.g, color.b, 1.0f,  0.0f,  0.0f, },
      { -0.5f, -0.5f,  0.5f, color.r, color.g, color.b, 1.0f,  0.0f,  0.0f, },
      { -0.5f,  0.5f,  0.5f, color.r, color.g, color.b, 1.0f,  0.0f,  0.0f, },

      {  0.5f,  0.5f,  0.5f, color.r, color.g, color.b, 1.0f,  0.0f,  0.0f, },
      {  0.5f,  0.5f, -0.5f, color.r, color.g, color.b, 1.0f,  0.0f,  0.0f, },
      {  0.5f, -0.5f, -0.5f, color.r, color.g, color.b, 1.0f,  0.0f,  0.0f, },
      {  0.5f, -0.5f, -0.5f, color.r, color.g, color.b, 1.0f,  0.0f,  0.0f, },
      {  0.5f, -0.5f,  0.5f, color.r, color.g, color.b, 1.0f,  0.0f,  0.0f, },
      {  0.5f,  0.5f,  0.5f, color.r, color.g, color.b, 1.0f,  0.0f,  0.0f, },

      { -0.5f, -0.5f, -0.5f, color.r, color.g, color.b, 0.0f, -1.0f,  0.0f, },
      {  0.5f, -0.5f, -0.5f, color.r, color.g, color.b, 0.0f, -1.0f,  0.0f, },
      {  0.5f, -0.5f,  0.5f, color.r, color.g, color.b, 0.0f, -1.0f,  0.0f, },
      {  0.5f, -0.5f,  0.5f, color.r, color.g, color.b, 0.0f, -1.0f,  0.0f, },
      { -0.5f, -0.5f,  0.5f, color.r, color.g, color.b, 0.0f, -1.0f,  0.0f, },
      { -0.5f, -0.5f, -0.5f, color.r, color.g, color.b, 0.0f, -1.0f,  0.0f, },

      { -0.5f,  0.5f, -0.5f, color.r, color.g, color.b, 0.0f,  1.0f,  0.0f, },
      {  0.5f,  0.5f, -0.5f, color.r, color.g, color.b, 0.0f,  1.0f,  0.0f, },
      {  0.5f,  0.5f,  0.5f, color.r, color.g, color.b, 0.0f,  1.0f,  0.0f, },
      {  0.5f,  0.5f,  0.5f, color.r, color.g, color.b, 0.0f,  1.0f,  0.0f, },
      { -0.5f,  0.5f,  0.5f, color.r, color.g, color.b, 0.0f,  1.0f,  0.0f, },
      { -0.5f,  0.5f, -0.5f, color.r, color.g, color.b, 0.0f,  1.0f,  0.0f, },
        // // Front
        // { origin.x + size.x / 2,  origin.y + size.y / 2, origin.z + size.z / 2, color.r, color.g, color.b, 0.0f,  0.0f, 1.0f, },
        // { origin.x + size.x / 2,  origin.y - size.y / 2, origin.z + size.z / 2, color.r, color.g, color.b, 0.0f,  0.0f, 1.0f, },
        // { origin.x - size.x / 2,  origin.y + size.y / 2, origin.z + size.z / 2, color.r, color.g, color.b, 0.0f,  0.0f, 1.0f, },
        // { origin.x + size.x / 2,  origin.y - size.y / 2, origin.z + size.z / 2, color.r, color.g, color.b, 0.0f,  0.0f, 1.0f, },
        // { origin.x - size.x / 2,  origin.y - size.y / 2, origin.z + size.z / 2, color.r, color.g, color.b, 0.0f,  0.0f, 1.0f, },
        // { origin.x - size.x / 2,  origin.y + size.y / 2, origin.z + size.z / 2, color.r, color.g, color.b, 0.0f,  0.0f, 1.0f, },
        // // Back
        // { origin.x + size.x / 2,  origin.y + size.y / 2, origin.z - size.z / 2, color.r, color.g, color.b, 0.0f,  0.0f, -1.0f, },
        // { origin.x + size.x / 2,  origin.y - size.y / 2, origin.z - size.z / 2, color.r, color.g, color.b, 0.0f,  0.0f, -1.0f, },
        // { origin.x - size.x / 2,  origin.y + size.y / 2, origin.z - size.z / 2, color.r, color.g, color.b, 0.0f,  0.0f, -1.0f, },
        // { origin.x + size.x / 2,  origin.y - size.y / 2, origin.z - size.z / 2, color.r, color.g, color.b, 0.0f,  0.0f, -1.0f, },
        // { origin.x - size.x / 2,  origin.y - size.y / 2, origin.z - size.z / 2, color.r, color.g, color.b, 0.0f,  0.0f, -1.0f, },
        // { origin.x - size.x / 2,  origin.y + size.y / 2, origin.z - size.z / 2, color.r, color.g, color.b, 0.0f,  0.0f, -1.0f, },
        // // Top
        // { origin.x + size.x / 2,  origin.y + size.y / 2, origin.z + size.z / 2, color.r, color.g, color.b, 0.0f,  1.0f,  0.0f },
        // { origin.x + size.x / 2,  origin.y + size.y / 2, origin.z - size.z / 2, color.r, color.g, color.b, 0.0f,  1.0f,  0.0f },
        // { origin.x - size.x / 2,  origin.y + size.y / 2, origin.z + size.z / 2, color.r, color.g, color.b, 0.0f,  1.0f,  0.0f },
        // { origin.x - size.x / 2,  origin.y + size.y / 2, origin.z + size.z / 2, color.r, color.g, color.b, 0.0f,  1.0f,  0.0f },
        // { origin.x - size.x / 2,  origin.y + size.y / 2, origin.z - size.z / 2, color.r, color.g, color.b, 0.0f,  1.0f,  0.0f },
        // { origin.x + size.x / 2,  origin.y + size.y / 2, origin.z - size.z / 2, color.r, color.g, color.b, 0.0f,  1.0f,  0.0f },
        // // Bottom
        // { origin.x + size.x / 2,  origin.y - size.y / 2, origin.z + size.z / 2, color.r, color.g, color.b, 0.0f,  -1.0f,  0.0f, },
        // { origin.x + size.x / 2,  origin.y - size.y / 2, origin.z - size.z / 2, color.r, color.g, color.b, 0.0f,  -1.0f,  0.0f, },
        // { origin.x - size.x / 2,  origin.y - size.y / 2, origin.z + size.z / 2, color.r, color.g, color.b, 0.0f,  -1.0f,  0.0f, },
        // { origin.x - size.x / 2,  origin.y - size.y / 2, origin.z + size.z / 2, color.r, color.g, color.b, 0.0f,  -1.0f,  0.0f, },
        // { origin.x - size.x / 2,  origin.y - size.y / 2, origin.z - size.z / 2, color.r, color.g, color.b, 0.0f,  -1.0f,  0.0f, },
        // { origin.x + size.x / 2,  origin.y - size.y / 2, origin.z - size.z / 2, color.r, color.g, color.b, 0.0f,  -1.0f,  0.0f, },
        // // Left
        // { origin.x - size.x / 2,  origin.y + size.y / 2, origin.z + size.z / 2, color.r, color.g, color.b, -1.0f, 0.0f,  0.0f, },
        // { origin.x - size.x / 2,  origin.y + size.y / 2, origin.z - size.z / 2, color.r, color.g, color.b, -1.0f, 0.0f,  0.0f, },
        // { origin.x - size.x / 2,  origin.y - size.y / 2, origin.z + size.z / 2, color.r, color.g, color.b, -1.0f, 0.0f,  0.0f, },
        // { origin.x - size.x / 2,  origin.y - size.y / 2, origin.z + size.z / 2, color.r, color.g, color.b, -1.0f, 0.0f,  0.0f, },
        // { origin.x - size.x / 2,  origin.y - size.y / 2, origin.z - size.z / 2, color.r, color.g, color.b, -1.0f, 0.0f,  0.0f, },
        // { origin.x - size.x / 2,  origin.y + size.y / 2, origin.z - size.z / 2, color.r, color.g, color.b, -1.0f, 0.0f,  0.0f, },
        // // Right
        // { origin.x + size.x / 2,  origin.y + size.y / 2, origin.z + size.z / 2, color.r, color.g, color.b, 1.0f,  0.0f,  0.0f, },
        // { origin.x + size.x / 2,  origin.y + size.y / 2, origin.z - size.z / 2, color.r, color.g, color.b, 1.0f,  0.0f,  0.0f, },
        // { origin.x + size.x / 2,  origin.y - size.y / 2, origin.z + size.z / 2, color.r, color.g, color.b, 1.0f,  0.0f,  0.0f, },
        // { origin.x + size.x / 2,  origin.y - size.y / 2, origin.z + size.z / 2, color.r, color.g, color.b, 1.0f,  0.0f,  0.0f, },
        // { origin.x + size.x / 2,  origin.y - size.y / 2, origin.z - size.z / 2, color.r, color.g, color.b, 1.0f,  0.0f,  0.0f, },
        // { origin.x + size.x / 2,  origin.y + size.y / 2, origin.z - size.z / 2, color.r, color.g, color.b, 1.0f,  0.0f,  0.0f, },
    };

    return vertices;
}

// float random_float(float min, float max) {
//     std::random_device rd;
//     std::mt19937 gen(rd());
//     std::uniform_real_distribution<> dis(min, max);
//     return (float)dis(gen);
// }

// std::vector<Vertex> create_random_rect() {
//     Origin origin = {random_float(0.1, 10.0), random_float(0.1, 10.0), random_float(0.1, 100.0)};
//     CubeSize size = {random_float(0.1, 0.5), random_float(0.1, 0.5), random_float(0.1, 0.5)};
//     Color color = {random_float(0.0, 1.0), random_float(0.0, 1.0), random_float(0.0, 1.0)};
//     auto rect = create_rectangle(size, origin, color);
//     return rect;
// }

// char* string_to_mutable_char_array(std::string str) {
//     auto cstr = new char[str.length()];
//     strcpy(cstr, str.c_str());
//     return cstr;
// }

void error_callback(int error, const char* description) {
    fprintf(stderr, "Error: %s\n", description);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}  

int main(int argc, char* argv[]) {
    const int WINDOW_WIDTH = 1200;
    const int WINDOW_HEIGHT = 800;

    // Color background_color = {0.0f, 1.0f, 199.0f/255.0f};
    Color background_color = {0.0f, 0.0f, 0.0f};

    // Create cube in clip space coordinates
    CubeSize size = {0.5, 0.5, 0.5};
    Origin origin = {0.0, 0.0, -0.5};
    Color color = {136.0f/255.0f, 0.0, 1.0};
    std::vector<Vertex> vertices = create_cube(size, origin, color);

    if (glfwInit() == GLFW_FALSE) {
        std::cout << "GLFW failed to initialize" << std::endl;
        return -1;
    }

    std::cout << "GLFW Initialized!" << std::endl;

    // Set the version and use the core profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // Set callbacks
    glfwSetErrorCallback(error_callback);

    // Create the window
    auto window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Fragment", NULL, NULL);
    if (!window) {
        std::cout << "GLFW failed to create a window. Terminating" << std::endl;
        glfwTerminate();
        return -1;
    }
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_DEBUG_OUTPUT);
    
    // Setup viewport and viewport resizing callback
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Set window as the current context in the main thread
    glfwMakeContextCurrent(window);

    // Initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Create shaders link and bind VBO and VAO objects
    Shader shader = Shader("shaders/basic.vs", "shaders/basic.fs");
    shader.bind_buffers(vertices);

    // Rotate model matrix
    glm::mat4 trans = glm::mat4(1.0f);
    trans = glm::rotate(trans, glm::radians(43.0f), glm::vec3(1.0, 1.0, 1.0));
    // trans = glm::rotate(trans, glm::radians(3.0f), glm::vec3(1.0, 0.0, 0.0));
    glUniformMatrix4fv(glGetUniformLocation(shader.getProgram(), "model"), 1, GL_FALSE, glm::value_ptr(trans));

    // Render loop   
    while(!glfwWindowShouldClose(window)) {
        // Set the background color
        glClearColor(background_color.r, background_color.g, background_color.b, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(shader.getProgram());
        glBindVertexArray(shader.getVAO());
        glDrawArrays(GL_TRIANGLES, 0, vertices.size());
        // glDrawElements(GL_TRIANGLES, vertices.size(), GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}
