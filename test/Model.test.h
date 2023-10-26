#pragma once

#include <memory>
#include <iostream>
#include <filesystem>

#include "VisionForge/EntitySystem/DefaulComponents/ModelComponent.hpp"
#include "VisionForge/System/System.hpp"
#include "VisionForge/Engine/Material.hpp"
#include "VisionForge/Engine/Engine.hpp"


class MEntity : public vision::IEntity{
public:

    MEntity(){

        // using std::filesystem::path;
        // Li::Material material;
        // material.AddNewMaterial(model_path.parent_path() / path("Bank_Beer_BaseColor.png"), Li::Type::DIFFUSE, "blinn3");
        // material.AddNewMaterial(model_path.parent_path() / path("Bank_Beer_Metallic.png"), Li::Type::METALNESS, "blinn3");
        // material.AddNewMaterial(model_path.parent_path() / path("Bank_Beer_Normal.png"), Li::Type::NORMALS, "blinn3");
        // material.AddNewMaterial(model_path.parent_path() / path("Bank_Beer_Roughness.png"), Li::Type::ROUGHNESS, "blinn3");

    }

    void Start() override{

        // using path = std::filesystem::path;
        using std::filesystem::path;

        model = gEngine->RegistrateComponent<vision::ModelComponent>();
        model->SetPath(std::filesystem::current_path() / std::filesystem::path("..") / std::filesystem::path("test") / std::filesystem::path("obj") / std::filesystem::path("testtest.obj"));
        model->LoadModel();
    }

    void Update() override{

    }

    void ProcessEvent(vision::GameEvents event) override {

    }


private:
vision::ModelComponent* model;

};