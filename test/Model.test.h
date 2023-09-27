#pragma once
#include "Entity.hpp"
#include "model.h"
#include <memory>
#include "Engine.h"
#include "material.hpp"
#include <iostream>
#include "material.hpp"

class MEntity : public lthm::IEntity{
public:

    MEntity(lthm::Engine& engine, std::filesystem::path model_path){

        using std::filesystem::path;

        engine_ = &engine;
        std::shared_ptr<lthm::ModelComponent> _model = std::make_shared<lthm::ModelComponent>(model_path.c_str());

        Li::Material material;
        material.AddNewMaterial(model_path.parent_path() / path("Bank_Beer_BaseColor.png"), Li::Type::DIFFUSE, "blinn3");
        material.AddNewMaterial(model_path.parent_path() / path("Bank_Beer_Metallic.png"), Li::Type::METALNESS, "blinn3");
        material.AddNewMaterial(model_path.parent_path() / path("Bank_Beer_Normal.png"), Li::Type::NORMALS, "blinn3");
        material.AddNewMaterial(model_path.parent_path() / path("Bank_Beer_Roughness.png"), Li::Type::ROUGHNESS, "blinn3");
        // material.AddNewMaterial(model_path.parent_path() / path("Bank_Beer_Height.png"), Li::Type::AO, "blinn3");

        _model->ScaleObject(glm::vec3{10, 10, 10});
        _model->AddMaterial(&material);
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