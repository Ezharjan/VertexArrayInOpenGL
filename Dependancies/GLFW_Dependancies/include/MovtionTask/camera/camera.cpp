//
//  camera.cpp
//  openGL-T10-cam
//
//  Created by Lax Zhang on 2019/2/28.
//  Copyright © 2019 Lax Zhang. All rights reserved.
//

#include "camera.hpp"

using namespace std;

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch) : camFront(glm::vec3(0.0f, 0.0f, -1.0f)), MouseSensitive(sensitive), MoveSpeed(speed), Zoom(ZOOM){
    
    camPos = position;
    worldUp = up;
    Yaw = yaw;
    Pitch = pitch;
    updateCamVectors();
}

Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : camFront(glm::vec3(0.0f, 0.0f, -1.0f)), MouseSensitive(sensitive), MoveSpeed(speed), Zoom(ZOOM){
    
    camPos = glm::vec3(posX, posY, posZ);
    worldUp = glm::vec3(upX, upY, upZ);
    Yaw = yaw;
    Pitch = pitch;
    updateCamVectors();
}

glm::mat4 Camera::getViewMatrix(){
    return cal_lookat_matrix(camPos, camPos + camFront, camUp);
//    return glm::lookAt(camPos, camPos + camFront, camUp);
}

void Camera::processKeyboard(CAMERA_MOVEMENT direction, float deltaTime){
    float camSpeed = MoveSpeed * deltaTime;
    if (direction == FORWARD)
        camPos += camFront * camSpeed;
    if (direction == BACKWARD)
        camPos -= camFront * camSpeed;
    if (direction == LEFT)
        camPos -= camRight * camSpeed;
    if (direction == RIGHT)
        camPos += camRight * camSpeed;
    // if set camPos.y = 0.0f, then constraint camera in ground.
//    camPos.y = 0.0f;
}

void Camera::processMouseMovement(float x_offset, float y_offset, GLboolean constrainPitch){
    
    x_offset *= MouseSensitive;
    y_offset *= MouseSensitive;
    
    Yaw += x_offset;
    Pitch += y_offset;
    
    if (constrainPitch) {
        if (Pitch >= 89.0f) Pitch = 89.0f;
        if (Pitch <= -89.0f) Pitch = -89.0f;
    }
    
    updateCamVectors();
}

void Camera::processMouseScroll(float y_offset){
    if (Zoom >= 1.0f && Zoom <= 45.0f)
        Zoom -= y_offset;
    if (Zoom <= 1.0f)
        Zoom = 1.0f;
    if (Zoom >= 45.0f)
        Zoom = 45.0f;
}


void Camera::updateCamVectors(){
    // calculate new front vector
    glm::vec3 front;
    front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    front.y = sin(glm::radians(Pitch));
    front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    camFront = glm::normalize(front);
    
    // ReCalculate Right and Up vector
    camRight = glm::normalize(glm::cross(camFront, worldUp));
    camUp = glm::normalize(glm::cross(camRight, camFront));
}

glm::mat4 Camera::cal_lookat_matrix(glm::vec3 position, glm::vec3 target, glm::vec3 up){
    // cal x,y,z axis;
    glm::vec3 zaxis = glm::normalize(position - target);
    glm::vec3 xaxis = glm::normalize(glm::cross(glm::normalize(up), zaxis));
    glm::vec3 yaxis = glm::normalize(glm::cross(zaxis, xaxis));
    
    // cause in glm, visit matrix element by matrix[col][row].
    glm::mat4 translation = glm::mat4(1.0f);
    translation[3][0] = -position.x;
    translation[3][1] = -position.y;
    translation[3][2] = -position.z;
    
    glm::mat4 rotation = glm::mat4(1.0f);
    rotation[0][0] = xaxis.x;
    rotation[1][0] = xaxis.y;
    rotation[2][0] = xaxis.z;
    
    rotation[0][1] = yaxis.x;
    rotation[1][1] = yaxis.y;
    rotation[2][1] = yaxis.z;
    
    rotation[0][2] = zaxis.x;
    rotation[1][2] = zaxis.y;
    rotation[2][2] = zaxis.z;
    
    return rotation * translation;
}
