#pragma once
#include "Entity.hpp"
#include "CameraComponent.h"
#include <memory>
#include "Engine.h"
#include <iostream>

namespace test{

class Entity : public lthm::IEntity{
public:

    Entity(lthm::Engine& engine){
        engine_ = &engine;
    }

    void Start() override{
        camera = std::make_shared<lthm::CameraComponent>(engine_->GetWindow());
        Update();
    }

    void Update() override{
        Move();
        lthm::CameraComponent& _camera = *GetCamera();
        _camera.SetCameraPosition(pos);
        camera->Update();
        // std::cout << _camera.GetCameraPos().x << " " << _camera.GetCameraPos().y << " " << _camera.GetCameraPos().z << std::endl;
    }

    std::vector<std::shared_ptr<lthm::IComponent>> GetComponents() const override {
        std::vector<std::shared_ptr<lthm::IComponent>> res;

        res.push_back(camera);

        return res;
    }

    lthm::CameraComponent* GetCamera() {
        return static_cast<lthm::CameraComponent*>(camera.get());
    }

    void Move(){

        auto camera = GetCamera();

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))	pos += speed * camera->GetCameraFront();
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))	pos -= speed * camera->GetCameraFront();
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))	pos -= glm::normalize(glm::cross(camera->GetCameraFront(), camera->GetCameraUp())) * speed;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))	pos += glm::normalize(glm::cross(camera->GetCameraFront(), camera->GetCameraUp())) * speed;
    }


private:

std::shared_ptr<lthm::IComponent> camera;
lthm::Engine* engine_;
float speed = 0.05f;
glm::vec3 pos = glm::vec3(0);
};

}