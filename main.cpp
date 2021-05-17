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
        // Front
        { origin.x + size.x / 2,  origin.y + size.y / 2, origin.z + size.z / 2, color.r, color.g, color.b, 0.0f, 0.0f, 1.0f, },
        { origin.x + size.x / 2,  origin.y - size.y / 2, origin.z + size.z / 2, color.r, color.g, color.b, 0.0f, 0.0f, 1.0f, },
        { origin.x - size.x / 2,  origin.y + size.y / 2, origin.z + size.z / 2, color.r, color.g, color.b, 0.0f, 0.0f, 1.0f, },
        { origin.x + size.x / 2,  origin.y - size.y / 2, origin.z + size.z / 2, color.r, color.g, color.b, 0.0f, 0.0f, 1.0f, },
        { origin.x - size.x / 2,  origin.y - size.y / 2, origin.z + size.z / 2, color.r, color.g, color.b, 0.0f, 0.0f, 1.0f, },
        { origin.x - size.x / 2,  origin.y + size.y / 2, origin.z + size.z / 2, color.r, color.g, color.b, 0.0f, 0.0f, 1.0f, },
        // Back
        { origin.x + size.x / 2,  origin.y + size.y / 2, origin.z - size.z / 2, color.r, color.g, color.b, 0.0f, 0.0f, -1.0f, },
        { origin.x + size.x / 2,  origin.y - size.y / 2, origin.z - size.z / 2, color.r, color.g, color.b, 0.0f, 0.0f, -1.0f, },
        { origin.x - size.x / 2,  origin.y + size.y / 2, origin.z - size.z / 2, color.r, color.g, color.b, 0.0f, 0.0f, -1.0f, },
        { origin.x + size.x / 2,  origin.y - size.y / 2, origin.z - size.z / 2, color.r, color.g, color.b, 0.0f, 0.0f, -1.0f, },
        { origin.x - size.x / 2,  origin.y - size.y / 2, origin.z - size.z / 2, color.r, color.g, color.b, 0.0f, 0.0f, -1.0f, },
        { origin.x - size.x / 2,  origin.y + size.y / 2, origin.z - size.z / 2, color.r, color.g, color.b, 0.0f, 0.0f, -1.0f, },
        // Top
        { origin.x + size.x / 2,  origin.y + size.y / 2, origin.z + size.z / 2, color.r, color.g, color.b, 0.0f, 1.0f, 0.0f, },
        { origin.x + size.x / 2,  origin.y + size.y / 2, origin.z - size.z / 2, color.r, color.g, color.b, 0.0f, 1.0f, 0.0f, },
        { origin.x - size.x / 2,  origin.y + size.y / 2, origin.z + size.z / 2, color.r, color.g, color.b, 0.0f, 1.0f, 0.0f, },
        { origin.x - size.x / 2,  origin.y + size.y / 2, origin.z + size.z / 2, color.r, color.g, color.b, 0.0f, 1.0f, 0.0f, },
        { origin.x - size.x / 2,  origin.y + size.y / 2, origin.z - size.z / 2, color.r, color.g, color.b, 0.0f, 1.0f, 0.0f, },
        { origin.x + size.x / 2,  origin.y + size.y / 2, origin.z - size.z / 2, color.r, color.g, color.b, 0.0f, 1.0f, 0.0f, },
        // Bottom
        { origin.x + size.x / 2,  origin.y - size.y / 2, origin.z + size.z / 2, color.r, color.g, color.b, 0.0f, -1.0f, 0.0f, },
        { origin.x + size.x / 2,  origin.y - size.y / 2, origin.z - size.z / 2, color.r, color.g, color.b, 0.0f, -1.0f, 0.0f, },
        { origin.x - size.x / 2,  origin.y - size.y / 2, origin.z + size.z / 2, color.r, color.g, color.b, 0.0f, -1.0f, 0.0f, },
        { origin.x - size.x / 2,  origin.y - size.y / 2, origin.z + size.z / 2, color.r, color.g, color.b, 0.0f, -1.0f, 0.0f, },
        { origin.x - size.x / 2,  origin.y - size.y / 2, origin.z - size.z / 2, color.r, color.g, color.b, 0.0f, -1.0f, 0.0f, },
        { origin.x + size.x / 2,  origin.y - size.y / 2, origin.z - size.z / 2, color.r, color.g, color.b, 0.0f, -1.0f, 0.0f, },
        // Left
        { origin.x - size.x / 2,  origin.y + size.y / 2, origin.z + size.z / 2, color.r, color.g, color.b, -1.0f, 0.0f, 0.0f, },
        { origin.x - size.x / 2,  origin.y + size.y / 2, origin.z - size.z / 2, color.r, color.g, color.b, -1.0f, 0.0f, 0.0f, },
        { origin.x - size.x / 2,  origin.y - size.y / 2, origin.z + size.z / 2, color.r, color.g, color.b, -1.0f, 0.0f, 0.0f, },
        { origin.x - size.x / 2,  origin.y - size.y / 2, origin.z + size.z / 2, color.r, color.g, color.b, -1.0f, 0.0f, 0.0f, },
        { origin.x - size.x / 2,  origin.y - size.y / 2, origin.z - size.z / 2, color.r, color.g, color.b, -1.0f, 0.0f, 0.0f, },
        { origin.x - size.x / 2,  origin.y + size.y / 2, origin.z - size.z / 2, color.r, color.g, color.b, -1.0f, 0.0f, 0.0f, },
        // Right
        { origin.x + size.x / 2,  origin.y + size.y / 2, origin.z + size.z / 2, color.r, color.g, color.b, 1.0f,  0.0f, 0.0f, },
        { origin.x + size.x / 2,  origin.y + size.y / 2, origin.z - size.z / 2, color.r, color.g, color.b, 1.0f,  0.0f, 0.0f, },
        { origin.x + size.x / 2,  origin.y - size.y / 2, origin.z + size.z / 2, color.r, color.g, color.b, 1.0f,  0.0f, 0.0f, },
        { origin.x + size.x / 2,  origin.y - size.y / 2, origin.z + size.z / 2, color.r, color.g, color.b, 1.0f,  0.0f, 0.0f, },
        { origin.x + size.x / 2,  origin.y - size.y / 2, origin.z - size.z / 2, color.r, color.g, color.b, 1.0f,  0.0f, 0.0f, },
        { origin.x + size.x / 2,  origin.y + size.y / 2, origin.z - size.z / 2, color.r, color.g, color.b, 1.0f,  0.0f, 0.0f, },
    };

    return vertices;
}

