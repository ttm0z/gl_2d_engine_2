
#include "Camera.hpp"

Camera::Camera(int screenWidth, int screenHeight, float pos_x, float pos_y) 
: m_screenWidth(screenWidth), m_screenHeight(screenHeight), m_positionX(pos_x), 
  m_positionY(pos_y), cameraSpeed(1)
{

}
//* Let input manager handle it and pass a simplified enum to camera

 void Camera::update(float deltaTime, InputAction direction){
     if (direction == InputAction::Left) {
         m_positionX -= cameraSpeed * deltaTime;
     }
     if (direction == InputAction::Left) {
         m_positionX += cameraSpeed * deltaTime;
     }
     if (direction == InputAction::Left) {
         m_positionY -= cameraSpeed * deltaTime;
     }
     if (direction == InputAction::Left) {
         m_positionY += cameraSpeed * deltaTime;
     }
 }

void Camera::setPosition(float x, float y){
    m_positionX = x;
    m_positionY = y;
}

void Camera::setZoomLevel(float zoom){
    m_zoomLevel = zoom;
}

glm::mat4 Camera::GetViewMatrix(){
    return glm::identity<glm::mat4>();
}