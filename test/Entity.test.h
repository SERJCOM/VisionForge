#pragma once
#include "VisionForge/Engine/Engine.hpp"
#include "VisionForge/EntitySystem/DefaulComponents/CameraComponent.hpp"
#include <memory>
#include "VisionForge/Common/Event.hpp"

#include <iostream>

namespace test{

class Entity : public vision::IEntity{
public:

    Entity(){}

    void Start() override{
        camera = gEngine->RegistrateComponent<vision::CameraComponent>();
        Update(); 
    }

    void Update() override{
        Move();
        vision::CameraComponent& _camera = *GetCamera();
        _camera.SetCameraPosition(pos);
    }

    void ProcessEvent(vision::GameEvents event) override {

    }


    vision::CameraComponent* GetCamera() {
        return static_cast<vision::CameraComponent*>(camera);
    }

    void Move(){
        auto camera = GetCamera();

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))	pos += speed * camera->GetCameraFront();
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))	pos -= speed * camera->GetCameraFront();
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))	pos -= glm::normalize(glm::cross(camera->GetCameraFront(), camera->GetCameraUp())) * speed;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))	pos += glm::normalize(glm::cross(camera->GetCameraFront(), camera->GetCameraUp())) * speed;
    }


private:

vision::CameraComponent* camera;

float speed = 0.5f;
glm::vec3 pos = glm::vec3(0);
};

}