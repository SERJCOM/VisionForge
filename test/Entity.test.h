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
    }

    void Update() override{
        lthm::CameraComponent& _camera = *static_cast<lthm::CameraComponent*>(camera.get());
        // std::cout << _camera.GetCameraPos().x << " " << _camera.GetCameraPos().y << " " << _camera.GetCameraPos().z << std::endl;
    }

    std::vector<std::shared_ptr<lthm::IComponent>> GetComponents() const override {
        std::vector<std::shared_ptr<lthm::IComponent>> res;

        res.push_back(camera);

        return res;
    }

    lthm::CameraComponent* GetCamera() const {
        return static_cast<lthm::CameraComponent*>(camera.get());
    }


private:
std::shared_ptr<lthm::IComponent> camera;
lthm::Engine* engine_;
};

}