#pragma once
#include "Entity.hpp"
#include "model.h"
#include <memory>
#include "Engine.h"
#include "material.hpp"
#include <iostream>

class MEntity : public lthm::IEntity{
public:

    MEntity(lthm::Engine& engine, std::filesystem::path model_path){


        engine_ = &engine;
        std::shared_ptr<lthm::ModelComponent> _model = std::make_shared<lthm::ModelComponent>(model_path.c_str());

        // _model->ScaleObject(glm::vec3{10, 10, 10});
        _model->SetShader(engine.GetMainShader());
        _model->MoveObject(0, 0, 0);
        _model->LoadModel();


        model = std::move(_model);

    }

    void Start() override{
        
    }

    void Update() override{

    }

    std::vector<std::shared_ptr<lthm::IComponent>> GetComponents() const override {
        std::vector<std::shared_ptr<lthm::IComponent>> res;

        res.push_back(model);

        return res;
    }

    // lthm::CameraComponent* GetCamera() const {
    //     return static_cast<lthm::CameraComponent*>(camera.get());
    // }


private:
std::shared_ptr<lthm::IComponent> model;
lthm::Engine* engine_;
};