#pragma once

#include <memory>
#include <iostream>
#include <filesystem>

#include "VisionForge/EntitySystem/DefaulComponents/ModelComponent.hpp"
#include "VisionForge/System/System.hpp"
#include "VisionForge/Engine/Material.hpp"
#include "VisionForge/Engine/Engine.hpp"
#include "VisionForge/EntitySystem/DefaulComponents/LightComponent.hpp"


class MEntity : public vision::IEntity{
public:

MEntity(){


}

void Start() override{

    using std::filesystem::path;

    model = gEngine->RegistrateComponent<vision::ModelComponent>();

    auto dir_path = std::filesystem::current_path() / path("..") / path("test") / path("assets") / path("models") / path("girl") ;

    model->SetPath(dir_path / path("1118_nao_walk.fbx"));

    vision::Material mat;
    // mat.AddNewMaterial(dir_path  / path("Room01") / path("Bank_Beer_BaseColor.png"), vision::Type::DIFFUSE, "blinn3");
    // mat.AddNewMaterial(dir_path  / path("Room01") / path("Bank_Beer_Metallic.png"), vision::Type::METALNESS, "blinn3");
    // mat.AddNewMaterial(dir_path  / path("Room01") / path("Bank_Beer_Normal.png"), vision::Type::NORMALS, "blinn3");
    // mat.AddNewMaterial(dir_path  / path("Room01") / path("Bank_Beer_Roughness.png"), vision::Type::ROUGHNESS, "blinn3");


    // model->AddMaterial(&mat );
    // model->LoadModel();

    light = gEngine->GetEnvironmentPtr()->GetLightManagerPtr()->AddLight<vision::PointLight>();

    light->SetObjectPosition(glm::vec3(5, 1, 1));
    light->color = glm::vec3(100, 100, 100);
    //light->brightness = glm::vec3(10, 10, 10);


    // room = gEngine->RegistrateComponent<vision::ModelComponent>();
    // room->SetPath(dir_path / path("dimaMap") / path("untitled.obj"));
    // room->LoadModel();
    

    // room->SetObjectSize(glm::vec3(0.1 , 0.1, 0.1));
    // model->SetObjectPosition(glm::vec3(200, 0, 200));
    
}

void Update() override{
    i+= 0.01;

    // light->SetObjectPosition(glm::vec3(-1, 3, 0));
    // model->SetObjectRotation(i, glm::vec3(0.0, 1.0, 0));
}

void ProcessEvent(vision::GameEvents event) override {

}


private:
vision::ModelComponent* model;
vision::ModelComponent* room;
vision::PointLight* light;

double i = 0;

};