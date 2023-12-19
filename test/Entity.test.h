#pragma once
#include "VisionForge/Engine/Engine.hpp"
#include "VisionForge/EntitySystem/DefaulComponents/CameraComponent.hpp"
#include <memory>
#include "VisionForge/Common/Event.hpp"
#include "VisionForge/Common/Common.hpp"

#include <iostream>

namespace test
{

    class Entity : public vision::IEntity
    {
    public:
        Entity() {}

        void Start() override
        {
            camera = gEngine->RegistrateComponent<vision::CameraComponent>();
            Update();

            ConfMove();
        }

        void Update() override
        {
            using namespace vision;

            camera->SetCameraPosition(pos);

            std::cout << pos << std::endl;
        }

        void ProcessEvent(vision::GameEvents event) override
        {
            
        }

        vision::CameraComponent *GetCamera()
        {
            return static_cast<vision::CameraComponent *>(camera);
        }

        void ConfMove()
        {
            auto forward = [&](int, int){
                pos += speed * camera->GetCameraFront();
            };

            auto back = [&](int, int){
                pos -= speed * camera->GetCameraFront();
            };

            auto left = [&](int, int){
                pos -= glm::normalize(glm::cross(camera->GetCameraFront(), camera->GetCameraUp())) * speed;
            };

            auto right = [&](int, int){
                pos += glm::normalize(glm::cross(camera->GetCameraFront(), camera->GetCameraUp())) * speed;
            };

            vision::input::DeviceParametrs parameter;
            parameter.SetKeyIndex(sf::Keyboard::W);
            parameter.SetDeviceType(vision::input::DeviceType::KEYBOARD);

            gEngine->GetInputManager()->CreateNewInput(parameter, "forward");
            gEngine->GetInputManager()->AddInputEvent("forward", forward);

            parameter.SetKeyIndex(sf::Keyboard::S);
            gEngine->GetInputManager()->CreateNewInput(parameter, "back");
            gEngine->GetInputManager()->AddInputEvent("back", back);

            parameter.SetKeyIndex(sf::Keyboard::A);
            gEngine->GetInputManager()->CreateNewInput(parameter, "left");
            gEngine->GetInputManager()->AddInputEvent("left", left);

            parameter.SetKeyIndex(sf::Keyboard::D);
            gEngine->GetInputManager()->CreateNewInput(parameter, "right");
            gEngine->GetInputManager()->AddInputEvent("right", right);
        }

    private:
        vision::CameraComponent *camera;

        float speed = 1.0f;
        glm::vec3 pos = glm::vec3(0);
    };

}