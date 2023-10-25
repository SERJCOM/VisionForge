#include "VisionForge/EntitySystem/DefaulComponents/CameraComponent.hpp"
#include <iostream>
#include "VisionForge/Engine/Engine.hpp"
//#include "CameraComponent.hpp"

void vision::CameraComponent::Start()
{
    SetWindow(gEngine->GetSystemPtr()->GetWindow());
}

void vision::CameraComponent::Looking() 
{

    window_->setMouseCursorVisible(false);
		
    float xoffset = -(lastX - xpos);
    float yoffset = -(ypos - lastY);


    xoffset *= sensitivity_;
    yoffset *= sensitivity_;

    yaw += xoffset;	
    pitch += yoffset;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;



    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(direction);

    sf::Vector2i localPosition = sf::Mouse::getPosition(*window_);
    xpos = localPosition.x;
    ypos = localPosition.y;

    sf::Vector2i Position;
    Position.x = lastX;
    Position.y = lastY;
    sf::Mouse::setPosition(Position, *window_);


}
