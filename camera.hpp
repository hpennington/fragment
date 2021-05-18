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
    Camera() {
        glm::vec3 front;
        front.x = cos(glm::radians(this->angle));
        front.z = sin(glm::radians(this->angle));
        this->front = glm::normalize(front);
    }

    void process_input(Camera_Movement movement) {
        switch (movement) {
            case FORWARD:
                this->position += this->front * 0.25f;
                break;
            case BACKWARD:
                this->position -= this->front * 0.25f;
                break;
            case LEFT:
                this->position -= this->right * 0.25f;
                break;
            case RIGHT:
                this->position += this->right * 0.25f;
                break;
        }
    }

    void process_mouse(float xOffset, float yOffset) {
        if (xOffset > 0) {
            this->angle += 3;
        } else {
            this->angle -= 3;
        }

        this->updateCameraVectors();
    }

    glm::mat4 getViewMatrix() {
        glm::mat4 view = glm::mat4(1.0f);
        view = glm::lookAt(this->position, this->position + this->front, this->up);
        return view;
    }

    glm::vec3 getPosition() {
        return this->position;
    }

private:
    glm::vec3 position = glm::vec3(0.0f, 0.0f, 3.0f);
    glm::vec3 target = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 direction = glm::normalize(position - target);
    glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 right = glm::normalize(glm::cross(this->front, this->up));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    float angle = glm::radians(0.0f);

    void updateCameraVectors() {
        // calculate the new Front vector
        glm::vec3 front;
        front.x = cos(glm::radians(this->angle));
        front.z = sin(glm::radians(this->angle));
        this->front = glm::normalize(front);
        this->right = glm::normalize(glm::cross(this->front, this->up));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
        this->up = glm::normalize(glm::cross(this->right, this->front));
    }
};

#endif