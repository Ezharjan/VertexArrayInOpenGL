//
//  camera.hpp
//  openGL-T10-cam
//


#ifndef CAMERA_H
#define CAMERA_H

#include <iostream>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum CAMERA_MOVEMENT{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

const float PITCH = 0.0f;
const float YAW = -90.0f;
const float speed = 2.50f;
const float sensitive = 0.1f;
const float ZOOM = 45.0f;

class Camera{
public:
    // camera attributes
    glm::vec3 camPos;
    glm::vec3 camFront;
    glm::vec3 camUp;
    glm::vec3 camRight;
    glm::vec3 worldUp;
    // Eular angles
    float Yaw;
    float Pitch;
    // camera options
    float MoveSpeed;
    float MouseSensitive;
    float Zoom;
    
    // as vec to construct
    Camera(glm::vec3 position  = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);
    // as scarlar to construct
    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);
    
    glm::mat4 getViewMatrix();
    
    // 键盘，鼠标交互函数
    void processKeyboard(CAMERA_MOVEMENT direction, float deltaTime);
    void processMouseMovement(float x_offset, float y_offset, GLboolean constrainPitch = GL_TRUE);
    void processMouseScroll(float y_offset);
    
private:
    void updateCamVectors();
    glm::mat4 cal_lookat_matrix(glm::vec3, glm::vec3, glm::vec3); // rewrite glm lookat func
};

#endif /* camera_hpp */
