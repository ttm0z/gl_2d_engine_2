#pragma once
#include <glm.hpp>

class Camera {
public:
    Camera(int screenWidth, int screenHeight);

    void setPosition(float x, float y);

    void setZoomLevel(float zoom);

    glm::mat4 GetViewMatrix() const;
    

private:
    float m_screenWidth;
    float m_screenHeight;
    float m_positionX;
    float m_positionY;
    float m_zoomLevel;
};
