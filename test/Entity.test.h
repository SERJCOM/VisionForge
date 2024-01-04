#pragma once
#include "VisionForge/Engine/Engine.hpp"
#include "VisionForge/EntitySystem/DefaulComponents/CameraComponent.hpp"
#include <memory>
#include "VisionForge/Common/Event.hpp"
#include "VisionForge/Common/Common.hpp"

#include "VisionForge/EntitySystem/DefaulComponents/LightComponent.hpp"

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
            // Update();

            ConfMove();

            light = gEngine->GetEnvironmentPtr()->GetLightManagerPtr()->AddLight<vision::PointLight>();
            light->SetObjectPosition(glm::vec3(10, 12, 20));
            light->color = glm::vec3(1, 1, 1);
            light->brightness = glm::vec3(10, 10, 10);

            light->SetObjectPosition(glm::vec3(17, 27, 12));
        }

        void Update() override
        {
            using namespace vision;

            camera->SetObjectPosition(pos);

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

            gEngine->GetInputManagerPtr()->CreateNewInput(parameter, "forward");
            gEngine->GetInputManagerPtr()->AddInputEvent("forward", forward);

            parameter.SetKeyIndex(sf::Keyboard::S);
            gEngine->GetInputManagerPtr()->CreateNewInput(parameter, "back");
            gEngine->GetInputManagerPtr()->AddInputEvent("back", back);

            parameter.SetKeyIndex(sf::Keyboard::A);
            gEngine->GetInputManagerPtr()->CreateNewInput(parameter, "left");
            gEngine->GetInputManagerPtr()->AddInputEvent("left", left);

            parameter.SetKeyIndex(sf::Keyboard::D);
            gEngine->GetInputManagerPtr()->CreateNewInput(parameter, "right");
            gEngine->GetInputManagerPtr()->AddInputEvent("right", right);
        }

    private:
        vision::CameraComponent *camera;

        float speed = 1.0f;
        glm::vec3 pos = glm::vec3(0);

        vision::PointLight* light;
    };

}