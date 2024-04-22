#pragma once
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>
#include "InputAction.hpp"

class Camera {
public:
    Camera(int screenWidth, int screenHeight, float pos_x, float pos_y);

    void setPosition(float x, float y);

    void setZoomLevel(float zoom);

    void update(float deltaTime, InputAction direction);

    glm::mat4 GetViewMatrix();
    

private:
    int m_screenWidth;
    int m_screenHeight;
    float m_positionX;
    float m_positionY;
    float m_zoomLevel;
    float cameraSpeed;
};
