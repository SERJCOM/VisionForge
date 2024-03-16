#include "VisionForge/EntitySystem/DefaulComponents/CameraComponent.hpp"
#include <iostream>
#include "VisionForge/Engine/Engine.hpp"
// #include "CameraComponent.hpp"

void vision::CameraComponent::Start()
{
    // SetWindow(gEngine->GetSystemPtr()->GetWindow());
    SetWindow(*System::GetInstance()->GetGLFWWindow());
}

void vision::CameraComponent::Looking()
{

    // window_->setMouseCursorVisible(false);
    // glfwSetCursorPos(window_, )
    // glfwSetInputMode(window_, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

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

    double local_pos_x, local_pos_y;
    glfwGetCursorPos(window_, &local_pos_x, &local_pos_y);
    xpos = local_pos_x;
    ypos = local_pos_y;

    sf::Vector2i Position;
    Position.x = lastX;
    Position.y = lastY;
    // sf::Mouse::setPosition(Position, *window_);
    // glfwSetCursorPos(window_, lastX, lastY);
}
