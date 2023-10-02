#pragma once

#include "VisionForge/EntitySystem/DefaulComponents/ModelComponent.hpp"
#include <memory>
#include "VisionForge/System/System.hpp"
#include "VisionForge/Engine/Material.hpp"
#include <iostream>

#include "VisionForge/EntitySystem/DefaulComponents/LightComponent.hpp"

class MEntity : public lthm::IEntity{
public:

    MEntity(lthm::System& engine, std::filesystem::path model_path){

        using std::filesystem::path;

        engine_ = &engine;
        std::shared_ptr<lthm::ModelComponent> _model = std::make_shared<lthm::ModelComponent>(model_path.c_str());

        // Li::Material material;
        // material.AddNewMaterial(model_path.parent_path() / path("Bank_Beer_BaseColor.png"), Li::Type::DIFFUSE, "blinn3");
        // material.AddNewMaterial(model_path.parent_path() / path("Bank_Beer_Metallic.png"), Li::Type::METALNESS, "blinn3");
        // material.AddNewMaterial(model_path.parent_path() / path("Bank_Beer_Normal.png"), Li::Type::NORMALS, "blinn3");
        // material.AddNewMaterial(model_path.parent_path() / path("Bank_Beer_Roughness.png"), Li::Type::ROUGHNESS, "blinn3");

        // _model->ScaleObject(glm::vec3{10, 10, 10});
        // _model->AddMaterial(&material);
        _model->SetShader(engine.GetMainShader());
        _model->MoveObject(0, 0, 0);
        _model->LoadModel();

        model = std::move(_model);

        // std::shared_ptr<lthm::LightComponent> _light = std::make_shared<lthm::LightComponent>();

    }

    void Start() override{
        
    }

    void Update() override{

    }

    std::vector<std::shared_ptr<lthm::IComponent>> GetComponents() const override {
        std::vector<std::shared_ptr<lthm::IComponent>> res;

        res.push_back(std::dynamic_pointer_cast<lthm::IComponent>(model));

        return res;
    }

    // lthm::CameraComponent* GetCamera() const {
    //     return static_cast<lthm::CameraComponent*>(camera.get());
    // }


private:
std::shared_ptr<lthm::ModelComponent> model;
// std::shared_ptr<lthm::IComponent> light;
lthm::System* engine_;
};