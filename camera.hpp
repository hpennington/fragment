#ifndef CAMERA_H
#define CAMERA_H

#ifdef __APPLE__
    #include <OpenGL/gl3.h>
#else
    #include <OpenGL/gl.h>
#endif
// Include glad before GLFW per documentation
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "glm/glm/glm.hpp"

enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

class Camera {
public:
    void process_input(Camera_Movement movement) {
        switch (movement) {
            case FORWARD:
                this->position.z += 0.25;
                break;
            case BACKWARD:
                this->position.z -= 0.25;
                break;
            case LEFT:
                this->position.x += 0.25;
                break;
            case RIGHT:
                this->position.x -= 0.25;
                break;
        }
    }

    void process_mouse(float xOffset, float yOffset) {
        if (xOffset > 0) {
            this->angle += 1.0f;    
        } else {
            this->angle -= 1.0f;    
        }
        
    }

    glm::mat4 getViewMatrix() {
        glm::mat4 view = glm::mat4(1.0f);
        view = glm::translate(view, this->position);
        view = glm::rotate(view, glm::radians(this->angle), glm::vec3(0.0f, 1.0f, 0.0f));  
        return view;
    }

    glm::vec3 getPosition() {
        return this->position;
    }

private:
    glm::vec3 position = glm::vec3(0.0f, 0.0f, -3.0f);
    float angle = glm::radians(0.0f);
};

#endif