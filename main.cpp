#include <iostream>
#include <GLFW/glfw3.h>
#include "glad/glad.h"
#include <OpenGL/gl.h>

void error_callback(int error, const char* description)
{
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

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glViewport(0, 0, width, height);

    while (!glfwWindowShouldClose(window))
    {
        glfwSwapBuffers(window);
        glfwPollEvents();  
    }


    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
