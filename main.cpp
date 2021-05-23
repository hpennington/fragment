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

Color background_color = {216.0f / 255.0f, 242.0f / 255.0f, 255.0f / 255.0f};

float lastX = WINDOW_WIDTH / 2.0f;
float lastY = WINDOW_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f; 
float lastFrame = 0.0f;

Camera camera = Camera(glm::vec3(0.0f, 2.0f, 0.0f));

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
    CubeSize size = {random_float(10.0f, 20.0f), random_float(10.0f, 100.0f), random_float(10.0f, 20.0f)};
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

std::vector<Vertex> init_world() {
    std::vector<Vertex> vertices = {};

    // Create ground plane/cube
    CubeSize size = {1000, 0.1, 1000};
    Origin origin = {0.0, 0.0, 0.0};
    Color color = {127.0f / 255.0f, 0.98f, 0.0f};
    auto ground = create_cube(size, origin, color);
    vertices.insert(vertices.end(), ground.begin(), ground.end());

    // Create buildings
    for (int i = 0; i < 100; i += 1) {
        float colorElement = random_float(0.5f, 0.75f);
        color = {colorElement, colorElement, colorElement};
        size = {random_float(30.0f, 80.0f), random_float(10.0f, 100.0f), random_float(30.0f, 80.0f)};
        origin = {random_float(-500.0f, 500.0f), size.y / 2, random_float(-500.0f, 500.0f)};
        auto building = create_cube(size, origin, color);
        vertices.insert(vertices.end(), building.begin(), building.end());
    }

    // Create golden cube
    size = {10, 10, 10};
    origin = {random_float(-500.0f, 500.0f), 0.0, random_float(-500.0f, 500.0f)};
    color = {255.0f / 255.0f, 215.0f / 255.0f, 0.0f};
    auto goldenCube = create_cube(size, origin, color);
    vertices.insert(vertices.end(), goldenCube.begin(), goldenCube.end());

    return vertices;
}

auto vertices = init_world();

// Create shaders
Shader shader = Shader("shaders/basic.vs", "shaders/basic.fs");

void add_block() {
    Origin origin = {camera.getPosition().x + camera.Front.x * 4, camera.getPosition().y + camera.Front.y * 4, camera.getPosition().z + camera.Front.z * 4};
    auto cube = create_uniform_cube(origin);
    vertices.insert(vertices.end(), cube.begin(), cube.end());
    shader.bind_buffers(vertices);
}

bool SPACE_DOWN = false;

void process_input(GLFWwindow* window) {
    // std::cout << camera.getPosition().x << " " << camera.getPosition().z << std::endl;
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
        SPACE_DOWN = true;
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE) {
        if (SPACE_DOWN) {
            add_block();
            SPACE_DOWN = false;
        }
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
    if (!shader.compile_shaders()) {
        std::cout << "Failed to compile shaders" << std::endl;
        return -1;
    }

    shader.bind_buffers(vertices);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_DEBUG_OUTPUT);

    camera.setMovementSpeed(40.0);

    // Render loop   
    while(!glfwWindowShouldClose(window)) {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        process_input(window);

        // Model matrix
        glm::mat4 trans = glm::mat4(1.0f);
        glUniformMatrix4fv(glGetUniformLocation(shader.getProgram(), "model"), 1, GL_FALSE, glm::value_ptr(trans));
        
        // Projection matrix
        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(45.0f), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 1000.0f);
        glUniformMatrix4fv(glGetUniformLocation(shader.getProgram(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));

        // View matrix
        glm::mat4 view = camera.getViewMatrix();
        glUniformMatrix4fv(glGetUniformLocation(shader.getProgram(), "view"), 1, GL_FALSE, glm::value_ptr(view));

        // Set camera_position for specular highlights
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
