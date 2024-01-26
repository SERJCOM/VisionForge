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

    auto dir_path = std::filesystem::current_path() / path("..") / path("test") / path("assets") / path("models") / path("dimamap") ;

    model->SetPath(dir_path / path("map.obj"));


    vision::Material mat;
    mat.AddNewMaterial(dir_path  /  path("map_color.jpg"), vision::Type::DIFFUSE, "Default_OBJ");
    mat.AddNewMaterial(dir_path  /  path("map_metalness.jpg"), vision::Type::METALNESS, "Default_OBJ");
    mat.AddNewMaterial(dir_path  /  path("map_normal.jpg"), vision::Type::NORMALS, "Default_OBJ");
    mat.AddNewMaterial(dir_path  /  path("map_roughness.jpg"), vision::Type::ROUGHNESS, "Default_OBJ");


    model->AddMaterial(&mat );
    model->LoadModel();


    // house = gEngine->RegistrateComponent<vision::ModelComponent>();

    // house->SetPath(dir_path / path("../house/D_House.FBX"));
    // house->LoadModel();
    
    // house->SetObjectPosition(glm::vec3(-2, 6, 0.83));
    // house->SetObjectSize(glm::vec3(0.1, 0.1, 0.1));

    // room = gEngine->RegistrateComponent<vision::ModelComponent>();
    // room->SetPath(dir_path / path("dimaMap") / path("untitled.obj"));
    // room->LoadModel();
    
    // model->SetObjectRotation(90, glm::vec3(1, 0, 0));
    
    // model->SetObjectSize(glm::vec3(0.01, 0.01, 0.01));
    // model->SetObjectPosition(glm::vec3(10, 10, 10));
    // model->SetObjectSize(glm::vec3(10 , 10, 10));
    // model->SetObjectPosition(glm::vec3(200, 0, 200));
    
}

void Update() override{
    i+= 1;


    // light->SetObjectPosition(glm::vec3(-1, 3, 0));
    // model->SetObjectRotation(i, glm::vec3(1, 0, 0));

    // light->SetObjectPosition(glm::vec3(10,  10 , 25 + sin(i) * 10));
}

void ProcessEvent(vision::GameEvents event) override {

}


private:
vision::ModelComponent* model;
vision::ModelComponent* room;

vision::ModelComponent* house;
double i = 0;

};