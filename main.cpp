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
#include "camera.hpp"

struct CubeSize {
    float x, y, z;
};

struct Origin {
    float x, y, z;
};

struct Color {
    float r, g, b;
};

enum KeyboardPress {
    SPACE
};

const int WINDOW_WIDTH = 1200;
const int WINDOW_HEIGHT = 800;

const int CENTER_Y = 50;
const int CENTER_X = 10;
const int CENTER_Z = 10;

Color background_color = {0.2f, 0.2f, 0.2f};

float lastX = WINDOW_WIDTH / 2.0f;
float lastY = WINDOW_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f; 
float lastFrame = 0.0f;

Camera camera = Camera();

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

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.processMouse(xoffset, yoffset);
}

float random_float(float min, float max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(min, max);
    return (float)dis(gen);
}

std::vector<Vertex> create_random_cube() {
    Origin origin = {random_float(-100.0f, 100.0f), random_float(0.0f, 0.0f), random_float(-100.0f, 100.0f)};
    CubeSize size = {random_float(1.0f, 1.0f), random_float(1.0f, 1.0f), random_float(1.0f, 1.0f)};
    Color color = {random_float(0.0, 1.0), random_float(0.0, 1.0), random_float(0.0, 1.0)};
    auto cube = create_cube(size, origin, color);
    return cube;
}

std::vector<Vertex> create_uniform_cube(Origin origin) {
    CubeSize size = {random_float(1.0f, 1.0f), random_float(1.0f, 1.0f), random_float(1.0f, 1.0f)};
    Color color = {random_float(0.0, 1.0), random_float(0.0, 1.0), random_float(0.0, 1.0)};
    auto cube = create_cube(size, origin, color);
    return cube;
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
    Origin origin = {0.0, 0.0, 0.0};
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
            origin.z = 0.0;
        }
        origin.y += 0.5;
        origin.x = 0.0;
    }

    return vertices;
}

auto vertices = init_world(CENTER_X, CENTER_Y, CENTER_Z);

// Create shaders
Shader shader = Shader("shaders/basic.vs", "shaders/basic.fs");

void add_block() {
    auto cube = create_random_cube();
    vertices.insert(vertices.end(), cube.begin(), cube.end());
    shader.bind_buffers(vertices);
}

void process_input(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        camera.processKeyboard(FORWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        camera.processKeyboard(BACKWARD, deltaTime);
    } 
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        camera.processKeyboard(LEFT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        camera.processKeyboard(RIGHT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        add_block();
    }
}

int main(int argc, char* argv[]) {

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

    // Create the window
    auto window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Fragment", NULL, NULL);
    if (!window) {
        std::cout << "GLFW failed to create a window. Terminating" << std::endl;
        glfwTerminate();
        return -1;
    }

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Set callbacks
    glfwSetErrorCallback(error_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

    // Set window as the current context in the main thread
    glfwMakeContextCurrent(window);

    // Initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Compile shaders and link buffers
    shader.compile_shaders();
    shader.bind_buffers(vertices);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_DEBUG_OUTPUT);

    camera.setMovementSpeed(10.0);

    // Render loop   
    while(!glfwWindowShouldClose(window)) {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        process_input(window);
        // Rotate model matrix
        glm::mat4 trans = glm::mat4(1.0f);
        trans = glm::rotate(trans, glm::radians(43.0f), glm::vec3(0.0, 1.0, 0.0));
        // trans = glm::rotate(trans, glm::radians(-camera.getAngle()), glm::vec3(0.0, 1.0, 0.0));
        glUniformMatrix4fv(glGetUniformLocation(shader.getProgram(), "model"), 1, GL_FALSE, glm::value_ptr(trans));
        
        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(45.0f), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.0f);
        glUniformMatrix4fv(glGetUniformLocation(shader.getProgram(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glm::mat4 view = camera.getViewMatrix();
        glUniformMatrix4fv(glGetUniformLocation(shader.getProgram(), "view"), 1, GL_FALSE, glm::value_ptr(view));

        auto camera_position = camera.getPosition();
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