float random_float(float min, float max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(min, max);
    return (float)dis(gen);
}

std::vector<Vertex> create_random_cube() {
    Origin origin = {random_float(-1.0f, 1.0f), random_float(-1.0f, 1.0f), random_float(-1.0f, 1.0f)};
    CubeSize size = {random_float(0.1, 0.5), random_float(0.1, 0.5), random_float(0.1, 0.5)};
    Color color = {random_float(0.0, 1.0), random_float(0.0, 1.0), random_float(0.0, 1.0)};
    auto rect = create_cube(size, origin, color);
    return rect;
}

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

std::vector<Vertex> init_world(int x, int y, int z) {
    // Create cube in clip space coordinates
    CubeSize size = {0.5, 0.5, 0.5};
    Origin origin = {0.0, -0.5, -0.5};
    Color color = {136.0f/255.0f, 0.0, 1.0};
    std::vector<Vertex> vertices = {};

    for (int i = 0; i < y; i += 1) {
        for (int j = 0; j < x; j += 1) {
            for (int k = 0; k < z; k += 1) {
                auto cube = create_cube(size, origin, color);
                vertices.insert(vertices.begin(), cube.begin(), cube.end());
                origin.z += 0.5;
            }

            origin.x += 0.5;
            origin.z = -0.5;
        }
        origin.y += 0.5;
        origin.x = 0.0;
    }

    return vertices;
}

int main(int argc, char* argv[]) {
    const int WINDOW_WIDTH = 1200;
    const int WINDOW_HEIGHT = 800;
    
    const int WORLD_Y = 5;
    const int WORLD_X = 10;
    const int WORLD_Z = 10;

    // Color background_color = {0.0f, 1.0f, 199.0f/255.0f};
    Color background_color = {0.1f, 0.1f, 0.1f};
    
    auto vertices = init_world(WORLD_X, WORLD_Y, WORLD_Z);

    auto camera_position = glm::vec3(0.0f, 0.0f, 0.0f);

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

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_DEBUG_OUTPUT);

    // Rotate model matrix
    glm::mat4 trans = glm::mat4(1.0f);
    trans = glm::rotate(trans, glm::radians(43.0f), glm::vec3(1.0, 1.0, 1.0));
    // trans = glm::rotate(trans, glm::radians(3.0f), glm::vec3(1.0, 0.0, 0.0));
    glUniformMatrix4fv(glGetUniformLocation(shader.getProgram(), "model"), 1, GL_FALSE, glm::value_ptr(trans));
    
    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(45.0f), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.0f);
    glUniformMatrix4fv(glGetUniformLocation(shader.getProgram(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));

    // Render loop   
    while(!glfwWindowShouldClose(window)) {

        glm::mat4 view = glm::mat4(1.0f);
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -20.0f));
        view = glm::rotate(view, glm::radians(90.0f * (float)glfwGetTime()), glm::vec3(1.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.getProgram(), "view"), 1, GL_FALSE, glm::value_ptr(view));
        camera_position = glm::vec3(1.0f, 10.0f, 20.0f);
        glUniform3fv(glGetUniformLocation(shader.getProgram(), "camera_position"), 1, &camera_position[0]);

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
