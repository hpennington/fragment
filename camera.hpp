#ifndef CAMERA_H
#define CAMERA_H

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
                this->position.z += 1;
                break;
            case BACKWARD:
                this->position.z -= 1;
                break;
            case LEFT:
                this->position.x += 1;
                break;
            case RIGHT:
                this->position.x -= 1;
                break;
        }
    }

    glm::vec3 getPosition() {
        return this->position;
    }

private:
    glm::vec3 position = glm::vec3(0.0, 0.0, -3.0);

};

#endif