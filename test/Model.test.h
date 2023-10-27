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


    }

    void Start() override{

        using std::filesystem::path;

        model = gEngine->RegistrateComponent<vision::ModelComponent>();
        model->SetPath(std::filesystem::current_path() / std::filesystem::path("..") / std::filesystem::path("test") / std::filesystem::path("obj") / std::filesystem::path("testtest.obj"));
        model->LoadModel();
        
    }

    void Update() override{
        i+= 0.005;

        model->SetObjectSize(glm::vec3(100 , 100 , 100 ));
        model->SetObjectPosition(glm::vec3(200, 0, 200));
        model->SetObjectRotation(i, glm::vec3(0.0, 1.0, 0));
    }

    void ProcessEvent(vision::GameEvents event) override {

    }


private:
vision::ModelComponent* model;

double i = 0;

};